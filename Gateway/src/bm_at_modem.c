/* Uses AT-Interface to send data over UDP, resolve dns and send a sms in regular intervalls */

#include <zephyr.h>
#include <device.h>
#include <drivers/uart.h>
#include <sys/printk.h>
#include <../drivers/modem/modem_receiver.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(bm_at_modem);
#include <stdlib.h>

#define MODEM_UART_DEV_NAME "UART_1"
#define RX_BUF_LEN 255
#define TX_BUF_LEN 255

struct mdm_receiver_context ctx;

uint8_t rx_buf[RX_BUF_LEN];
uint8_t rx_ring_buf[RX_BUF_LEN];
size_t rx_len = RX_BUF_LEN;

uint8_t tx_buf[TX_BUF_LEN];
size_t tx_len = TX_BUF_LEN;

struct uart_config uart_conf = {
	.baudrate = 115200,
	.parity = UART_CFG_PARITY_NONE,
	.stop_bits = UART_CFG_STOP_BITS_1,
	.data_bits = UART_CFG_DATA_BITS_8,
	.flow_ctrl = UART_CFG_FLOW_CTRL_NONE};

int Guthaben_Fr;
int Guthaben_Rp;

int Daten_MB;
int Daten_KB;

/**
 * @brief  Send a AT Cmd and check response
 * 
 * @param cmd AT Command String (AT+...)
 * @param waittime_ms Waittime until checking for rsp_substr in Response Buffer
 * @param rsp_substr Search for this substring in Response after waittime_ms
 * 
 * @return 1 if Response Substring was found, otherwise 0 
 * 
 */
bool bm_at_modem_send_cmd(const char *cmd, uint32_t waittime_ms, const char *rsp_substr)
{
	static int ret;
	static size_t bytes_read;
	strcpy(tx_buf, cmd);
	if (!ring_buf_is_empty(&ctx.rx_rb))
	{
		ring_buf_reset(&ctx.rx_rb);
	}
	ret = mdm_receiver_send(&ctx, tx_buf, strlen(tx_buf));
	k_sleep(K_MSEC(waittime_ms));
	mdm_receiver_recv(&ctx, rx_buf, rx_len, &bytes_read);
	if (bytes_read > 0)
	{
		rx_buf[bytes_read] = '\0';
		LOG_DBG("%s", log_strdup((char *)rx_buf));
		if (strstr((char *)rx_buf, rsp_substr) != NULL)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

/**
 * @brief  Send a SMS "Status" to 444 
 *
 * @note   To keep PrePaid Mobile NUmber Active Should be called once a month. Also usefull to inspect used Data Volume. 
 */
void bm_at_modem_send_status_sms()
{
	bm_at_modem_send_cmd("AT+CMGD=0,4\r\0", 1000, "OK");		   //Delete all SMS
	bm_at_modem_send_cmd("AT+CSMS=0\r\0", 1000, "+CSMS: 1,1,1");   //Select message service
	bm_at_modem_send_cmd("AT+CMGF=1\r\0", 1000, "OK");			   // Set SMS Text Mode
	bm_at_modem_send_cmd("AT+CMGS=\"444\"\r\0", 1000, ">");		   //Setup SMS to 444
	bm_at_modem_send_cmd("Status\x1A\0", 3000, "+CMTI: \"SM\",0"); //Send SMS with text Status (CTRL+Z) = \1xA
	bm_at_modem_send_cmd("AT+CMGR=0\r\0", 1000, "+CMGR: \"REC");   //Read SMS
	// Get Guthaben Fr.
	static char * begin;
	static char * middle;
	static char * end;
	begin = strstr((char *)rx_buf, "CHF ");
	middle = strstr(begin, ".");
	end = strstr(middle, ". Daten");
	if ((begin != NULL) && (middle != NULL) && (end != NULL) && ((end - begin - 4)<=10))
	{
		static char substr_tmp[10];
		memcpy(&substr_tmp,"\0\0\0\0\0\0\0\0\0",10); // Reset tmp
		memcpy(&substr_tmp,begin + 4,middle - begin + 4);
		Guthaben_Fr = atoi(substr_tmp);
		memcpy(&substr_tmp,"\0\0\0\0\0\0\0\0\0",10); // Reset tmp
		memcpy(&substr_tmp,middle + 1,end - middle + 1);
		Guthaben_Rp = atoi(substr_tmp) * 10;
	}
	// Get Daten MB
	begin = strstr((char *)rx_buf, "Schweiz: ");
	middle = strstr(begin, ".");
	end = strstr(middle, " MB");
	if ((begin != NULL) && (middle != NULL) && (end != NULL) && ((end - begin - 9)<=10))
	{
		static char substr_tmp[10];
		memcpy(&substr_tmp,"\0\0\0\0\0\0\0\0\0",10); // Reset tmp
		memcpy(&substr_tmp,begin + 9,middle - begin + 9);
		Daten_MB = atoi(substr_tmp);
		memcpy(&substr_tmp,"\0\0\0\0\0\0\0\0\0",10); // Reset tmp
		memcpy(&substr_tmp,middle + 1,end - middle + 1);
		Daten_KB = atoi(substr_tmp);
	}
	bm_at_modem_send_cmd("AT+CMGD=0,4\r\0", 1000, "OK"); //Delete all SMS
	printk("Guthaben: %d.%d CHF\n",Guthaben_Fr,Guthaben_Rp);
	printk("Daten: %d.%d MB\n",Daten_MB,Daten_KB);
}

/**
 * @brief  Initialize AT Modem
 *
 * @note   Uses Defined UART Interface. 
 */
void bm_at_modem_init()
{
	static int ret;
	static size_t bytes_read;

	ctx.uart_dev = device_get_binding(MODEM_UART_DEV_NAME);
	ret = uart_configure(ctx.uart_dev, &uart_conf);
	LOG_DBG("Init UART returned code: %d", ret);

	ret = mdm_receiver_register(&ctx, MODEM_UART_DEV_NAME, rx_ring_buf, rx_len);
	LOG_DBG("Init AT Modem returned code: %d", ret);

	bm_at_modem_send_status_sms();

}
