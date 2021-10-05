#include <zephyr.h>

#include <szl_uart.h>
#include <stdio.h>
#include <string.h>
#include <sys/util.h>
#define UART_DEV_NAME "UART_1"
#define RX_BUF_LEN 1024
static struct szl_uart_context ctx;
static uint8_t rx_buf[RX_BUF_LEN];
struct k_work_delayable parse_push_work;
void *parser;

#include <App_LGe450_Push_Parser.h>

/**@brief Function to parse a push Message. Called by the delayable work item.
 */
void parse_push(struct k_work *work)
{
  static size_t bytes_read;
  szl_uart_recv(&ctx, rx_buf, RX_BUF_LEN, &bytes_read);
  /*
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
  */
  static char rx_hex_str[RX_BUF_LEN];
  //bin2hex(raw_bin_data,sizeof(raw_bin_data),rx_hex_str,sizeof(rx_hex_str));
  bin2hex(rx_buf,bytes_read,rx_hex_str,sizeof(rx_hex_str));
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

/**@brief Function for application main entry.
 */
void main(void)
{
  // Start Application
  printk("Starting Application...\n");

  //DLMS
  //thread_analyzer_print();
  static int ret;
  //Init the Worker
  k_work_init_delayable(&parse_push_work, parse_push);
  //Init the Parser
  parser = App_LGe450_Push_Parser_create();
  //Init the UART
  ret = szl_uart_register(&ctx, UART_DEV_NAME);

  /* Wait for the Receive semaphore */
  while (1)
  {
    k_sem_take(&ctx.rx_sem, K_FOREVER);
    k_work_reschedule(&parse_push_work, K_MSEC(500));
  }
}