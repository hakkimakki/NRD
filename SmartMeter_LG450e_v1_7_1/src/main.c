/*
 * Copyright (c) 2017 Raffael Anklin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* ---------------------- Base128 Unsigned Compression ------------------------ */

#include <zephyr.h>
#include <sys/printk.h>
#include <stdio.h>
#include <string.h>

/**
 * Write unsigned LEB128 data
 * @dst: the address where the ULEB128 data is to be stored
 * @val: value to be stored
 *
 * Encode an unsigned LEB128 encoded datum. The algorithm is taken
 * from Appendix C of the DWARF 3 spec. For information on the
 * encodings refer to section "7.6 - Variable Length Data". Return
 * the number of bytes written.
 */
size_t szl_encode_uleb128(uint64_t val, uint8_t * dst){
	static uint8_t count;
	static uint8_t byte;
  count = 0;
	do {
		byte = val & 0x7f;
		val >>= 7;

		if (val != 0)
		byte |= 0x80;  // mark this byte to show that more bytes will follow

		memcpy(dst+count,&byte,1);

		count++;
  	} while (val != 0);
	return count;
}

/**
 * Read unsigned LEB128 data
 * @addr: the address where the ULEB128 data is stored
 * @ret: address to store the result
 *
 * Decode an unsigned LEB128 encoded datum. The algorithm is taken
 * from Appendix C of the DWARF 3 spec. For information on the
 * encodings refer to section "7.6 - Variable Length Data". Return
 * the number of bytes read.
 */
size_t szl_decode_uleb128(uint8_t* addr, uint64_t* ret) {
  static uint8_t byte;
  static uint64_t result;
  static int shift;
  static size_t count;

  shift = 0;
  count = 0;
  result = 0;

  while (1) {
    byte = addr[count];
    count++;

    result |= (byte & 0x7f) << shift;
    shift += 7;

    if (!(byte & 0x80)) break;
  }

  memcpy(ret,&result,count);

  return count;
}

/* ---------------------- Sponge Data Protocol ------------------------ */

#include <zephyr.h>

//Data structure
struct Smart_Meter_data_t {
    uint16_t Strom_L1;
    uint16_t Strom_L2;
    uint16_t Strom_L3;
    uint32_t Wirkleistungsbezug;
    uint32_t Wirkenergiebezug_Tarif_1;
    uint32_t Wirkenergiebezug_Tarif_2;
};

//Number of struct elements for new_data_bitmask = n_data / 8 -> round up to byte
uint8_t new_data_bitmask[1];  

//Data
const struct Smart_Meter_data_t Smart_Meter_data_init;
struct Smart_Meter_data_t Smart_Meter_data;

/**
 * Encode the buffer with sponge
 * @buffer: buffer to encode into
 * @ret: size of encoded bytes
 */
int sponge_encode(uint8_t *buffer) {
    //Encode Message 
    int pos = 0;
    printk("Bitmask: %u\n",new_data_bitmask[0]); 
    pos += szl_encode_uleb128(new_data_bitmask[0],&buffer[pos]);
    if (new_data_bitmask[0] & (1 << 0))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Strom_L1,&buffer[pos]);
    }
    if (new_data_bitmask[0] & (1 << 1))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Strom_L2,&buffer[pos]);
    }
    if (new_data_bitmask[0] & (1 << 2))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Strom_L3,&buffer[pos]);
    }
    if (new_data_bitmask[0] & (1 << 3))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Wirkleistungsbezug,&buffer[pos]);
    }
    if (new_data_bitmask[0] & (1 << 4))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Wirkenergiebezug_Tarif_1,&buffer[pos]);
    }
    if (new_data_bitmask[0] & (1 << 5))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Wirkenergiebezug_Tarif_2,&buffer[pos]);
    } 
    printk("Message Encoded Size: %u\n",pos);   
    //Send LoRa 
    //k_sleep(K_MSEC(1000));
    //szl_lora_send((uint8_t *)"&buffer[0]", sizeof("&buffer[0]")-1);  
    //szl_lora_send(&buffer[0], (uint32_t) pos+1);
    //k_sleep(K_MSEC(1000));
    printk("Buffer Debug[0]: %u\n",buffer[0]); 
    printk("Buffer Debug[1]: %u\n",buffer[1]);
    printk("Buffer Debug[2]: %u\n",buffer[2]);
    return pos;
}

