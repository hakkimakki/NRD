#include <zephyr.h>
#include <bm_simple_buttons_and_leds.h>
#include <bm_at_modem.h>
#include <bm_influxdb.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**@brief Function for application main entry.
 */
void main(void)
{
  // Start Application
  printk("Starting Application...\n");

  bm_init_leds();
  bm_init_switch();

  init_db();

  static int64_t testval = 42;

  static double testval_2 = 666.69;

  static char testval_s[12] = "Hello 1";

static bool test_bool = true;

  static int64_t ts;

  ts = k_uptime_get();

  begin_meas("name_1","field_1",&testval,int_64,&ts);
  add_fieldset("field_2",&testval_s,string);
  add_tagset("tag_1","hoi");
  add_tagset("tag_2","sali");
  end_meas();

  ts = k_uptime_get();

  for (size_t j = 0; j < 255; j++)
  {
   
 

  for (size_t i = 0; i < 250; i++)
  {
    testval_2 = testval_2 + 1;
    ts = k_uptime_get();
    static char num[6];
    sprintf(num,"%u",(uint16_t)i);
    static char field_1[10];
    memset(field_1,0,sizeof(field_1));
    strcat(field_1,"tst_");
    strcat(field_1,num);
    
    begin_meas("name_2",field_1,&test_bool,boolean,&ts);
    add_fieldset("field_2",&testval_2,float_64);
    add_tagset("tag_1","hoi");
    add_tagset("tag_2","sali");
    end_meas();
    
  }
  




  print_all_meas();

  }

  

  

  

  //bm_at_modem_init();
  
  
}