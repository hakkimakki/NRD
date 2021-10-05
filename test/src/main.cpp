#include <zephyr.h>
#include <stdio.h>
#include "../dlms/include/GXDLMSNotify.h"
#include "../dlms/include/GXDLMSData.h"
//#include "../dlms/include/GXDLMSTranslator.h"




void main(void)
{
    
    printf("Started\n");
    printf("Landys+Gyr E450 Push Listener started\n");

    static int ret;    

    //CGXByteBuffer reply;
    // Client used to parse received data.
    static CGXDLMSClient cl(true, -1, -1, DLMS_AUTHENTICATION_NONE, NULL, DLMS_INTERFACE_TYPE_HDLC);

    static CGXByteBuffer bb;
    ret = bb.Capacity(2048);

    /**
    * Received data. This is used if GBT is used and data is received on
    * several data blocks.
    */
    static CGXReplyData data;
    static CGXReplyData notify;

    /** Frames */
    char const *p1 = "7ea084ceff0313128be6e700e04000010000700f0001d3760c07e5061c010f1b32ff800000020e010e020412002809060008190900ff0f02120000020412002809060008190900ff0f01120000020412000109060000600100ff0f02120000020412000309060100010700ff0f02120000020412000309060100020700ff0f02120000b21a7e";
    char const *p2 = "7ea07dceff0313d045e040000200006c020412000309060101010800ff0f02120000020412000309060101020800ff0f02120000020412000309060101050800ff0f02120000020412000309060101060800ff0f02120000020412000309060101070800ff0f02120000020412000309060101080800ff0f02120000c1957e";
    char const *p3 = "7ea08aceff0313aaeae0c000030000790204120003090601001f0700ff0f02120000020412000309060100330700ff0f02120000020412000309060100470700ff0f0212000009060008190900ff090835363535323737330600000047060000000006000343f20600000000060000209d06000000000600000000060001a02212002412001112001032167e"; 
    bb.SetHexString(p1);
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

    /** Frame 2 */
    
    bb.SetHexString(p2);
    bb.SetPosition(0);

    /** Parse HDLC Frame */
    if ((ret = cl.GetData(bb, data, notify)) != 0 && ret != DLMS_ERROR_CODE_FALSE)
    {
        printf("Error cl.GetData: %u", ret);
    }
    /** Is More Data available */
    printf("Packet Complete: %u\n", notify.IsComplete());
    printf("More Data: %u\n", notify.IsMoreData());
    bb.Clear();

    /** Frame 3 */
    
    bb.SetHexString(p3);
    bb.SetPosition(0);

    /** Parse HDLC Frame */
    if ((ret = cl.GetData(bb, data, notify)) != 0 && ret != DLMS_ERROR_CODE_FALSE)
    {
        printf("Error cl.GetData: %u", ret);
    }
    /** Is More Data available */
    printf("Packet Complete: %u\n", notify.IsComplete());
    printf("More Data: %u\n", notify.IsMoreData());
    bb.Clear();

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