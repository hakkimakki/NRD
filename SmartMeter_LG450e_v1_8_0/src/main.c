/*
 * Copyright (c) 2017 Raffael Anklin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* ---------------------- COMP PPI GPIOTE M-Bus UART ------------------------ */
#include <sys/printk.h>
#include <nrfx_gpiote.h>
#include <hal/nrf_gpio.h>
#include <nrfx_comp.h>
#include <helpers/nrfx_gppi.h>
#if defined(DPPI_PRESENT)
#include <nrfx_dppi.h>
#else
#include <nrfx_ppi.h>
#endif

#define OUTPUT_PIN_LED 8
#define OUTPUT_PIN 13

#define INPUT_A0	7

#define COMP_LPCOMP_IRQn	19

static void comparator_handler (nrf_comp_event_t event)
{
	printk("Comp event");
}

void init_mbus_comp_gpiote(){
  /* Comp Init */
  nrfx_comp_config_t  comp_config = NRFX_COMP_DEFAULT_CONFIG(INPUT_A0);
  comp_config.reference = NRF_COMP_REF_Int2V4;
  nrf_comp_th_t const thres = {
    .th_down = NRFX_VOLTAGE_THRESHOLD_TO_INT(2.0, 2.4),
    .th_up = NRFX_VOLTAGE_THRESHOLD_TO_INT(2.1, 2.4)
  };
  comp_config.threshold = thres;
	nrfx_comp_init(&comp_config, comparator_handler);
	//nrfx_comp_start(NRFX_COMP_EVT_EN_CROSS_MASK, 0);
  nrfx_comp_start(0, 0);
  /* GPIOTE Init */
  nrfx_gpiote_init(0);
  
  nrfx_gpiote_out_config_t const out_config = {
		.action = NRF_GPIOTE_POLARITY_TOGGLE,
		.init_state = 0,
		.task_pin = true,
	};
  
  /* Initialize output pin. SET task will turn the LED on,
	 * CLR will turn it off and OUT will toggle it.
	 */
	nrfx_gpiote_out_init(OUTPUT_PIN, &out_config);
  nrfx_gpiote_out_task_enable(OUTPUT_PIN);
  nrfx_gpiote_out_init(OUTPUT_PIN_LED, &out_config);
  nrfx_gpiote_out_task_enable(OUTPUT_PIN_LED);
  /* Allocate a (D)PPI channel. */
	nrf_ppi_channel_t channel_up;
	nrf_ppi_channel_t channel_down;
	nrfx_ppi_channel_alloc(&channel_up);
	nrfx_ppi_channel_alloc(&channel_down);
  nrf_ppi_channel_t channel_up_led;
	nrf_ppi_channel_t channel_down_led;
	nrfx_ppi_channel_alloc(&channel_up_led);
	nrfx_ppi_channel_alloc(&channel_down_led);
	/* Configure endpoints of the channel so that the input pin event is
	 * connected with the output pin OUT task. This means that each time
	 * the button is pressed, the LED pin will be toggled.
	 */
	nrfx_gppi_channel_endpoints_setup(channel_up,
			nrf_comp_event_address_get(NRF_COMP,NRF_COMP_EVENT_UP),
			nrf_gpiote_task_address_get(NRF_GPIOTE,
				nrfx_gpiote_set_task_get(OUTPUT_PIN)));
	nrfx_gppi_channel_endpoints_setup(channel_down,
			nrf_comp_event_address_get(NRF_COMP,NRF_COMP_EVENT_DOWN),
			nrf_gpiote_task_address_get(NRF_GPIOTE,
				nrfx_gpiote_clr_task_get(OUTPUT_PIN)));
  nrfx_gppi_channel_endpoints_setup(channel_up_led,
			nrf_comp_event_address_get(NRF_COMP,NRF_COMP_EVENT_UP),
			nrf_gpiote_task_address_get(NRF_GPIOTE,
				nrfx_gpiote_set_task_get(OUTPUT_PIN_LED)));
	nrfx_gppi_channel_endpoints_setup(channel_down_led,
			nrf_comp_event_address_get(NRF_COMP,NRF_COMP_EVENT_DOWN),
			nrf_gpiote_task_address_get(NRF_GPIOTE,
				nrfx_gpiote_clr_task_get(OUTPUT_PIN_LED)));
	/* Enable (D)PPI channel. */
  nrfx_ppi_channel_enable(channel_up);
	nrfx_ppi_channel_enable(channel_down);
  nrfx_ppi_channel_enable(channel_up_led);
	nrfx_ppi_channel_enable(channel_down_led);
}

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
    //uint32_t BlindenergiebezugRi;
    //uint32_t BlindenergiebezugRc;
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
    //printk("Bitmask: %u\n",new_data_bitmask[0]); 
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
    //printk("Bitmask: %u\n",new_data_bitmask[0]);
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
    //printk("Message Decoded Size: %u\n",pos); 
    //printk("Current L3: %u\n",Smart_Meter_data.Strom_L3);  
    return pos;
}


