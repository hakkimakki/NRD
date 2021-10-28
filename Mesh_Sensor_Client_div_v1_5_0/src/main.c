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

#include <szl_usb_cdc_acm.h>

#include <drivers/sensor.h>

#include <stdio.h>

struct LORA_PDU
{
	double temp;
	double hum;
} __attribute__((packed)) lora_pdu; // Attribute informing compiler to pack all members to 8bits or 1byte

void main(void)
{
	szl_init_usb_cdc_acm();

	bm_blemesh_enable();

	bm_lora_init();

	while (true)
	{
		if (bm_lora_recv(&lora_pdu) > 0)
		{
			printf("BEGIN %0.2f NRD/lora/keller/temp\n", lora_pdu.temp);
			printf("BEGIN %0.2f NRD/lora/keller/hum\n", lora_pdu.hum);
		};
	}
}
