#include <zephyr.h>
#include <bm_simple_buttons_and_leds.h>
#include <bm_gsm_modem.h>


/**@brief Function for application main entry.
 */
void main(void)
{
  // Start Application
  printk("Starting Application...\n");

  bm_init_leds();
  bm_init_switch();

  bm_at_modem_init();
  
  
}