#include <zephyr.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <szl_usb_cdc_acm.h>
#include <szl_lora.h>
#include <szl_leb128.h>

//Data structure
struct Smart_Meter_data_t {
    uint16_t Strom_L1;
    uint16_t Strom_L2;
    uint16_t Strom_L3;
    uint32_t Wirkleistungsbezug;
    uint32_t Wirkenergiebezug_Tarif_1;
    uint32_t Wirkenergiebezug_Tarif_2;
};

const struct Smart_Meter_data_t Smart_Meter_data_init;
struct Smart_Meter_data_t Smart_Meter_data;
uint8_t new_data_bitmask[1];  


/**@brief Function for application main entry.
 */
void main(void)
{
  //Init USB CDC ACM
  szl_init_usb_cdc_acm();
  // Start Application
  printk("Starting Application...\n");
  //Init LoRa
  szl_lora_init();
  while (1)
  {
    static uint8_t buffer[255];
    static uint8_t buf_size;
    // Wait for the Receive LoRa
    buf_size = szl_lora_recv(buffer);
    printk("Received len: %u\n",buf_size);
    printk("Received : %u\n",buffer[0]);
    printk("Received : %u\n",buffer[1]);
    printk("Received : %u\n",buffer[2]);
    //Decode Message 
    Smart_Meter_data = Smart_Meter_data_init;   
    static int pos;
    pos = 0;
    pos += szl_decode_uleb128(&buffer[pos],&new_data_bitmask[0]);
    printk("Bitmask: %u\n",new_data_bitmask[0]);
    if (new_data_bitmask[0] & (1 << 0))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Strom_L1);
    }
    if (new_data_bitmask[0] & (1 << 1))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Strom_L2);
    }
    if (new_data_bitmask[0] & (1 << 2))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Strom_L3);
    }
    if (new_data_bitmask[0] & (1 << 3))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Wirkleistungsbezug);
    }
    if (new_data_bitmask[0] & (1 << 4))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Wirkenergiebezug_Tarif_1);
    }
    if (new_data_bitmask[0] & (1 << 5))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Wirkenergiebezug_Tarif_2);
    } 
    printk("Message Decoded Size: %u\n",pos); 
    printk("Current L3: %u\n",Smart_Meter_data.Strom_L3);  
    
    break; //Testmode  
    printk("Done\n");  
  }
  
}