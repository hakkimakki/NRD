#include <zephyr.h>
#include <bm_simple_buttons_and_leds.h>
#include <bm_at_modem.h>
#include <bm_influxdb.h>


/**@brief Function for application main entry.
 */
void main(void)
{
  // Start Application
  printk("Starting Application...\n");

  bm_init_leds();
  bm_init_switch();

  begin_meas("test_name","test_field_key",42,sizeof(42),k_uptime_get());
  add_fieldset("test_2_filedkey",666,sizeof(666));
  add_tagset("test_tag_key_1","hoi");
  add_tagset("test_tag_key_2","sali");
  end_meas();

  

  //bm_at_modem_init();
  
  
}