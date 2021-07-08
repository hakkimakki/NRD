#include <zephyr.h>
#include <sys/printk.h>
#include <drivers/uart.h>
#include <net/net_mgmt.h>
#include <net/net_event.h>
#include <net/net_conn_mgr.h>
#include <drivers/gsm_ppp.h>

static const struct device *gsm_dev;
static struct net_mgmt_event_callback mgmt_cb;
static bool connected;
static bool starting = true;

static void event_handler(struct net_mgmt_event_callback *cb,
			  uint32_t mgmt_event, struct net_if *iface)
{
	if ((mgmt_event & (NET_EVENT_L4_CONNECTED
			   | NET_EVENT_L4_DISCONNECTED)) != mgmt_event) {
		return;
	}

	starting = false;

	if (mgmt_event == NET_EVENT_L4_CONNECTED) {
		printk("Network connected");
		connected = true;
		return;
	}

	if (mgmt_event == NET_EVENT_L4_DISCONNECTED) {
		printk("Network disconnected");
		connected = false;
		return;
	}
}

void bm_gsm_modem_connect(){

    gsm_ppp_start(gsm_dev);
    //Wait for connected (Event)


}

void bm_gsm_modem_disconnect(){

    gsm_ppp_stop(gsm_dev);
    //Wait for disconnected (Event)


}


void bm_gsm_modem_init()
{
    const struct device *uart_dev =
				device_get_binding(CONFIG_MODEM_GSM_UART_NAME);

	gsm_dev = device_get_binding(GSM_MODEM_DEVICE_NAME);

    net_mgmt_init_event_callback(&mgmt_cb, event_handler,
				     NET_EVENT_L4_CONNECTED |
				     NET_EVENT_L4_DISCONNECTED);
	net_mgmt_add_event_callback(&mgmt_cb);

}