/* ---------------------- DLMS Push Listener ------------------------ */
#include <zephyr.h>
#include <sys/printk.h>
#include <console/console.h>
#include <device.h>
#include <drivers/gpio.h>
#include <console/tty.h>
#include <drivers/uart.h>

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

//LEDs
static struct gpio_dt_spec led_green = GPIO_DT_SPEC_GET_OR(DT_ALIAS(led0), gpios,{0});

//Consol Stuff
static struct tty_serial console_serial;

static uint8_t console_rxbuf[CONFIG_CONSOLE_GETCHAR_BUFSIZE];
static uint8_t console_txbuf[CONFIG_CONSOLE_PUTCHAR_BUFSIZE];

int dlms_console_init(void)
{
	const struct device *uart_dev;
	int ret;

	uart_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));
	if (!device_is_ready(uart_dev)) {
		return -ENODEV;
	}

	ret = tty_init(&console_serial, uart_dev);

	if (ret) {
		return ret;
	}

	/* Checks device driver supports for interrupt driven data transfers. */
	if (CONFIG_CONSOLE_GETCHAR_BUFSIZE + CONFIG_CONSOLE_PUTCHAR_BUFSIZE) {
		const struct uart_driver_api *api =
			(const struct uart_driver_api *)uart_dev->api;
		if (!api->irq_callback_set) {
			return -ENOTSUP;
		}
	}

	tty_set_tx_buf(&console_serial, console_txbuf, sizeof(console_txbuf));
	tty_set_rx_buf(&console_serial, console_rxbuf, sizeof(console_rxbuf));

  //Set Timeout
  console_serial.rx_timeout = 100; //100ms

	return 0;
}

ssize_t dlms_console_read(void *dummy, void *buf, size_t size)
{
	ARG_UNUSED(dummy);

	return tty_read(&console_serial, buf, size);
}

//DLMS Settings
dlmsSettings settings;

//Received data.
gxByteBuffer frameData;
gxReplyData data;
gxArray items;

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
  dlms_console_init();
  BYTE_BUFFER_INIT(&frameData);
  //Set frame capacity.
  bb_capacity(&frameData, 1024);
  reply_init(&data);
  bb_capacity(&data.data, 1024);
  arr_init(&items);
  arr_capacity(&items, 1024);
  //TODO: Parameters depend from the meter.
  cl_init(&settings, true, 13311, 1, DLMS_AUTHENTICATION_NONE, NULL, DLMS_INTERFACE_TYPE_HDLC);
  //init LEDs
  gpio_pin_configure_dt(&led_green,  GPIO_OUTPUT_INACTIVE);
}


