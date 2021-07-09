#include <zephyr.h>
#include <sys/printk.h>
#include <drivers/uart.h>
#include <net/net_mgmt.h>
#include <net/net_event.h>
#include <net/net_conn_mgr.h>
#include <drivers/gsm_ppp.h>

#include <drivers/../../drivers/modem/modem_cmd_handler.h>

static const struct device *gsm_dev;
struct gsm_modem *gsm;
/*
static const struct device *uart_dev;
static const struct uart_config uart_conf = {
		.baudrate = 115200,
		.data_bits = UART_CFG_DATA_BITS_8,
		.stop_bits = UART_CFG_STOP_BITS_1,
		.parity = UART_CFG_PARITY_NONE,
		.flow_ctrl = UART_CFG_FLOW_CTRL_NONE
	};
static const uint8_t tst = 64;
*/
static struct net_mgmt_event_callback mgmt_cb;
static bool connected;
static bool starting = true;

static void event_handler(struct net_mgmt_event_callback *cb,
						  uint32_t mgmt_event, struct net_if *iface)
{
	if ((mgmt_event & (NET_EVENT_L4_CONNECTED | NET_EVENT_L4_DISCONNECTED)) != mgmt_event)
	{
		return;
	}

	starting = false;

	if (mgmt_event == NET_EVENT_L4_CONNECTED)
	{
		printk("Network connected");
		connected = true;
		return;
	}

	if (mgmt_event == NET_EVENT_L4_DISCONNECTED)
	{
		printk("Network disconnected");
		connected = false;
		return;
	}
}

void bm_gsm_modem_reset()
{

	//Reset Funktion
	int ret;
	ret = modem_cmd_send_nolock(&gsm->context.iface,
								&gsm->context.cmd_handler,
								NULL, 0, "AT+COPS=0,0",
								&gsm->sem_response,
								GSM_CMD_AT_TIMEOUT);

	printk("Returnd %d\n",ret);
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

	gsm_ppp_start(gsm_dev);
	//Wait for connected (Event)
}

void bm_gsm_modem_disconnect()
{

	//gsm_ppp_stop(gsm_dev);
	//Wait for disconnected (Event)
}

void bm_gsm_modem_init()
{
	/*
    uart_dev = device_get_binding(CONFIG_MODEM_GSM_UART_NAME);

	int ret;
	ret = uart_configure(uart_dev,&uart_conf);
	printk("Returned %d", ret);

	*/

	gsm_dev = device_get_binding(GSM_MODEM_DEVICE_NAME);
	gsm = gsm_dev->data;
	// Init has been done on Kernel Startup of UART Driver etc..

	net_mgmt_init_event_callback(&mgmt_cb, event_handler,
								 NET_EVENT_L4_CONNECTED |
									 NET_EVENT_L4_DISCONNECTED);
	net_mgmt_add_event_callback(&mgmt_cb);
}
