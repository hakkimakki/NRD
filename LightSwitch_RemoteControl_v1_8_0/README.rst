DLMS SMart Meter Push Listener
####################################

Overview
********

This Application let you decode PushMessages from a SmartMeter. 

Tested with a Landy+GyrE450 needed the following change in code:
dlms.c:6213
if (((frame != 0x13 && frame != 0x3) || (data->moreData != DLMS_DATA_REQUEST_TYPES_NONE && data->moreData != DLMS_DATA_REQUEST_TYPES_GBT)) && (frame & 0x1) != 0)
notify.c:403
memcpy(obj->logicalName, tmp->byteArr->data, 6);
