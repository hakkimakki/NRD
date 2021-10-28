/** @file
 * @brief USB CDC ACM
 *
 * Enables Console Output over USB CDC ACM
 */

/*
 * Copyright (c) 2021 Raffael Anklin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>

#include <usb/usb_device.h>
 
/* Enables Console Output over USB CDC ACM */
void szl_init_usb_cdc_acm(){
	usb_enable(NULL);
	return;
}
