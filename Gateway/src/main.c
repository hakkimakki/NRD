#include <zephyr.h>
#include <bm_gsm_modem.h>

/**@brief Function for application main entry.
 */
void main(void)
{
  // Start Application
  printk("Starting Application...\n");

  bm_gsm_modem_init();

  //bm_gsm_modem_reset();


  k_sleep(K_MSEC(60000));
  
  
}