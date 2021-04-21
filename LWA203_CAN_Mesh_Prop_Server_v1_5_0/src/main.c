#include "bm_config.h"
#include "bm_blemesh.h"
#include "bm_simple_buttons_and_leds.h"
#include <zephyr.h>

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



	/* ===================================*/

  // Start Mesh Operation
  bm_blemesh_enable(); // Will return faster than the Stack is realy ready... keep on waiting in the transition.

  bm_led0_set(true);

  k_sleep(K_MSEC(500));

  bm_led0_set(false);




}