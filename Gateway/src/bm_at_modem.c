/* Uses AT-Interface to send data over UDP, resolve dns and send a sms in regular intervalls */

#include <zephyr.h>
#include <device.h>
#include <drivers/uart.h>
#include <sys/printk.h>
#include <../drivers/modem/modem_receiver.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(bm_at_modem);
#include <stdlib.h>
#include <stdio.h>
#include <bm_simple_buttons_and_leds.h>

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

char ip[15];

/**
 * @brief  Send a AT Cmd and check response
 * 
 * @param cmd AT Command String (AT+...)
 * @param waittime_ms Waittime until checking for rsp_substr in Response Buffer
 * @param rsp_substr Search for this substring in Response after waittime_ms
 * @param reset_modul_on_fail Search for this substring in Response after waittime_ms
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
 * @brief  Reset Modem 
 *
 * @note   Should be done in case of a error and in the beginning
 */
void bm_at_modem_reset()
{
	//Check that Modem is Responding
	static bool OK = false;
	bm_switch_set(false); //Turn Off PWR Key
	while (!OK){
		OK = bm_at_modem_send_cmd("AT\r\0", 1000, "OK");		   //AT
		if (!OK){
			bm_led1_set(!bm_led1_get()); //Toogle Red LED
			bm_switch_set(!bm_switch_get()); //Toogle PWR Key
		}
	}
	bm_switch_set(true); //Turn On PWR Key
	bm_led1_set(false); //Turn off Red LED
	bm_at_modem_send_cmd("AT+CFUN=1,1\r\0", 7000, "SMS Ready");	//Reset Modul
	bm_at_modem_send_cmd("AT+CPIN?\r\0", 1000, "+CPIN:READY");		//Check SIM Status
	bm_at_modem_send_cmd("AT+CSQ\r\0", 1000, "+CSQ:");				//Check RF Signal
	bm_at_modem_send_cmd("AT+CGATT?\r\0", 1000, "+CGATT: 1");		//Check PS service. 1 indicates PS has attached:
	bm_at_modem_send_cmd("AT+COPS?\r\0", 1000, "+COPS:");			//Query Network information, operator and network.
	bm_at_modem_send_cmd("AT+CGNAPN\r\0", 1000, "+CGNAPN: 1");		//Query the APN delivered by the network after the CAT-M or NB-IOT network is successfully registered.
	bm_at_modem_send_cmd("AT+CNACT=0,1\r\0", 5000, "+APP PDP: 0,ACTIVE");	//Activate network, Activate 0th PDP.
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
	bm_at_modem_send_cmd("AT+CMGR=0\r\0", 5000, "+CMGR: \"REC");   //Read SMS
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
 * @brief  DNS Request 
 *
 * @note   Issue a DNS Request
 */
void bm_at_modem_dns_query(const char *domain)
{
	bm_at_modem_send_cmd("AT+CDNSPDPID=0\r\0", 1000, "OK");			//Select PDP Index for DNS
	static char dns_cmd[50];
	strcpy(dns_cmd,  "AT+CDNSGIP=\"");
	strcat(dns_cmd, domain);
	strcat(dns_cmd, "\",1,1000\r\0");
	bm_at_modem_send_cmd(dns_cmd, 5000, "+CDNSGIP: 1");	//DNS Request:
	// Get IP
	static char * begin;
	static char * end;
	begin = strstr((char *)rx_buf, "\",\"");
	end = strstr(begin+3, "\"");
	if ((begin != NULL)  && (end != NULL) && ((end - begin - 3)<=15))
	{
		memcpy(&ip,"\0\0\0\0\0\0\0\0\0\0\0\0\0\0",15); // Reset tmp
		memcpy(&ip, begin + 3,end - begin - 3);
		LOG_DBG("IP: %s", log_strdup((char *)ip));
	} else {
		bm_at_modem_reset();
	}
}


/**
 * @brief  Send UDP Data 
 *
 * @note   Send fixed size UDP Data. Send to Previously Queried IP Address on fixed Port
 */
void bm_at_modem_udp_send(char * data)
{
	bm_at_modem_send_cmd("AT+CNACT?\r\0", 1000, "+CNACT:");			//Check the 0th PDN/PDP local IP
	static char caopen_cmd[50];
	memset(caopen_cmd,0,sizeof(caopen_cmd)); // Reset
	strcpy(caopen_cmd,  "AT+CAOPEN=0,0,\"UDP\",\"");
	strcat(caopen_cmd, ip);
	strcat(caopen_cmd, "\",63521\r\0");
	bm_at_modem_send_cmd(caopen_cmd, 5000, "+CAOPEN: 0,0");	 //Create a UDP connection with 0th PDP on 0th connection.
	memset(caopen_cmd,0,sizeof(caopen_cmd)); // Reset
	strcpy(caopen_cmd,  "AT+CASEND=0,");
	static char num[8];
	memset(num,0,sizeof(num)); // Reset
	sprintf(num,"%d",strlen(data));
	strcat(caopen_cmd, num);
	strcat(caopen_cmd, "\r\0");
	bm_at_modem_send_cmd(caopen_cmd, 1000, "OK");			//Request to send 5 bytes of data
	bm_at_modem_send_cmd(data, 2000, "OK");	 //Create a UDP connection with 0th PDP on 0th connection.
	bm_at_modem_send_cmd("AT+CACLOSE=0\r\0", 1000, "OK");			//Close the connection with an identifier of 0.
	
}




/**
 * @brief  Initialize AT Modem
 *
 * @note   Uses Defined UART Interface. 
 */
void bm_at_modem_init()
{
	static int ret;

	ctx.uart_dev = device_get_binding(MODEM_UART_DEV_NAME);
	ret = uart_configure(ctx.uart_dev, &uart_conf);
	LOG_DBG("Init UART returned code: %d", ret);

	ret = mdm_receiver_register(&ctx, MODEM_UART_DEV_NAME, rx_ring_buf, rx_len);
	LOG_DBG("Init AT Modem returned code: %d", ret);

	bm_at_modem_reset();

	bm_at_modem_dns_query("home.villa28.ch");

	bm_at_modem_send_status_sms();

	bm_at_modem_udp_send("Hoi Du Geili Sau :) @BFF");



}