static char dlms_raw_bin_test_data[] = {
  126, 160, 132, 206, 255,   3,  19,  18, 
  139, 230, 231,   0, 224,  64,   0,   1, 
    0,   0, 112,  15,   0,   1, 211, 118, 
  12,   7, 229,   6,  28,   1,  15,  27, 
  50, 255, 128,   0,   0,   2,  14,   1, 
  14,   2,   4,  18,   0,  40,   9,   6, 
    0,   8,  25,   9,   0, 255,  15,   2, 
  18,   0,   0,   2,   4,  18,   0,  40, 
    9,   6,   0,   8,  25,   9,   0, 255, 
  15,   1,  18,   0,   0,   2,   4,  18, 
    0,   1,   9,   6,   0,   0,  96,   1, 
    0, 255,  15,   2,  18,   0,   0,   2, 
    4,  18,   0,   3,   9,   6,   1,   0, 
    1,   7,   0, 255,  15,   2,  18,   0, 
    0,   2,   4,  18,   0,   3,   9,   6, 
    1,   0,   2,   7,   0, 255,  15,   2, 
  18,   0,   0, 178,  26, 126, 126, 160, 
  125, 206, 255,   3,  19, 208,  69, 224, 
  64,   0,   2,   0,   0, 108,   2,   4, 
  18,   0,   3,   9,   6,   1,   1,   1, 
    8,   0, 255,  15,   2,  18,   0,   0, 
    2,   4,  18,   0,   3,   9,   6,   1, 
    1,   2,   8,   0, 255,  15,   2,  18, 
    0,   0,   2,   4,  18,   0,   3,   9, 
    6,   1,   1,   5,   8,   0, 255,  15, 
    2,  18,   0,   0,   2,   4,  18,   0, 
    3,   9,   6,   1,   1,   6,   8,   0, 
  255,  15,   2,  18,   0,   0,   2,   4, 
  18,   0,   3,   9,   6,   1,   1,   7, 
    8,   0, 255,  15,   2,  18,   0,   0, 
    2,   4,  18,   0,   3,   9,   6,   1, 
    1,   8,   8,   0, 255,  15,   2,  18, 
    0,   0, 193, 149, 126, 126, 160, 138, 
  206, 255,   3,  19, 170, 234, 224, 192, 
    0,   3,   0,   0, 121,   2,   4,  18, 
    0,   3,   9,   6,   1,   0,  31,   7, 
    0, 255,  15,   2,  18,   0,   0,   2, 
    4,  18,   0,   3,   9,   6,   1,   0, 
  51,   7,   0, 255,  15,   2,  18,   0, 
    0,   2,   4,  18,   0,   3,   9,   6, 
    1,   0,  71,   7,   0, 255,  15,   2, 
  18,   0,   0,   9,   6,   0,   8,  25, 
    9,   0, 255,   9,   8,  53,  54,  53, 
  53,  50,  55,  55,  51,   6,   0,   0, 
    0,  71,   6,   0,   0,   0,   0,   6, 
    0,   3,  67, 242,   6,   0,   0,   0, 
    0,   6,   0,   0,  32, 157,   6,   0, 
    0,   0,   0,   6,   0,   0,   0,   0, 
    6,   0,   1, 160,  34,  18,   0,  36, 
  18,   0,  17,  18,   0,  16,  50,  22, 
  126
};


