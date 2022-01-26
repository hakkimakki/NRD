#include <zephyr.h>

#include <szl_uart.h>
#ifdef SZL_USB_CDC_ACM_ENABLE
#include <szl_usb_cdc_acm.h>
#endif
#include <szl_lora.h>
#include <szl_leb128.h>

#include <stdio.h>
#include <string.h>
#include <sys/util.h>

#include <App_LGe450_Push_Parser.h>


#define UART_DEV_NAME "UART_1"
#define RX_BUF_LEN 1024
static struct szl_uart_context ctx;
static uint8_t rx_buf[RX_BUF_LEN];
struct k_work_delayable parse_push_work;
void *parser;

const struct Smart_Meter_data_t Smart_Meter_data_init;
struct Smart_Meter_data_t Smart_Meter_data;
uint8_t new_data_bitmask[1]; 
uint8_t buffer[255];
uint8_t pos;

/* size of stack area used by each thread */
#define STACKSIZE_UART_RX 1024

/* scheduling priority used by each thread */
#define PRIORITY_UART_RX 7


//Parser DOne Semaphore
struct k_sem parser_done_sem;
K_SEM_DEFINE(parser_done_sem, 0, 1);




/* -------------------------- DLMS Parser Area --------------------------  */

/**@brief Function to parse a push Message. Called by the delayable work item.
 */


void parse_push(struct k_work *work)
{
  static size_t bytes_read;
  //szl_uart_recv(&ctx, rx_buf, RX_BUF_LEN, &bytes_read);
  
  //Convert to Hex String
  static char raw_bin_data[] = {
  126, 160, 132, 206, 255,   3,  19,  18, 
  139, 230, 231,   0, 224,  64,   0,   1, 
    0,   0, 112,  15,   0,   1, 211, 118, 
  12,   7, 229,   6,  28,   1,  15,  27, 
  50, 255, 128,   0,   0,   2,  14,   1, 
  14,   2,   4,  18,   0,  40,   9,   6, 
    0,   8,  25,   9,   0, 255,  15,   2, 
  18,   0,   0,   2,   4,  18,   0,  40, 
    9,   6,   0,   8,  25,   9,   0, 255, 
  15,   1,  18,   0,   0,   2,   4,  18, 
    0,   1,   9,   6,   0,   0,  96,   1, 
    0, 255,  15,   2,  18,   0,   0,   2, 
    4,  18,   0,   3,   9,   6,   1,   0, 
    1,   7,   0, 255,  15,   2,  18,   0, 
    0,   2,   4,  18,   0,   3,   9,   6, 
    1,   0,   2,   7,   0, 255,  15,   2, 
  18,   0,   0, 178,  26, 126, 126, 160, 
  125, 206, 255,   3,  19, 208,  69, 224, 
  64,   0,   2,   0,   0, 108,   2,   4, 
  18,   0,   3,   9,   6,   1,   1,   1, 
    8,   0, 255,  15,   2,  18,   0,   0, 
    2,   4,  18,   0,   3,   9,   6,   1, 
    1,   2,   8,   0, 255,  15,   2,  18, 
    0,   0,   2,   4,  18,   0,   3,   9, 
    6,   1,   1,   5,   8,   0, 255,  15, 
    2,  18,   0,   0,   2,   4,  18,   0, 
    3,   9,   6,   1,   1,   6,   8,   0, 
  255,  15,   2,  18,   0,   0,   2,   4, 
  18,   0,   3,   9,   6,   1,   1,   7, 
    8,   0, 255,  15,   2,  18,   0,   0, 
    2,   4,  18,   0,   3,   9,   6,   1, 
    1,   8,   8,   0, 255,  15,   2,  18, 
    0,   0, 193, 149, 126, 126, 160, 138, 
  206, 255,   3,  19, 170, 234, 224, 192, 
    0,   3,   0,   0, 121,   2,   4,  18, 
    0,   3,   9,   6,   1,   0,  31,   7, 
    0, 255,  15,   2,  18,   0,   0,   2, 
    4,  18,   0,   3,   9,   6,   1,   0, 
  51,   7,   0, 255,  15,   2,  18,   0, 
    0,   2,   4,  18,   0,   3,   9,   6, 
    1,   0,  71,   7,   0, 255,  15,   2, 
  18,   0,   0,   9,   6,   0,   8,  25, 
    9,   0, 255,   9,   8,  53,  54,  53, 
  53,  50,  55,  55,  51,   6,   0,   0, 
    0,  71,   6,   0,   0,   0,   0,   6, 
    0,   3,  67, 242,   6,   0,   0,   0, 
    0,   6,   0,   0,  32, 157,   6,   0, 
    0,   0,   0,   6,   0,   0,   0,   0, 
    6,   0,   1, 160,  34,  18,   0,  36, 
  18,   0,  17,  18,   0,  16,  50,  22, 
  126
  };
  
  static char rx_hex_str[RX_BUF_LEN];
  bin2hex(raw_bin_data,sizeof(raw_bin_data),rx_hex_str,sizeof(rx_hex_str));
  //bin2hex(rx_buf,bytes_read,rx_hex_str,sizeof(rx_hex_str));
  //static char * rx_hex_str = rx_buf;
  //Split into frames
  static char delim[] = "7e";
  static char * frame_start;
  frame_start = strstr(rx_hex_str,delim);
  while (frame_start != NULL)
  {
    //Get Frame Size
    static int frame_size;
    hex2bin(frame_start+sizeof(delim)-1,4,(uint8_t*)&frame_size,sizeof(frame_size));
    frame_size = (frame_size<<8) | (frame_size>>8); //Reverse the byte order
    frame_size = frame_size & 0x0FFF; //Get rid of Type
    frame_size = frame_size + 2; //Append Tag fields size
    frame_size = frame_size * 2; //Addjust for Hex-String
    //Parse the Frame
    printf("Frame:\n%.*s\n", (int)frame_size, frame_start);
    App_LGe450_Push_Parser_parse(parser, frame_start, (unsigned long)frame_size);
    //Get next Frame
    frame_start = strstr(frame_start+(size_t)frame_size,delim);
  }
}

