/*
This file is part of Gateway.

Gateway is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Gateway is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Gateway.  If not, see <http://www.gnu.org/licenses/>.
*/

/* AUTHOR 	 :    Raffael Anklin       */

#include <zephyr.h>
#include <stdio.h>
#include "sz_dlms_push_parser_lg450.h"
#include "../dlms/include/GXDLMSNotify.h"
#include "../dlms/include/GXDLMSData.h"

/**
 * @brief DLMS Push Listener LG450 does Parse Push Messeges HDLC (M-BUS) tested with a Landys+Gyr e450 Smart Meter. 
 * 
 */



void dlms_push_parser_lge450_parse(uint8_t *rx_data, unsigned long count)
{

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

  bb.Set(rx_data, count);
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
  if (notify.IsComplete() && !notify.IsMoreData())
  {
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