#include <zephyr.h>
#include <stdio.h>
#include <string.h>
#include "../dlms/include/GXDLMSNotify.h"
#include "../dlms/include/GXDLMSData.h"
#include "../dlms/include/GXDLMSClient.h"

#include <App_LGe450_Push_Parser.h>


class App_LGe450_Push_Parser {       
    public:
        App_LGe450_Push_Parser() : cl(true, -1, -1, DLMS_AUTHENTICATION_NONE, NULL, DLMS_INTERFACE_TYPE_HDLC){
            bb.Capacity(2048);
            bb.Clear();
        }
        void parse(const void* pSource, unsigned long count);
    private:
        int ret; 
        // Buffer
        CGXByteBuffer bb;
        // Client used to parse received data.
        CGXDLMSClient cl;
        /**
        * Received data. This is used if GBT is used and data is received on
        * several data blocks.
        */
        CGXReplyData data;
        CGXReplyData notify;
};

// Method/function definition outside the class
void App_LGe450_Push_Parser::parse(const void* pSource, unsigned long count) {

    //Make String out of It
    static char HexString[1024];
    memcpy(HexString,pSource,(size_t)count);
    HexString[(size_t)count] = (char)0x0;
    bb.SetHexString(HexString);
    bb.SetPosition(0);
    
    /** Parse HDLC Frame */
    if ((ret = cl.GetData(bb, data, notify)) != 0 && ret != DLMS_ERROR_CODE_FALSE)
    {
        printk("Error cl.GetData: %u\n", ret);
    }
    /** Is More Data available */
    printk("Packet Complete: %u\n", notify.IsComplete());
    printk("More Data: %u\n", notify.IsMoreData());
    bb.Clear();
    //All Data Received
    if((notify.IsMoreData() == 0) && (notify.IsComplete() == 1)){
        //Example is sending list of push messages in first parameter.
        if (notify.GetValue().vt == DLMS_DATA_TYPE_STRUCTURE)
        {
            std::vector<std::pair<CGXDLMSObject *, unsigned char>> objects;
            ret = cl.ParsePushObjects(notify.GetValue().Arr[0].Arr, objects);
            //Remove first item because it's not needed anymore.
            objects.erase(objects.begin());
            //Update clock.
            int Valueindex = 1;
            std::vector<std::string> values;
            // Init new Meassages
            Smart_Meter_data = Smart_Meter_data_init;
            for (std::vector<std::pair<CGXDLMSObject *, unsigned char>>::iterator it = objects.begin(); it != objects.end(); ++it)
            {
                values.clear();
                cl.UpdateValue(*it->first, it->second, notify.GetValue().Arr[Valueindex]);
                ++Valueindex;
                //Print value
                std::string ln;
                it->first->GetLogicalName(ln);
                it->first->GetValues(values);
                printf("%s %s %d: %s\r\n", CGXDLMSConverter::ToString(it->first->GetObjectType()), ln.c_str(), it->second, values.at(it->second - 1).c_str());
                //Fill in the Data
                if (strcmp("1.0.31.7.0.255",ln.c_str()) == 0) {
                    Smart_Meter_data.Strom_L1 = (uint16_t)atoi(values.at(it->second - 1).c_str());
                    new_data_bitmask[0] |= 1 << 0;
                } else if (strcmp("1.0.51.7.0.255",ln.c_str()) == 0) {
                    Smart_Meter_data.Strom_L2 = (uint16_t)atoi(values.at(it->second - 1).c_str());
                    new_data_bitmask[0] |= 1 << 1;
                } else if (strcmp("1.0.71.7.0.255",ln.c_str()) == 0) {
                    Smart_Meter_data.Strom_L3 = (uint16_t)atoi(values.at(it->second - 1).c_str());
                    new_data_bitmask[0] |= 1 << 2;
                } else if (strcmp("1.0.1.7.0.255",ln.c_str()) == 0) {
                    Smart_Meter_data.Wirkleistungsbezug = (uint32_t)atoi(values.at(it->second - 1).c_str());
                    new_data_bitmask[0] |= 1 << 3;
                } else if (strcmp("1.1.1.8.1.255",ln.c_str()) == 0) {
                    Smart_Meter_data.Wirkenergiebezug_Tarif_1 = (uint32_t)atoi(values.at(it->second - 1).c_str());
                    new_data_bitmask[0] |= 1 << 4;
                } else if (strcmp("1.1.1.8.2.255",ln.c_str()) == 0) {
                    Smart_Meter_data.Wirkenergiebezug_Tarif_2 = (uint32_t)atoi(values.at(it->second - 1).c_str());
                    new_data_bitmask[0] |= 1 << 5;
                } 
           }
           //Encode and Send Data
           k_sem_give(&parser_done_sem);
        }
        printf("Server address: %d Client Address: %d\r\n", notify.GetServerAddress(), notify.GetClientAddress());
        notify.Clear();
        data.Clear();
        bb.Trim();
    }    
}

/*extern "C"*/ void* App_LGe450_Push_Parser_create(){
    static App_LGe450_Push_Parser app_LGe450_Push_Parser;
    return &app_LGe450_Push_Parser;
}
/*extern "C"*/ void App_LGe450_Push_Parser_release(void* app_LGe450_Push_Parser){
    delete static_cast<App_LGe450_Push_Parser*>(app_LGe450_Push_Parser);
}
/*extern "C"*/ void App_LGe450_Push_Parser_parse(void* app_LGe450_Push_Parser, const void* pSource, unsigned long count){
    static_cast<App_LGe450_Push_Parser*>(app_LGe450_Push_Parser)->parse(pSource, count);
}