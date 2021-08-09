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


#include "bm_simple_buttons_and_leds.h"
#include "bm_blemesh.h"
#include "bm_blemesh_model_handler.h"
#include "bm_servo_valve.h"

#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh/models.h>
#include <bluetooth/mesh/model_types.h>




/** ON/OFF Server definition */
static void valve_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx,
					const struct bt_mesh_onoff_set *set,
					struct bt_mesh_onoff_status *rsp)
{
	// Set DK LED index
	if (set->on_off){
		bm_open_servo_valve();
	} else {
		bm_close_servo_valve();
	}	
}

static void valve_get(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx,
					struct bt_mesh_onoff_status *rsp)
{
	rsp->present_on_off = bm_status_servo_valve;
}

static const struct bt_mesh_onoff_srv_handlers onoff_handlers = {
	.set = valve_set,
	.get = valve_get,
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
		1, BT_MESH_MODEL_LIST(BT_MESH_MODEL_CFG_SRV, BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub), BT_MESH_MODEL_ONOFF_SRV(&on_off_srv)),
		BT_MESH_MODEL_NONE)};

/* Create Composition */
static const struct bt_mesh_comp comp = {
	.cid = CONFIG_BT_COMPANY_ID,
	.elem = elements,
	.elem_count = ARRAY_SIZE(elements),
};

const struct bt_mesh_comp *bm_blemesh_model_handler_init(void)
{
	return &comp;
}
