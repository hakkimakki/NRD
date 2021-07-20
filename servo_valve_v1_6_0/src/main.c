#include "bm_blemesh.h"
#include "bm_simple_buttons_and_leds.h"
#include <zephyr.h>
#include <bm_servo.h>

/**@brief Function for application main entry.
 */
void main(void) {
  // Start Application
  printk("Starting Application...\n");
  // Init MAC Address
  uint32_t LSB_MAC_Address = NRF_FICR->DEVICEADDR[0];
  printk("Preprogrammed Randomly Static MAC-Address (LSB): 0x%x, %u \n", LSB_MAC_Address, LSB_MAC_Address);
  // Init Leds
  bm_init_leds();
  // Start Mesh Operation
  bm_blemesh_enable(); // Will return faster than the Stack is realy ready... keep on waiting in the transition.

  bm_init_servo();

  do_test();

}