/**
 * Decode the buffer with sponge
 * @buffer: buffer to decode from
 * @ret: size of decoded bytes
 */
int sponge_decode(uint8_t *buffer) { 
    Smart_Meter_data = Smart_Meter_data_init;   
    static int pos;
    pos = 0;
    pos += szl_decode_uleb128(&buffer[pos],&new_data_bitmask[0]);
    printk("Bitmask: %u\n",new_data_bitmask[0]);
    if (new_data_bitmask[0] & (1 << 0))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Strom_L1);
    }
    if (new_data_bitmask[0] & (1 << 1))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Strom_L2);
    }
    if (new_data_bitmask[0] & (1 << 2))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Strom_L3);
    }
    if (new_data_bitmask[0] & (1 << 3))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Wirkleistungsbezug);
    }
    if (new_data_bitmask[0] & (1 << 4))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Wirkenergiebezug_Tarif_1);
    }
    if (new_data_bitmask[0] & (1 << 5))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Wirkenergiebezug_Tarif_2);
    } 
    printk("Message Decoded Size: %u\n",pos); 
    printk("Current L3: %u\n",Smart_Meter_data.Strom_L3);  
    return pos;
}


/* ---------------------- DLMS Push Listener ------------------------ */
#include <zephyr.h>
#include <sys/printk.h>
#include <console/console.h>

#include "gxignore.h"
#include "serverevents.h"
#include "dlmssettings.h"
#include "gxvalueeventargs.h"
#include "gxObjects.h"
#include "bytebuffer.h"
#include "variant.h"
#include "objectarray.h"
#include "cosem.h"
#include "dlms.h"
#include "notify.h"
#include "converters.h"
#include <stdlib.h>

//DLMS Settings
dlmsSettings settings;

//Received data.
gxByteBuffer frameData;
gxReplyData data;

DLMS_ACCESS_MODE svr_getAttributeAccess(
  dlmsSettings * settings /*settings*/,
  gxObject * obj /*obj*/,
  unsigned char index /*index*/)
{
  //Client don't need this.
  return DLMS_ACCESS_MODE_NONE;
}

DLMS_METHOD_ACCESS_MODE svr_getMethodAccess(
  dlmsSettings * settings /*settings*/,
  gxObject * obj /*obj*/,
  unsigned char index /*index*/)
{
  //Client don't need this.
  return DLMS_METHOD_ACCESS_MODE_NONE;
}

/////////////////////////////////////////////////////////////////////////////
//Client has made connection to the server.
/////////////////////////////////////////////////////////////////////////////
int svr_connected(
  dlmsServerSettings* settings)
{
  //Empty skeleton. This is added because server implementation needs this.
  return 0;
}

unsigned char svr_isTarget(
  dlmsSettings * settings /*settings*/,
  uint32_t serverAddress /*serverAddress*/,
  uint32_t clientAddress /*clientAddress*/)
{
  return 0;
}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void svr_preRead(
  dlmsSettings* settings,
  gxValueEventCollection* args)
{
  //Empty skeleton. This is added because server implementation needs this.
}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void svr_postRead(
  dlmsSettings* settings,
  gxValueEventCollection* args)
{
  //Empty skeleton. This is added because server implementation needs this.
}

void dlms_push_listener_init(void)
{
  console_init();
  BYTE_BUFFER_INIT(&frameData);
  //Set frame capacity.
  bb_capacity(&frameData, 512);
  reply_init(&data);
  //TODO: Parameters depend from the meter.
  cl_init(&settings, true, 13311, 1, DLMS_AUTHENTICATION_NONE, NULL, DLMS_INTERFACE_TYPE_HDLC);
}

