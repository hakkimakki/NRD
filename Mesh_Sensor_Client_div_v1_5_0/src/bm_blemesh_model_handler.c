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

#include "bm_simple_buttons_and_leds.h"
#include "bm_blemesh.h"
#include "bm_blemesh_model_handler.h"

#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh/models.h>
#include <bluetooth/mesh/model_types.h>



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

/* ---------------- Sensor Client Stuff --------------------- */

static void sensor_cli_data_cb(struct bt_mesh_sensor_cli *cli,
			       struct bt_mesh_msg_ctx *ctx,
			       const struct bt_mesh_sensor_type *sensor,
			       const struct sensor_value *value)
{
	if (sensor->id == bt_mesh_sensor_present_dev_op_temp.id) {
		printk("Temperature: %s C\n",
		       bt_mesh_sensor_ch_str_real(value));		
	} else if (sensor->id == bt_mesh_sensor_present_amb_rel_humidity.id) {
		printk("Humidity: %s RH\n",
		       bt_mesh_sensor_ch_str_real(value));
	} else if (sensor->id == bt_mesh_sensor_present_amb_voc_concentration.id) {
		printk("tVOC  Concentration: %s ppm\n",
		       bt_mesh_sensor_ch_str_real(value));
	} else if (sensor->id == bt_mesh_sensor_present_amb_co2_concentration.id) {
		printk("CO2eq Concentration: %s ppm\n",
		       bt_mesh_sensor_ch_str_real(value));
	}
	printk("BEGIN %s NRD/%04x/0052/%04x\n",bt_mesh_sensor_ch_str_real(value),ctx->addr,sensor->id);
}


static const struct bt_mesh_sensor_cli_handlers bt_mesh_sensor_cli_handlers = {
	.data = sensor_cli_data_cb
};

static struct bt_mesh_sensor_cli sensor_cli =
	BT_MESH_SENSOR_CLI_INIT(&bt_mesh_sensor_cli_handlers);


/* -------------------- Composition Stuff ---------------------------*/


/* Define all Elements */
static struct bt_mesh_elem elements[] = {
	BT_MESH_ELEM(
		1, BT_MESH_MODEL_LIST(BT_MESH_MODEL_CFG_SRV, BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub), BT_MESH_MODEL_SENSOR_CLI(&sensor_cli)),
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


