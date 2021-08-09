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

#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh/models.h>
#include <bluetooth/mesh/model_types.h>

#include <bm_draniage_system.h>


/* ============================================== Element 1 ============================== */

/** ON/OFF Server definition */
static void pump_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx,
					const struct bt_mesh_onoff_set *set,
					struct bt_mesh_onoff_status *rsp)
{
	// Set DK LED index
	bm_pumpdrain_set(set->on_off);
}

static void pump_get(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx,
					struct bt_mesh_onoff_status *rsp)
{
	rsp->present_on_off = bm_pumpdrain_get();
}

static const struct bt_mesh_onoff_srv_handlers pump_onoff_handlers = {
	.set = pump_set,
	.get = pump_get,
};

static struct bt_mesh_onoff_srv pump_on_off_srv = BT_MESH_ONOFF_SRV_INIT(&pump_onoff_handlers);

/** Convert level to percent */
static int16_t level_to_percent(int16_t level){
	return (double)((double)level+BT_MESH_LVL_MAX)*100/(BT_MESH_LVL_MAX*2);
}

/** Convert percent to level */
static int16_t percent_to_level(int16_t percent){
	return ((percent*2*BT_MESH_LVL_MAX)/100)-BT_MESH_LVL_MAX;
}

/** Time Drainage Intervall LEVEL Server definition */
static void drain_intervall_h_get(struct bt_mesh_lvl_srv *srv, struct bt_mesh_msg_ctx *ctx,
					struct bt_mesh_lvl_status *rsp)
{
	printk("Waittime get is %u hours\n",drain_intervall_h);
	rsp->current = percent_to_level(drain_intervall_h);
}
static void drain_intervall_h_set(struct bt_mesh_lvl_srv *srv, struct bt_mesh_msg_ctx *ctx,
					const struct bt_mesh_lvl_set *set,
					struct bt_mesh_lvl_status *rsp)
{
	drain_intervall_h = level_to_percent(set->lvl);
	printk("Waittime set is %u hours\n",drain_intervall_h);
}
static void dummy_delta_set(struct bt_mesh_lvl_srv *srv,
				struct bt_mesh_msg_ctx *ctx,
				const struct bt_mesh_lvl_delta_set *delta_set,
				struct bt_mesh_lvl_status *rsp)
{ 
	printk("Not Supported\n");
}
static void dummy_h_move_set(struct bt_mesh_lvl_srv *srv,
			       struct bt_mesh_msg_ctx *ctx,
			       const struct bt_mesh_lvl_move_set *move_set,
			       struct bt_mesh_lvl_status *rsp)
{
	printk("Not Supported\n");
}
static const struct bt_mesh_lvl_srv_handlers drain_intervall_h_lvl_handlers = {
	.set = drain_intervall_h_set,
	.get = drain_intervall_h_get,
	.delta_set = dummy_delta_set,
	.move_set = dummy_h_move_set
};
static struct bt_mesh_lvl_srv drain_intervall_h_lvl_srv = BT_MESH_LVL_SRV_INIT(&drain_intervall_h_lvl_handlers);

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


/* ============================================== Valve Elements ============================== */

/** ON/OFF Client definition */
struct bt_mesh_onoff_cli valve_drain_on_off_cli[NUMBER_OF_VALVES] = {
	[0 ... NUMBER_OF_VALVES -1] =  BT_MESH_ONOFF_CLI_INIT(NULL) ,
};

/** Drain Valves Open Time Seconds LEVEL Server definition */
static void valve_drain_time_s_get(struct bt_mesh_lvl_srv *srv, struct bt_mesh_msg_ctx *ctx,
					struct bt_mesh_lvl_status *rsp)
{
	rsp->current = percent_to_level(valve_drain_time_s[srv->model->elem_idx - 1]);
}
static void valve_drain_time_s_set(struct bt_mesh_lvl_srv *srv, struct bt_mesh_msg_ctx *ctx,
					const struct bt_mesh_lvl_set *set,
					struct bt_mesh_lvl_status *rsp)
{
	valve_drain_time_s[srv->model->elem_idx - 1] = level_to_percent(set->lvl);
}
static const struct bt_mesh_lvl_srv_handlers valve_drain_time_s_lvl_handlers = {
	.set = valve_drain_time_s_set,
	.get = valve_drain_time_s_get,
	.delta_set = dummy_delta_set,
	.move_set = dummy_h_move_set
};
static struct bt_mesh_lvl_srv valve_drain_time_s_lvl_srv[NUMBER_OF_VALVES] = {
	[0 ... NUMBER_OF_VALVES -1] =  BT_MESH_LVL_SRV_INIT(&valve_drain_time_s_lvl_handlers) ,
};




/* Define all Elements */
static struct bt_mesh_elem elements[1+ NUMBER_OF_VALVES] = {
	BT_MESH_ELEM(
		1, BT_MESH_MODEL_LIST(BT_MESH_MODEL_CFG_SRV, BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub), BT_MESH_MODEL_ONOFF_SRV(&pump_on_off_srv), BT_MESH_MODEL_LVL_SRV(&drain_intervall_h_lvl_srv)),
		BT_MESH_MODEL_NONE),
	BT_MESH_ELEM(
		2, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_CLI(&valve_drain_on_off_cli[0]), BT_MESH_MODEL_LVL_SRV(&valve_drain_time_s_lvl_srv[0])),
		BT_MESH_MODEL_NONE),
	BT_MESH_ELEM(
		3, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_CLI(&valve_drain_on_off_cli[1]), BT_MESH_MODEL_LVL_SRV(&valve_drain_time_s_lvl_srv[1])),
		BT_MESH_MODEL_NONE),
		BT_MESH_ELEM(
		4, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_CLI(&valve_drain_on_off_cli[2]), BT_MESH_MODEL_LVL_SRV(&valve_drain_time_s_lvl_srv[2])),
		BT_MESH_MODEL_NONE),
		BT_MESH_ELEM(
		5, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_CLI(&valve_drain_on_off_cli[3]), BT_MESH_MODEL_LVL_SRV(&valve_drain_time_s_lvl_srv[3])),
		BT_MESH_MODEL_NONE),
		BT_MESH_ELEM(
		6, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_CLI(&valve_drain_on_off_cli[4]), BT_MESH_MODEL_LVL_SRV(&valve_drain_time_s_lvl_srv[4])),
		BT_MESH_MODEL_NONE),
		BT_MESH_ELEM(
		7, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_CLI(&valve_drain_on_off_cli[5]), BT_MESH_MODEL_LVL_SRV(&valve_drain_time_s_lvl_srv[5])),
		BT_MESH_MODEL_NONE),
		BT_MESH_ELEM(
		8, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_CLI(&valve_drain_on_off_cli[6]), BT_MESH_MODEL_LVL_SRV(&valve_drain_time_s_lvl_srv[6])),
		BT_MESH_MODEL_NONE),
		BT_MESH_ELEM(
		9, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_CLI(&valve_drain_on_off_cli[7]), BT_MESH_MODEL_LVL_SRV(&valve_drain_time_s_lvl_srv[7])),
		BT_MESH_MODEL_NONE)
				};



/* Create Composition */
const struct bt_mesh_comp comp = {
	.cid = CONFIG_BT_COMPANY_ID,
	.elem = elements,
	.elem_count = ARRAY_SIZE(elements),
};

const struct bt_mesh_comp *bm_blemesh_model_handler_init(void)
{
	return &comp;
}