void dlms_push_listener_rx(void)
{
  while (1)
  {
    //Wait for Serial Data
    uint8_t c = console_getchar();
    //Append to Data
    uint8_t available = 1;
    if (available > 0)
    {
      if (frameData.size + available > frameData.capacity)
      {
        available = frameData.capacity - frameData.size;
        if (available == 0)
        {
          printk("Buffer is full!\n");
          bb_empty(&frameData);
          return;
        }
      }
      *(frameData.data + frameData.size) = c;
      frameData.size += available;
      if (notify_getData(&settings, &frameData, &data) != 0)
      {
        printk("Invalid data received!\n");
        reply_clear(&data);
      }
      else
      {
        if (data.complete)
        {
          bb_empty(&frameData);
          if (data.moreData == DLMS_DATA_REQUEST_TYPES_NONE)
          {
            dlmsVARIANT * tmp;
            gxObject *item;
            gxArray items;
            uint16_t pos;
            char ln[20];
            arr_init(&items);
            printk("Time Unix Epoch: %lu\n",data.time);
            notify_parsePush(&settings, data.dataValue.Arr, &items);
            Smart_Meter_data = Smart_Meter_data_init; //Init the Target Data Structure
            new_data_bitmask[0] = 0x0; //Init the new_data_bitmask
            for (pos = 0; pos != settings.objects.size; ++pos)
            {
                oa_getByIndex(&settings.objects,pos,&item);
                snprintk(ln,sizeof(ln)-1,"%u.%u.%u.%u.%u.%u",item->logicalName[0],item->logicalName[1],item->logicalName[2],item->logicalName[3],item->logicalName[4],item->logicalName[5]);
                printk("LN: %u.%u.%u.%u.%u.%u\n",item->logicalName[0],item->logicalName[1],item->logicalName[2],item->logicalName[3],item->logicalName[4],item->logicalName[5]);
                if (strcmp(ln,"1.0.31.7.0.255") == 0)
                {
                  va_getByIndex(data.dataValue.Arr,pos+1,&tmp);
                  printk("Strom L1: %u\n",tmp->uiVal);
                  Smart_Meter_data.Strom_L1 = tmp->uiVal;
                  new_data_bitmask[0] |= 1 << 0;
                }
                if (strcmp(ln,"1.0.51.7.0.255") == 0)
                {
                  va_getByIndex(data.dataValue.Arr,pos+1,&tmp);
                  printk("Strom L2: %u\n",tmp->uiVal);
                  Smart_Meter_data.Strom_L2 = tmp->uiVal;
                  new_data_bitmask[0] |= 1 << 1;
                }
                if (strcmp(ln,"1.0.71.7.0.255") == 0)
                {
                  va_getByIndex(data.dataValue.Arr,pos+1,&tmp);
                  printk("Strom L3: %u\n",tmp->uiVal);
                  Smart_Meter_data.Strom_L3 = tmp->uiVal;
                  new_data_bitmask[0] |= 1 << 2;
                }
                if (strcmp(ln,"1.0.1.7.0.255") == 0)
                {
                  va_getByIndex(data.dataValue.Arr,pos+1,&tmp);
                  printk("Wirkleistungsbezug: %lu\n",tmp->ulVal);
                  Smart_Meter_data.Wirkleistungsbezug = tmp->ulVal;
                  new_data_bitmask[0] |= 1 << 3;
                }
                if (strcmp(ln,"1.1.1.8.1.255") == 0)
                {
                  va_getByIndex(data.dataValue.Arr,pos+1,&tmp);
                  printk("Wirkenergiebezug Tarif 1: %lu\n",tmp->ulVal);
                  Smart_Meter_data.Wirkenergiebezug_Tarif_1 = tmp->ulVal;
                  new_data_bitmask[0] |= 1 << 4;
                } 
                if (strcmp(ln,"1.1.1.8.2.255") == 0)
                {
                  va_getByIndex(data.dataValue.Arr,pos+1,&tmp);
                  printk("Wirkenergiebezug Tarif 2: %lu\n",tmp->ulVal);
                  Smart_Meter_data.Wirkenergiebezug_Tarif_2 = tmp->ulVal;
                  new_data_bitmask[0] |= 1 << 5;
                }                                 
            }
            bb_empty(&frameData);
            reply_clear(&data);
            break;
          }
        }
      }
    }
  }

}


