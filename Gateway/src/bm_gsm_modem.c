#include <zephyr.h>
#include <device.h>
#include <sys/printk.h>
#include <console/tty.h>

#define RX_BUFFER_SIZE 512
#define TX_BUFFER_SIZE 512
#define UART_DEV_NAME "UART_1"

const struct device *uart_dev;
struct tty_serial* tty_dev;
static uint8_t rx_buf[RX_BUFFER_SIZE];
static uint8_t tx_buf[TX_BUFFER_SIZE];

void bm_gsm_modem_reset()
{

	//Reset Funktion
	//tx_buf = "AT\r";
	tty_write(tty_dev,"AT\r",3);
	//tty_write(tty_dev,tx_buf,TX_BUFFER_SIZE);
	//Wait for connected (Event)
}

void bm_gsm_modem_connect()
{

	//Reset Modul
	//char tx[11] = "AT+CFUN=1,1";
	/*
	char tx[3] = "AT\r";
	int ret;
	
	ret = uart_tx(uart_dev, &tst, 1, SYS_FOREVER_MS);
	printk("Returned %d", ret);
	*/

}

void bm_gsm_modem_disconnect()
{

	//gsm_ppp_stop(gsm_dev);
	//Wait for disconnected (Event)
}

void bm_gsm_modem_init()
{
	uart_dev = device_get_binding(UART_DEV_NAME);
	tty_init(tty_dev,uart_dev);
	//tty_dev->uart_dev = uart_dev;
	//tty_set_rx_buf(tty_dev,rx_buf,RX_BUFFER_SIZE);
	//tty_set_tx_buf(tty_dev,tx_buf,TX_BUFFER_SIZE);

	
}
