/*
This file is part of Bluetooth-Benchamrk.

Bluetooth-Benchamrk is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Bluetooth-Benchamrk is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Bluetooth-Benchamrk.  If not, see <http://www.gnu.org/licenses/>.
*/

/* AUTHOR 	 :    Raffael Anklin       */

/* Pin Assigments: 

| Port.Pin 	| Description
|	P1.10	|	Switch ON/OFF
|	P1.13	|	Signal from Host (1=ON/0=OFF)
|	P1.15	|	Switch Pulse from Host (1s High for Active Switching)

*/

#include "bm_config.h"
#include "bm_simple_buttons_and_leds.h"
#include "bm_blemesh.h"
#include "bm_blemesh_model_handler.h"

#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh/models.h>
#include <bluetooth/mesh/model_types.h>

#define PORT DT_ALIAS_GPIO_1_LABEL
#define Switch_PIN 10
#define Signal_PIN 13
#define Pulse_PIN 15

int64_t last_switch_server;

/** Generic OnOff client definition */
static void status_handler_onoff_cli(struct bt_mesh_onoff_cli *cli,
									 struct bt_mesh_msg_ctx *ctx,
									 const struct bt_mesh_onoff_status *status)
{
}
struct bt_mesh_onoff_cli on_off_cli = BT_MESH_ONOFF_CLI_INIT(&status_handler_onoff_cli);

static void pulse_cb()
{
	//int err;
	if ((k_uptime_get() - last_switch_server) > 1000)
	{
		struct bt_mesh_onoff_set set = {
			.on_off = (bm_signal_state_get()),
		};
		bt_mesh_onoff_cli_set(&on_off_cli, NULL, &set, NULL);

		//printk("Set from Signal State: %d",bm_signal_state_get() );
		bm_led2_set(!bm_led2_get()); // Toggle the Blue LED
	}
}

static void signal_cb()
{
	bm_led1_set(!bm_led1_get()); // Toggle the Red LED
}

/** ON/OFF Server definition */
static void led_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx,
					const struct bt_mesh_onoff_set *set,
					struct bt_mesh_onoff_status *rsp)
{
	// Set DK LED index
	bm_switch_set(set->on_off);
	last_switch_server = k_uptime_get();
}

static void led_get(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx,
					struct bt_mesh_onoff_status *rsp)
{
	// Send respond Status
	rsp->present_on_off = bm_switch_get();
}

static const struct bt_mesh_onoff_srv_handlers onoff_handlers = {
	.set = led_set,
	.get = led_get,
};

static struct bt_mesh_onoff_srv on_off_srv = BT_MESH_ONOFF_SRV_INIT(&onoff_handlers);

/** Health Server definition */
static void attention_on(struct bt_mesh_model *model)
{
	printk("attention_on()\n");
}

static void attention_off(struct bt_mesh_model *model)
{
	printk("attention_off()\n");
}
static const struct bt_mesh_health_srv_cb health_srv_cb = {
	.attn_on = attention_on,
	.attn_off = attention_off,
};

static struct bt_mesh_health_srv health_srv = {
	.cb = &health_srv_cb,
};

BT_MESH_HEALTH_PUB_DEFINE(health_pub, 0);

/* Define all Elements */
static struct bt_mesh_elem elements[] = {
	BT_MESH_ELEM(
		1, BT_MESH_MODEL_LIST(BT_MESH_MODEL_CFG_SRV, BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub), BT_MESH_MODEL_ONOFF_CLI(&on_off_cli), BT_MESH_MODEL_ONOFF_SRV(&on_off_srv)),
		BT_MESH_MODEL_NONE)};

/* Create Composition */
static const struct bt_mesh_comp comp = {
	.cid = CONFIG_BT_COMPANY_ID,
	.elem = elements,
	.elem_count = ARRAY_SIZE(elements),
};

const struct bt_mesh_comp *bm_blemesh_model_handler_init(void)
{
	bm_init_buttons(pulse_cb); // Init Buttons
	bm_init_pulse(pulse_cb);   // Init Pulse input
	bm_init_signal(signal_cb); // Init Signal input
	return &comp;
}
