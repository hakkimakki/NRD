#include "bm_config.h"
#include "bm_blemesh.h"
#include "bm_simple_buttons_and_leds.h"
#include <zephyr.h>



/*
 * Class A LoRaWAN sample application
 *
 * Copyright (c) 2020 Manivannan Sadhasivam <mani@kernel.org>
 *
 * Modified by Primal Cortex -> https://primalcortex.wordpress.com/2020/11/17/a-zephyr-rtos-based-ttn-lorawan-node/
 *            - Enabled OTAA
 *            - Enabled ADR
 *            - Enable packet send after duty cycle restrition
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define   OTAA              // Enables OTAA. Comment out and enable line below for ABP.
//#define ABP

#include <lorawan/lorawan.h>
#include <drivers/lora.h>

#define DEFAULT_RADIO_NODE DT_ALIAS(lora0)
BUILD_ASSERT(DT_NODE_HAS_STATUS(DEFAULT_RADIO_NODE, okay),
	     "No default LoRa radio specified in DT");
#define DEFAULT_RADIO DT_LABEL(DEFAULT_RADIO_NODE)

/* Customize based on network configuration */
// OTAA
#ifdef OTAA
#define LORAWAN_DEV_EUI			{ 0xAD, 0xD9, 0x13, 0xFC, 0x0E, 0x98, 0x66, 0x00 }    // LSB Format!
#define LORAWAN_JOIN_EUI		{ 0xBB, 0x1B, 0x04, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 }
#define LORAWAN_APP_KEY         { 0x8C, 0x16, 0x24, 0x92, 0x1E, 0xF5, 0xAF, 0x7B, 0xD9, 0x30, 0x22, 0xEF, 0xA7, 0x21, 0x4F, 0xD9 }
#endif

// ABP
#ifdef ABP
#define LORAWAN_DEV_ADDR        { 0x00, 0x00, 0x00, 0x00 }
#define LORAWAN_NWK_SKEY        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
#define LORAWAN_APP_SKEY        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD0, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
#define LORAWAN_APP_EUI         { 0x00, 0x00, 0x00, 0x00, 0xD0, 0x00, 0x00, 0x00 }
#endif

#define DELAY K_MSEC(10000)

char data[] = {'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd','f','r','o','z','e','p','h','y','r'};

/* size of stack area used by each thread */
#define STACKSIZE 1024

/* scheduling priority used by each thread */
#define PRIORITY 7

//#define LED0_NODE DT_ALIAS(led0)
//#define LED1_NODE DT_ALIAS(led1)



/**@brief Function for application main entry.
 */
void main(void) {
  // Start Application
  printk("Starting Application...\n");
  // Init MAC Address
  uint32_t LSB_MAC_Address = NRF_FICR->DEVICEADDR[0];
  printk("Preprogrammed Randomly Static MAC-Address (LSB): 0x%x, %u \n", LSB_MAC_Address, LSB_MAC_Address);
  /* --------------- Init Board ------------*/
	printk("Init Buttons and LEDs...\n");
	bm_init_leds();
	printk("Buttons and LEDs initialized\n");
  printk("Init SHT3xd Sensor\n");

	/* ===================================*/

  // Start Mesh Operation
  bm_blemesh_enable(); // Will return faster than the Stack is realy ready... keep on waiting in the transition.


  	const struct device *lora_dev;
	struct lorawan_join_config join_cfg;
#ifdef OTAA
	uint8_t dev_eui[] = LORAWAN_DEV_EUI;
	uint8_t join_eui[] = LORAWAN_JOIN_EUI;
	uint8_t app_key[] = LORAWAN_APP_KEY;
#endif

#ifdef ABP
    uint8_t dev_addr[] = LORAWAN_DEV_ADDR;
    uint8_t nwk_skey[] = LORAWAN_NWK_SKEY;
    uint8_t app_skey[] = LORAWAN_APP_SKEY;
    uint8_t app_eui[]  = LORAWAN_APP_EUI;
#endif
	int ret;

    printk("Starting up Lora node...\n\n");

	lora_dev = device_get_binding(DEFAULT_RADIO);
	if (!lora_dev) {
        printk("Lora default radio not found.\nExiting program.\n");
		return;
	}

	/* LoRa MAC Layer Test */
	uint8_t rx_data[255];
	int16_t rssi;
	int8_t snr;
	lora_recv(lora_dev,rx_data,255,K_FOREVER,&rssi,&snr);

	printk("Data: %x, RSSI %d, SNR %d\n",rx_data[0],rssi,snr);

    printk("Starting Lorawan stack...\n");
	ret = lorawan_start();
	if (ret < 0) {
		printk("lorawan_start failed: %d\n\n", ret);
		return;
	}


    // Enable ADR
    lorawan_enable_adr( true );

#ifdef OTAA
	join_cfg.mode = LORAWAN_CLASS_A;
	join_cfg.dev_eui = dev_eui;
	join_cfg.otaa.join_eui = join_eui;
	join_cfg.otaa.app_key = app_key;
	join_cfg.otaa.nwk_key = app_key;
#endif

#ifdef ABP
    join_cfg.mode = LORAWAN_ACT_ABP;
    join_cfg.dev_eui = dev_addr;
    join_cfg.abp.dev_addr = dev_addr;
    join_cfg.abp.app_skey = app_skey;
    join_cfg.abp.nwk_skey = nwk_skey;
    join_cfg.abp.app_eui  = app_eui;
#endif


	printk("Joining TTN network over");
#ifdef OTAA
    printk(" OTTA\n\n\n");
#else
    printk(" ABP\n\n\n");
#endif
	ret = lorawan_join(&join_cfg);
	if (ret < 0) {
		printk("lorawan_join_network failed: %d\n\n", ret);
		bm_led0_set(true);
		return;
	} else {
		bm_led3_set(true);
	}

	printk("Sending data...\n\n");

	while (1) {
		ret = lorawan_send(2, data, sizeof(data), LORAWAN_MSG_CONFIRMED);

		if (ret == -EAGAIN) {
			k_sleep(DELAY);
			continue;
		}

		if (ret < 0) {
			k_sleep(DELAY);
			continue;
		}

		printk("Data sent!\n\n");
		k_sleep(DELAY);
	}




}