void dlms_push_listener_rx(void)
{
  static bool done;
  static int count;
  done = false;
  while (!done)
  {
    //Wait for Serial Data
    static char buf[512];
    static int bytes_read;
    bytes_read = dlms_console_read(NULL,buf,512);
    //k_msleep(2000);
    //bytes_read = sizeof(dlms_raw_bin_test_data);
    //memcpy(buf,dlms_raw_bin_test_data,bytes_read);
    //printk("Received: %d\n", bytes_read);
    //printk("Count: %d\n",count); 
    count++;  
    //Append to Data
    if (bytes_read > 0)
    {
      //Split into frames
      static char delim = 126; // 7e
      static char * frame_start;
      static int pos = 0;
      pos = 0;
      frame_start = NULL;
      //Get Start of Frame
      for (size_t i = 0; i < bytes_read; i++)
      {
        if (buf[i] == delim)
        {
          frame_start = &buf[i];
          pos = i;
          break;
        }        
      }
      while (frame_start != NULL)
      {
        //Get Frame Size
        static int err;
        static short frame_size;
        frame_size = buf[pos+2];
        //frame_size = frame_size & 0x07FF; //Get rid of Type and segmentation bit
        frame_size = frame_size + 2; //Append Tag fields sizes
        //Parse the Frame
        //printf("Frame:\n%.*s\n", (int)frame_size, frame_start);
        //printk("Frame Size: %u\n", frame_size);
        bb_empty(&frameData);
        bb_set(&frameData,frame_start,(size_t)frame_size);
        frameData.position = 0;        
        err = notify_getData(&settings, &frameData, &data);
        if (err != 0)
        {
          printk("Error %d\n",err);
          printk(err_toString(err)); //doesnt work when IGNORE_MALLOC
          printk("\n");
          printk("Invalid data received!\n");
          //reply_clear(&data);
          bb_empty(&frameData);
          reply_clear(&data);
          //bb_empty(&data.data);
          break;          
        }
        else
        {
          if (data.complete)
          {
            bb_empty(&frameData);
            if (data.moreData == DLMS_DATA_REQUEST_TYPES_NONE)
            {
              static dlmsVARIANT * tmp;
              static gxObject *item;
              static uint16_t pos;
              static char ln[20];
              //printk("Time Unix Epoch: %lu\n",data.time);
              notify_parsePush(&settings, data.dataValue.Arr, &items);              
              Smart_Meter_data = Smart_Meter_data_init; //Init the Target Data Structure
              new_data_bitmask[0] = 0x0; //Init the new_data_bitmask 
              for (pos = 0; pos != settings.objects.size; ++pos)
              {
                  oa_getByIndex(&settings.objects,pos,&item);
                  snprintk(ln,sizeof(ln)-1,"%u.%u.%u.%u.%u.%u",item->logicalName[0],item->logicalName[1],item->logicalName[2],item->logicalName[3],item->logicalName[4],item->logicalName[5]);
                  //printk("LN: %u.%u.%u.%u.%u.%u\n",item->logicalName[0],item->logicalName[1],item->logicalName[2],item->logicalName[3],item->logicalName[4],item->logicalName[5]);
                  if (strcmp(ln,"1.0.31.7.0.255") == 0)
                  {
                    va_getByIndex(data.dataValue.Arr,pos+1,&tmp);
                    //printk("Strom L1: %u\n",tmp->uiVal);
                    Smart_Meter_data.Strom_L1 = tmp->uiVal;
                    new_data_bitmask[0] |= 1 << 0;
                  }
                  if (strcmp(ln,"1.0.51.7.0.255") == 0)
                  {
                    va_getByIndex(data.dataValue.Arr,pos+1,&tmp);
                    //printk("Strom L2: %u\n",tmp->uiVal);
                    Smart_Meter_data.Strom_L2 = tmp->uiVal;
                    new_data_bitmask[0] |= 1 << 1;
                  }
                  if (strcmp(ln,"1.0.71.7.0.255") == 0)
                  {
                    va_getByIndex(data.dataValue.Arr,pos+1,&tmp);
                    //printk("Strom L3: %u\n",tmp->uiVal);
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
                  /*
                  if (strcmp(ln,"1.1.5.8.0.255") == 0)
                  {
                    va_getByIndex(data.dataValue.Arr,pos+1,&tmp);
                    printk("Blindenergie +Ri: %lu\n",tmp->uiVal);
                    Smart_Meter_data.BlindenergiebezugRi = tmp->uiVal;
                    new_data_bitmask[0] |= 1 << 4;
                  }
                  if (strcmp(ln,"1.1.8.8.0.255") == 0)
                  {
                    va_getByIndex(data.dataValue.Arr,pos+1,&tmp);
                    printk("Blindenergie -Rc: %lu\n",tmp->uiVal);
                    Smart_Meter_data.BlindenergiebezugRc = tmp->uiVal;
                    new_data_bitmask[0] |= 1 << 5;
                  } 
                  */
                  if (strcmp(ln,"1.1.1.8.1.255") == 0)
                  {
                    va_getByIndex(data.dataValue.Arr,pos+1,&tmp);
                    //printk("Wirkenergiebezug Tarif 1: %lu\n",tmp->ulVal);
                    Smart_Meter_data.Wirkenergiebezug_Tarif_1 = tmp->ulVal;
                    new_data_bitmask[0] |= 1 << 4;
                  } 
                  if (strcmp(ln,"1.1.1.8.2.255") == 0)
                  {
                    va_getByIndex(data.dataValue.Arr,pos+1,&tmp);
                    //printk("Wirkenergiebezug Tarif 2: %lu\n",tmp->ulVal);
                    Smart_Meter_data.Wirkenergiebezug_Tarif_2 = tmp->ulVal;
                    new_data_bitmask[0] |= 1 << 5;
                  }                                                   
              }              
              cl_clear(&settings);
              cl_init(&settings, true, 13311, 1, DLMS_AUTHENTICATION_NONE, NULL, DLMS_INTERFACE_TYPE_HDLC);              
              bb_empty(&frameData);
              reply_clear(&data);
              //bb_empty(&data.data);
              arr_clear(&items);
              gpio_pin_toggle_dt(&led_green);
              done = true;
              break;
            }
          }
        }
        //Get next Frame
        frame_start = NULL;
        for (size_t i = pos+frame_size; i < bytes_read; i++)
        {
          if (buf[i] == delim)
          {
            frame_start = &buf[i];
            pos = i;
            break;
          }        
        }
      }
    //Clear Buffer
    bb_empty(&frameData);
    //bb_empty(&data.data);
    reply_clear(&data);
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

//Test
#include <hal/nrf_uarte.h>

void main(void)
{
  NRF_UARTE0->CONFIG = NRF_UARTE_PARITY_INCLUDED;
  printk("Init Application\n");
  printk("Config: %u\n",NRF_UARTE0->CONFIG);
  printk("Baud: %u\n",NRF_UARTE0->BAUDRATE);
  NRF_UARTE0->CONFIG = NRF_UARTE_PARITY_INCLUDED;
  init_mbus_comp_gpiote();  
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
