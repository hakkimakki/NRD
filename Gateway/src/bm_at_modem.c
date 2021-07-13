/* Uses AT-Interface to send data over UDP, resolve dns and send a sms in regular intervalls */

#include <zephyr.h>
#include <device.h>
#include <drivers/uart.h>
#include <sys/printk.h>
#include <../drivers/modem/modem_receiver.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(bm_at_modem);

#define MODEM_UART_DEV_NAME "UART_1"
#define RX_BUF_LEN 255
#define TX_BUF_LEN 255

struct mdm_receiver_context ctx;

uint8_t rx_buf[RX_BUF_LEN];
size_t rx_len = RX_BUF_LEN;

uint8_t tx_buf[TX_BUF_LEN];
size_t tx_len = TX_BUF_LEN;

struct uart_config uart_conf = {
	.baudrate = 115200,
	.parity = UART_CFG_PARITY_NONE,
	.stop_bits = UART_CFG_STOP_BITS_1,
	.data_bits = UART_CFG_DATA_BITS_8,
	.flow_ctrl = UART_CFG_FLOW_CTRL_NONE};

void bm_at_modem_send_cmd(const char *cmd)
{
	static int ret;
	static size_t bytes_read;
	strcpy(tx_buf, cmd);
	if (!ring_buf_is_empty(&ctx.rx_rb))
	{
		ring_buf_reset(&ctx.rx_rb);
	}
	ret = mdm_receiver_send(&ctx, tx_buf, strlen(tx_buf));
	k_sleep(K_MSEC(1000));
	mdm_receiver_recv(&ctx, rx_buf, rx_len, &bytes_read);
	if (bytes_read > 0)
	{
		rx_buf[bytes_read] = '\0';
		LOG_DBG("%s", log_strdup((char *)rx_buf));
	}
}

/**
 * @brief  Send a SMS "Status" to 444 
 *
 * @note   To keep PrePaid Mobile NUmber Active Should be called once a month. Also usefull to inspect used Data Volume. 
 */
void bm_at_modem_send_status_sms()
{
	bm_at_modem_send_cmd("AT+CSMS=0\r\0");
	bm_at_modem_send_cmd("AT+CMGF=1\r\0");
	bm_at_modem_send_cmd("AT+CMGS=\"444\"\r\0");
	bm_at_modem_send_cmd("Status\x1A\0");
	k_sleep(K_MSEC(3000));
	bm_at_modem_send_cmd("AT+CMGRD=1\r\0");
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

	ret = mdm_receiver_register(&ctx, MODEM_UART_DEV_NAME, rx_buf, rx_len);
	LOG_DBG("Init AT Modem returned code: %d", ret);


	bm_at_modem_send_status_sms();


/*
	while (true)
	{
		bm_at_modem_send_cmd("AT+CICCID\r\0");
		//k_sleep(K_MSEC(3000));
	}*/	
}
