#include "bm_simple_buttons_and_leds.h"
#include <zephyr.h>
#include <sys/reboot.h>
#include "../dlms/include/client.h"

#include "../dlms/include/dlmssettings.h"
#include "../dlms/include/variant.h"
#include "../dlms/include/cosem.h"
#include "../dlms/include/server.h"


#include <stdio.h>

static gxClock clock1;
static long started;

long time_current(void)
{
  //Get current time.
  //Because there is no clock, clock object keeps base time and uptime is added to that.
  return time_toUnixTime(&clock1.time.value) + (k_uptime_get() - started) / 1000;
}

long time_elapsed(void)
{
  return k_uptime_get();
}



void time_now(
gxtime* value)
{
  long offset = time_current();
  time_initUnix(value, offset);
}


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
  dlmsSettings settings;
  char hexstring[] = "0F0001D3760C07E5061C010F1B32FF800000020E010E020412002809060008190900FF0F02120000020412002809060008190900FF0F01120000020412000109060000600100FF0F02120000020412000309060100010700FF0F02120000020412000309060100020700FF0F02120000020412000309060101010800FF0F02120000020412000309060101020800FF0F02120000020412000309060101050800FF0F02120000020412000309060101060800FF0F02120000020412000309060101070800FF0F02120000020412000309060101080800FF0F021200000204120003090601001F0700FF0F02120000020412000309060100330700FF0F02120000020412000309060100470700FF0F0212000009060008190900FF090835363535323737330600000047060000000006000343F20600000000060000209D06000000000600000000060001A022120024120011120010";
  char *pos = hexstring;
  unsigned char val[sizeof(hexstring)];

       /* WARNING: no sanitization or error-checking whatsoever */
    for (size_t count = 0; count < sizeof val/sizeof *val; count++) {
        sscanf(pos, "%2hhx", &val[count]);
        pos += 2;
    }

    printf("0x");
    for(size_t count = 0; count < sizeof val/sizeof *val; count++)
        printf("%02x", val[count]);
    printf("\n");

  gxByteBuffer bb;
  bb_attach(&bb,val,sizeof(hexstring),sizeof(hexstring)+10);


  cl_parseObjects(&settings,&bb);
  
}