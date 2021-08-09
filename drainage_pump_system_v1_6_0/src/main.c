#include "bm_blemesh.h"
#include "bm_simple_buttons_and_leds.h"
#include <zephyr.h>
#include <sys/reboot.h>
#include <bm_draniage_system.h>

/**@brief For Reseting the System
 */
void reset(){
  printk("Reboot now!\n");
  sys_reboot(SYS_REBOOT_COLD);
}

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
  //Init Reset Buttons
  bm_init_buttons(reset);
  // Start Mesh Operation
  bm_blemesh_enable(); // Will return faster than the Stack is realy ready... keep on waiting in the transition.

  while(true){
    bm_drainage_stateMachine();
    k_sleep(K_MSEC(1000));
  }

}