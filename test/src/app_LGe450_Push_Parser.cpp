#include <zephyr.h>
#include <stdio.h>
#include "../dlms/include/GXDLMSNotify.h"
#include "../dlms/include/GXDLMSData.h"
//#include "../dlms/include/GXDLMSTranslator.h"

class app_LGe450_Push_Parser {       
    public:
        app_LGe450_Push_Parser(){
            bb.Capacity(2048);
            bb.Clear();
        }
    private:
        int ret; 
        // Client used to parse received data.
        CGXDLMSClient cl(true, -1, -1, DLMS_AUTHENTICATION_NONE, NULL, DLMS_INTERFACE_TYPE_HDLC);
        CGXByteBuffer bb;
        /**
        * Received data. This is used if GBT is used and data is received on
        * several data blocks.
        */
        CGXReplyData data;
        CGXReplyData notify;
};

// Method/function definition outside the class
void app_LGe450_Push_Parser::parse(const void* pSource, unsigned long count) {
    bb.set(pSource,count);
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
            }
        }
        printf("Server address: %d Client Address: %d\r\n", notify.GetServerAddress(), notify.GetClientAddress());
        notify.Clear();
        data.Clear();
        bb.Trim();
        
        printf("Done\n");
    }    
}