/* ---------------------- LoRa ------------------------ */

#include <device.h>
#include <drivers/lora.h>
#include <errno.h>
#include <sys/util.h>
#include <zephyr.h>
#include <sys/crc.h>
#include <logging/log.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_RADIO_NODE DT_ALIAS(lora0)
BUILD_ASSERT(DT_NODE_HAS_STATUS(DEFAULT_RADIO_NODE, okay),
             "No default LoRa radio specified in DT");
#define DEFAULT_RADIO DT_LABEL(DEFAULT_RADIO_NODE)

#define MAX_DATA_LEN 255

const struct device *lora_dev;
struct lora_modem_config config;
static int ret, len;
uint8_t data_crc[MAX_DATA_LEN] = {0};
uint16_t crc, crc_calc;
int16_t rssi;
int8_t snr;

void szl_lora_init()
{

    lora_dev = device_get_binding(DEFAULT_RADIO);
    if (!lora_dev)
    {
        printk("%s Device not found\n", DEFAULT_RADIO);
        return;
    }

    config.frequency = 865100000;
    config.bandwidth = BW_125_KHZ;
    config.datarate = SF_10;
    config.preamble_len = 8;
    config.coding_rate = CR_4_5;
    config.tx_power = 4;
    config.tx = true;

    ret = lora_config(lora_dev, &config);
    if (ret < 0)
    {
        printk("LoRa config failed\n");
        return;
    }
}

void szl_lora_send(uint8_t *data, uint32_t data_len)
{
    if (lora_dev == NULL)
    {
        printk("Could not get LoRa device\n");
        return;
    }

    //Prepare Device for Sending
    config.tx_power = 4;
    config.tx = true;

    ret = lora_config(lora_dev, &config);
    if (ret < 0)
    {
        printk("LoRa config failed\n");
        return;
    }

    // Calc CRC
    crc = crc16_ccitt(0, data, (size_t)data_len);
    // Append CRC    
    memcpy(data_crc, data, (size_t)data_len);                   // copy data
    memcpy(data_crc + (size_t)data_len, &crc, sizeof(crc));      // copy crc

    ret = lora_send(lora_dev, data_crc, (size_t)data_len + sizeof(crc));
    if (ret < 0)
    {
        printk("LoRa send failed\n");
        return;
    }

    printk("Data sent!\n");
}

uint32_t szl_lora_recv(uint8_t *data)
{
    if (lora_dev == NULL)
    {
        printk("Could not get LoRa device\n");
        return 0;
    }

    //Prepare Device for Receiving
    config.tx_power = 14;
    config.tx = false;

    ret = lora_config(lora_dev, &config);
    if (ret < 0)
    {
        printk("LoRa config failed\n");
        return 0;
    }
    /* Block until data arrives */
    len = lora_recv(lora_dev, data_crc, MAX_DATA_LEN, K_FOREVER,
                    &rssi, &snr);
    if (len <= 0)
    {
        printk("LoRa receive failed\n");
        return 0;
    }
    /* Decode CRC */
    memcpy(&crc, data_crc + (size_t) len - sizeof(crc), sizeof(crc));      // copy crc
    crc_calc = crc16_ccitt(0,data_crc,(size_t) len - sizeof(crc)); // Calculate CRC
    if (crc != crc_calc)
    {
        printk("LoRa receive CRC Check failed\n");
        return 0;
    } 
    memcpy(data, data_crc, (size_t) len - sizeof(crc));      // copy data    

    printk("Received data: %s (RSSI:%ddBm, SNR:%ddBm)\n",
           log_strdup(data), rssi, snr);
    return len;
}


/* ------------------- Main App ---------------------------- */

void main(void)
{
  printk("Init Application\n");  
  dlms_push_listener_init();
  szl_lora_init();

  printk("Starting Application\n");
  char buffer[255];
  int sz;
  while (1)
  {
    dlms_push_listener_rx(); //Wait for a DLMS Package Received
    sz = sponge_encode(buffer); //Encode the Received Data into Sponge structure
    szl_lora_send(buffer,sz); //Send the Encoded Buffer over LoRa
  }
  
  
}
