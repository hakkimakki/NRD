/*
This file is part of Bluetooth-Benchamrk.

Bluetooth-Benchamrk is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Bluetooth-Benchamrk is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Bluetooth-Benchamrk.  If not, see <http://www.gnu.org/licenses/>.
*/

/* AUTHOR 	 :    Raffael Anklin       */

/* Pin Assigments: 

| Port.Pin 	| Description
|	P1.10	|	Switch ON/OFF
|	P1.13	|	Signal from Host (1=ON/0=OFF)
|	P1.15	|	Switch Pulse from Host (1s High for Active Switching)

*/


#include "bm_config.h"
#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh/models.h>
#include <drivers/hwinfo.h>
#include "bm_blemesh_model_handler.h"
#include "bm_blemesh.h"
#include <bluetooth/mesh/main.h>
#include "bm_simple_buttons_and_leds.h"



static bool initialized=false; // Flag if the Stack is initialized

static void prov_complete(uint16_t net_idx, uint16_t src)
{
	printk("Prov complete! Addr: 0x%04x\n", src);
}

static void prov_reset(void)
{
	bt_mesh_prov_enable(BT_MESH_PROV_ADV | BT_MESH_PROV_GATT);
}

static int input(bt_mesh_input_action_t act, uint8_t size)
{
	printk("Press a button to set the right number.");
	return 0;
}

static void input_complete(void)
{
	printk("Input Complete");
}

static int output_number(bt_mesh_output_action_t action, uint32_t number)
{
	if (action == BT_MESH_DISPLAY_NUMBER) {
		printk("OOB Number: %u\n", number);
		return 0;
	}

	if (action == BT_MESH_BLINK) {
		printk("Blinking %u times", number);
		return 0;
	}

	return -ENOTSUP;
}

static int output_string(const char *string)
{
	printk("OOB String: %s\n", string);
	return 0;
}

static uint8_t dev_uuid[16];

static struct bt_mesh_prov prov = {
	.uuid = dev_uuid,
	.output_size = 1,
	.output_actions = (0),
	.output_number = output_number,
	.output_string = output_string,
	.input_size = 1,
	.input = input,
	.complete = prov_complete,
	.input_complete = input_complete,
	.reset = prov_reset
	};

// Init the rest while Bluetooth is enabled
static void bt_ready(int err){

	/* --------------- Init Board ------------*/
	printk("Init Buttons and LEDs...\n");
	
	printk("Buttons and LEDs initialized\n");
	/* ===================================*/
	
	/* --------------- Init Mesh ------------*/
	printk("Init Mesh...\n");
	
	hwinfo_get_device_id(dev_uuid, sizeof(dev_uuid));
	// Do catch for nrf53 -> no HWINFO set (0xFFFF)
	if (dev_uuid[0] == 0xFF && dev_uuid[1] == 0xFF && dev_uuid[5] == 0xFF){
		uint8_t *p0 = (uint8_t*)&NRF_FICR->DEVICEADDR[0]; // Use MAC Address for UUID
		dev_uuid[0] = p0[0];
		dev_uuid[1] = p0[1];
		dev_uuid[2] = p0[2];
		dev_uuid[3] = p0[3];
		uint8_t *p1 = (uint8_t*)&NRF_FICR->DEVICEADDR[1]; // Use MAC Address for UUID
		dev_uuid[4] = p1[0];
		dev_uuid[5] = p1[1];
	}

	err = bt_mesh_init(&prov, bm_blemesh_model_handler_init());
	if (err)
	{
		printk("Initializing mesh failed (err %d)\n", err);
		return;
	}
	printk("Mesh initialized\n");
	/* ===================================*/

	/* ------------- Provisioning ------------*/
	printk("Provisioning...\n");
	if (IS_ENABLED(CONFIG_SETTINGS))
	{
		settings_load();
	}
	/* 
	err = bt_mesh_provision(net_key, net_idx, flags, iv_index, addr,
							dev_key);
	*/
	/* This will be a no-op if settings_load() loaded provisioning info */
	err = bt_mesh_prov_enable(BT_MESH_PROV_ADV | BT_MESH_PROV_GATT);
	if (err == -EALREADY)
	{
		printk("Already Provisioned (Restored Settings)\n");
	}
	else if (err)
	{
		printk("Provisioning failed (err %d)\n", err);
		return;
	}
	else
	{
		printk("Provisioning completed\n");
	}
	/* ===================================*/

	initialized = true;
}

void bm_blemesh_enable(void)
{
	int err;

	/* ---------- Init Bluetooth ---------- */
	printk("Enabling Bluetooth...\n");
	err = bt_enable(bt_ready);
	while (initialized == false){
		k_sleep(K_MSEC(10));
	}
	if (err)
	{
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	} 
	printk("Bluetooth initialized\n");
	/* =====================================*/

	
	//bm_sleep(bm_rand_32 % 5000); // Sleep Random Time for LPN Activation
	/*
	bt_mesh_cfg_friend_set(net_idx,addr,false,&stat);
	printk("Err Code: %d\n", stat);
	bt_mesh_lpn_set(true); // Enable Low Power Node
	*/	
	printk("Configuring done\n");

	//bm_led0_set(true); // Signal that the Configuring was sucessfull
	/* ===================================*/	
}
