#include "bm_config.h"
#include "bm_blemesh.h"
#include "bm_simple_buttons_and_leds.h"
#include "bm_sht3x.h"
#include "bm_lora.h"
#include <zephyr.h>

#include <drivers/sensor.h>

struct sensor_value temp;
struct sensor_value hum;

struct LORA_PDU
{
	double temp;
	double hum;
} __attribute__((packed)) lora_pdu; // Attribute informing compiler to pack all members to 8bits or 1byte



/**@brief Function for application main entry.
 */
void main(void)
{
  // Start Application
  printk("Starting Application...\n");
  // Init MAC Address
  uint32_t LSB_MAC_Address = NRF_FICR->DEVICEADDR[0];
  printk("Preprogrammed Randomly Static MAC-Address (LSB): 0x%x, %u \n", LSB_MAC_Address, LSB_MAC_Address);
  /* --------------- Init Board ------------*/
  printk("Init Buttons and LEDs...\n");
  bm_init_leds();
  printk("Buttons and LEDs initialized\n");
  printk("Init SHT3xd Sensor\n");
  sht3x_init();
  printk("Init LoRa\n");
  bm_lora_init();

  /* ===================================*/

  // Start Mesh Operation
  bm_blemesh_enable(); // Will return faster than the Stack is realy ready... keep on waiting in the transition.

  // Read out Sensor Values and Publish them over Lora
  while (true)
  {

   sht3x_temp_hum_get(&temp,&hum);

   lora_pdu.temp = sensor_value_to_double(&temp);
   lora_pdu.hum = sensor_value_to_double(&hum);

   bm_lora_send(&lora_pdu,sizeof(lora_pdu));

		k_sleep(K_MSEC(30000));
  }
}