/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

/** @file
 *  @brief Nordic mesh sensor observer sample
 */
#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh/models.h>
#include <bluetooth/mesh/dk_prov.h>
#include <dk_buttons_and_leds.h>
#include "bm_blemesh.h"
#include "bm_lora.h"
#include "bm_simple_buttons_and_leds.h"


#include <drivers/sensor.h>

struct LORA_PDU
{
  struct sensor_value temp;
  struct sensor_value hum;
} __attribute__((packed)) lora_pdu; // Attribute informing compiler to pack all members to 8bits or 1byte



void main(void)
{
	bm_blemesh_enable();

	//bm_led0_set(true);


	
	bm_lora_init();

	while (true)
	{
		bm_lora_recv(&lora_pdu);
		printk("BEGIN %s NRD/lora/keller/temp\n",bt_mesh_sensor_ch_str_real(&lora_pdu.temp));
		printk("BEGIN %s NRD/lora/keller/hum\n",bt_mesh_sensor_ch_str_real(&lora_pdu.hum));
	}

	
	

}
