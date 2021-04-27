/*
This file is part of Benchamrk-Shared-Library.

Benchamrk-Shared-Library is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Benchamrk-Shared-Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Benchamrk-Shared-Library.  If not, see <http://www.gnu.org/licenses/>.
*/

/* AUTHOR ZEPHYR_BLE_MESH  :   Raffael Anklin        */
/* AUTHOR NRF_SDK_ZIGBEE   :   Cyrill Horath        */


#ifdef __cplusplus
extern "C" {
#endif

#ifndef SIMPLE_BUTTONS_AND_LEDS_H
#define SIMPLE_BUTTONS_AND_LEDS_H


#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <devicetree_unfixed.h>
#include <drivers/gpio.h>
#include <sys/util.h>
#include <sys/slist.h>

/*
 * Devicetree helper macro which gets the 'flags' cell from a 'gpios'
 * property, or returns 0 if the property has no 'flags' cell.
 */

#define FLAGS_OR_ZERO(node)						\
	COND_CODE_1(DT_PHA_HAS_CELL(node, gpios, flags),		\
		    (DT_GPIO_FLAGS(node, gpios)),			\
		    (0))



/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN_LED0	DT_GPIO_PIN(LED0_NODE, gpios)
#if DT_PHA_HAS_CELL(LED0_NODE, gpios, flags)
#define FLAGS_LED0	DT_GPIO_FLAGS(LED0_NODE, gpios)
#endif
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0	""
#define PIN_LED0	0
#endif

#ifndef FLAGS_LED0
#define FLAGS_LED0	0
#endif

/* The devicetree node identifier for the "led1" alias. Is the RED LED on THe nRF52 Donlge*/
#define LED1_NODE DT_ALIAS(led1)

#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
#define LED1	DT_GPIO_LABEL(LED1_NODE, gpios)
#define PIN_LED1	DT_GPIO_PIN(LED1_NODE, gpios)
#if DT_PHA_HAS_CELL(LED1_NODE, gpios, flags)
#define FLAGS_LED1	DT_GPIO_FLAGS(LED1_NODE, gpios)
#endif
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led1 devicetree alias is not defined"
#define LED1	""
#define PIN_LED1	0
#endif

#ifndef FLAGS_LED1
#define FLAGS_LED1	0
#endif


/* The devicetree node identifier for the "led2" alias. Is the GREEN LED on THe nRF52 Donlge*/
#define LED2_NODE DT_ALIAS(led2)

#if DT_NODE_HAS_STATUS(LED2_NODE, okay)
#define LED2	DT_GPIO_LABEL(LED2_NODE, gpios)
#define PIN_LED2	DT_GPIO_PIN(LED2_NODE, gpios)
#if DT_PHA_HAS_CELL(LED2_NODE, gpios, flags)
#define FLAGS_LED2	DT_GPIO_FLAGS(LED2_NODE, gpios)
#endif
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led2 devicetree alias is not defined"
#define LED2	""
#define PIN_LED2	0
#endif

#ifndef FLAGS_LED2
#define FLAGS_LED1	0
#endif

/* The devicetree node identifier for the "led3" alias. Is the BLUE LED on THe nRF52 Donlge*/
#define LED3_NODE DT_ALIAS(led3)

#if DT_NODE_HAS_STATUS(LED3_NODE, okay)
#define LED3	DT_GPIO_LABEL(LED3_NODE, gpios)
#define PIN_LED3	DT_GPIO_PIN(LED3_NODE, gpios)
#if DT_PHA_HAS_CELL(LED3_NODE, gpios, flags)
#define FLAGS_LED3	DT_GPIO_FLAGS(LED3_NODE, gpios)
#endif
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led3 devicetree alias is not defined"
#define LED3	""
#define PIN_LED3	0
#endif

#ifndef FLAGS_LED3
#define FLAGS_LED3	0
#endif


/*
 * Get button configuration from the devicetree sw0 alias.
 *
 * At least a GPIO device and pin number must be provided. The 'flags'
 * cell is optional.
 */

#define SW0_NODE	DT_ALIAS(sw0)

#if DT_NODE_HAS_STATUS(SW0_NODE, okay)
#define SW0_GPIO_LABEL	DT_GPIO_LABEL(SW0_NODE, gpios)
#define SW0_GPIO_PIN	DT_GPIO_PIN(SW0_NODE, gpios)
#define SW0_GPIO_FLAGS	(GPIO_INPUT | FLAGS_OR_ZERO(SW0_NODE) | GPIO_INT_DEBOUNCE)
#else
#error "Unsupported board: sw0 devicetree alias is not defined"
#define SW0_GPIO_LABEL	""
#define SW0_GPIO_PIN	0
#define SW0_GPIO_FLAGS	0
#endif





/**
* Init the Buttons
*
*/
void bm_init_buttons(void (*button0_cb)());

/**
* Init the Signal
*
*/
void bm_init_signal(void (*signal_cb)());

/**
* Init the Pulse
*
*/
void bm_init_pulse(void (*pulse_cb)());


/**
* Get the BUTTON0 Toggled State
*
* @return State of the BUTTON0 Toggled State (0/1)
*/
bool bm_button0_toggle_state_get();

/**
* Set the BUTTON0 Toggled State
*
* @param State of the BUTTON0 Toggled State (0/1)
*/
void bm_button0_toggle_state_set(bool newstate);

/**
* Get the PULSE Toggled State
*
* @return State of the PULSE Toggled State (0/1)
*/
bool bm_pulse_toggle_state_get();

/**
* Set the PULSE Toggled State
*
* @param State of the PULSE Toggled State (0/1)
*/
void bm_pulse_toggle_state_set(bool newstate);

/**
* Get the SIGNAL State
*
* @return State of the SIGNAL State (0/1)
*/
bool bm_signal_state_get();

/**
* Get the SIGNAL Toggled State
*
* @return State of the SIGNAL Toggled State (0/1)
*/
bool bm_signal_toggle_state_get();

/**
* Set the SIGNAL Toggled State
*
* @param State of the SIGNAL Toggled State (0/1)
*/
void bm_signal_toggle_state_set(bool newstate);


/**
* Init the Leds
*
*/
void bm_init_leds();

/**
* Init the Switch
*
*/
void bm_init_switch();

/**
* Set the LED0 State
*
* @param State to set the LED0 to (0/1) (GREEN no RGB on nRF52 Dongle / LED1 on nRF52 DK)
*/
void bm_led0_set(bool state);

/**
* Get the LED0 State
*
* @return State of the LED0 (0/1) (GREEN no RGB on nRF52 Dongle / LED1 on nRF52 DK)
*/
bool bm_led0_get();


/**
* Set the LED1 State
*
* @param State to set the LED1 to (0/1) (RED on nRF52 Dongle / LED2 on nRF52 DK)
*/
void bm_led1_set(bool state);

/**
* Get the LED1 State
*
* @return State of the LED1 (0/1) (RED on nRF52 Dongle / LED2 on nRF52 DK)
*/
bool bm_led1_get();

/**
* Set the LED2 State
*
* @param State to set the LED2 to (0/1) (GREEN on nRF52 Dongle / LED3 on nRF52 DK)
*/
void bm_led2_set(bool state);

/**
* Get the LED2 State
*
* @return State of the LED2 (0/1) (GREEN on nRF52 Dongle / LED3 on nRF52 DK)
*/
bool bm_led2_get();

/**
* Set the LED3 State
*
* @param State to set the LED3 to (0/1) (BLUE on nRF52 Dongle / LED4 on nRF52 DK)
*/
void bm_led3_set(bool state);

/**
* Get the LED3 State
*
* @return State of the LED3 (0/1) (BLUE on nRF52 Dongle / LED4 on nRF52 DK)
*/
bool bm_led3_get();

/**
* Set the Switch State
*
* @param State to set the Switch to (0/1) 
*/
void bm_switch_set(bool state);

/**
* Get the SWITCH State
*
* @return State of the SWITCH (0/1)
*/
bool bm_switch_get();

#endif

#ifdef __cplusplus
}
#endif