// ------------- UART RX Thread -----------------------

void uart_rx_thread(void)
{
    while (1) {
      // Wait for the Receive semaphore 
      //k_sem_take(&ctx.rx_sem, K_FOREVER); //Testmode
      k_work_reschedule(&parse_push_work, K_MSEC(500));        
      break; //Testmode
    }
}

/* ------------------- Encode and Send ---------------------- */
void encode_send() {
    //Encode Message 
    pos = 0;
    printk("Bitmask: %u\n",new_data_bitmask[0]); 
    pos += szl_encode_uleb128(new_data_bitmask[0],&buffer[pos]);
    if (new_data_bitmask[0] & (1 << 0))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Strom_L1,&buffer[pos]);
    }
    if (new_data_bitmask[0] & (1 << 1))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Strom_L2,&buffer[pos]);
    }
    if (new_data_bitmask[0] & (1 << 2))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Strom_L3,&buffer[pos]);
    }
    if (new_data_bitmask[0] & (1 << 3))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Wirkleistungsbezug,&buffer[pos]);
    }
    if (new_data_bitmask[0] & (1 << 4))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Wirkenergiebezug_Tarif_1,&buffer[pos]);
    }
    if (new_data_bitmask[0] & (1 << 5))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Wirkenergiebezug_Tarif_2,&buffer[pos]);
    } 
    printk("Message Encoded Size: %u\n",pos);   
    //Send LoRa 
    k_sleep(K_MSEC(1000));
    szl_lora_send((uint8_t *)"&buffer[0]", sizeof("&buffer[0]")-1);  
    //szl_lora_send(&buffer[0], (uint32_t) pos+1);
    k_sleep(K_MSEC(1000));
    printk("Buffer Debug[0]: %u\n",buffer[0]); 
    printk("Buffer Debug[1]: %u\n",buffer[1]);
    printk("Buffer Debug[2]: %u\n",buffer[2]);
}




/* -------------------------- Main Area --------------------------  */

/**@brief Function for application main entry.
 */
void main(void)
{
  #ifdef SZL_USB_CDC_ACM_ENABLE
  //Init USB CDC ACM
  szl_init_usb_cdc_acm();
  #endif

  // Start Application
  printk("Starting Application...\n");      

  //Init the Worker
  k_work_init_delayable(&parse_push_work, parse_push);
  
  //Init the Parser
  parser = App_LGe450_Push_Parser_create();

  //Init the UART
  static int ret;
  ret = szl_uart_register(&ctx, UART_DEV_NAME);

  //Init LoRa
  szl_lora_init();

  k_sleep(K_MSEC(1000));

  //szl_lora_send((uint8_t *)"&buffer[0]", sizeof("&buffer[0]")-1);  

  //k_sleep(K_MSEC(10000));

  //encode_send();

  
  
  while (1)
  {
     //Wait for Parser to be done parseing
     k_sem_take(&parser_done_sem, K_FOREVER); 
     //Encode and Send Message
     encode_send();
  }

  
  
}


K_THREAD_DEFINE(uart_rx_thread_id, STACKSIZE_UART_RX, uart_rx_thread, NULL, NULL, NULL,
		PRIORITY_UART_RX, 0, 1000);


