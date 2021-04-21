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

//#include <device.h>
//#include <drivers/sensor.h>

#include "sht3x.h"

#include <stdio.h>


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


static int rc;
static int32_t temperature, humidity;

// the good stuff
void doubleToSensorValue(double d, struct sensor_value *val) {
  val->val1 = (int)d;
  val->val2 = (d - val->val1) * 1000000;
}

static void temp_hum_get(){
	/* Measure temperature and relative humidity and store into variables
         * temperature, humidity (each output multiplied by 1000).
         */
	rc = sht3x_measure_blocking_read(&temperature, &humidity);
	if (rc == STATUS_OK)
	{
		printf("measured temperature: %0.2f degreeCelsius, "
			   "measured humidity: %0.2f percentRH\n",
			   temperature / 1000.0f, humidity / 1000.0f);
	}
	else
	{
		printf("error reading measurement\n");
	}
}

static int temp_get(struct bt_mesh_sensor *sensor,
					struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp)
{
	temp_hum_get();
	doubleToSensorValue((double)temperature / 1000,rsp);
	return rc;
}

static int hum_get(struct bt_mesh_sensor *sensor,
					struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp)
{
	temp_hum_get();
	doubleToSensorValue((double)humidity / 1000,rsp);
	return rc;
}

static struct bt_mesh_sensor temp = {
	.type = &bt_mesh_sensor_present_dev_op_temp,
	.get = temp_get,
};

static struct bt_mesh_sensor hum = {
	.type = &bt_mesh_sensor_present_amb_rel_humidity,
	.get = hum_get,
};

static struct bt_mesh_sensor *const sensors[] = {
	&temp,
	&hum};

static struct bt_mesh_sensor_srv sensor_srv = BT_MESH_SENSOR_SRV_INIT(sensors, ARRAY_SIZE(sensors));

/* Define all Elements */
static struct bt_mesh_elem elements[] = {
	BT_MESH_ELEM(
		1, BT_MESH_MODEL_LIST(BT_MESH_MODEL_CFG_SRV, BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub), BT_MESH_MODEL_SENSOR_SRV(&sensor_srv)),
		BT_MESH_MODEL_NONE)};

/* Create Composition */
static const struct bt_mesh_comp comp = {
	.cid = CONFIG_BT_COMPANY_ID,
	.elem = elements,
	.elem_count = ARRAY_SIZE(elements),
};

const struct bt_mesh_comp *bm_blemesh_model_handler_init(void)
{
	/*
	dev = device_get_binding("SHT3XD");
	if (dev == NULL)
	{
		printf("Could not get SHT3XD device\n");
	}
	*/
	/* Initialize the i2c bus for the current platform */
	sensirion_i2c_init();
	sensirion_i2c_select_bus(0);

	return &comp;
}
