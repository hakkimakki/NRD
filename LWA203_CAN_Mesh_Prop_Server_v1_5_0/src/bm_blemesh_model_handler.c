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

#include <device.h>
#include <drivers/can.h>

#include <stdio.h>

const struct device *can_dev;
struct can_timing timing;
int filter_id;
struct bt_mesh_prop_val *buf_prop_val;

const struct zcan_filter my_filter = {
	.id_type = CAN_STANDARD_IDENTIFIER,
	.rtr = CAN_DATAFRAME,
	.id = 0x0, // REceive All
	.rtr_mask = 1,
	.id_mask = 0x0 //Receive all
};

K_SEM_DEFINE(prop_get_sem, 0, 1);
K_SEM_DEFINE(prop_set_sem, 0, 1);

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

/* -------------------- CAN Stuff --------------------------------------- */

void state_change_callback_function(enum can_state state, struct can_bus_err_cnt err_cnt)
{
	printk("State Change ISR\nstate: %u\n"
		   "rx error count: %d\n"
		   "tx error count: %d\n",
		   state,
		   err_cnt.rx_err_cnt, err_cnt.tx_err_cnt);
	if (state == CAN_ERROR_ACTIVE)
	{
		bm_led1_set(false);
	} else {
		bm_led1_set(true);
	}
	
}

/* -------------------- CAN Receive Stuff --------------------------------------- */

void rx_callback_function(struct zcan_frame *frame, void *arg)
{

	//struct bt_mesh_prop_val *prop_val = arg;

	/*
	printk("%02x ", frame->id);
	printk("%02x ", frame->data[0]);
	printk("%02x ", frame->data[1]);
	printk("%02x ", frame->data[2]);
	printk("%02x ", frame->data[3]);
	printk("%02x ", frame->data[4]);
	printk("%02x ", frame->data[5]);
	printk("%02x\n", frame->data[6]);
	*/

	uint16_t id = frame->data[4] | (frame->data[3] << 8);

	if (buf_prop_val->meta.id == id)
	{
		buf_prop_val->value[0] = frame->data[6];
		buf_prop_val->value[1] = frame->data[5];
	}
}

/* -------------------- CAN SEND Stuff --------------------------------------- */

void tx_irq_callback(uint32_t error_flags, void *arg)
{
	char *sender = (char *)arg;

	if (error_flags)
	{
		printk("Sendig failed [%d]\nSender: %s\n", error_flags, sender);
	}

	printk("Sent :)\n");
}

void get_elsterid_canbus(struct bt_mesh_prop_val *prop_val)
{
	// Wait until CAN Bus is Free
	bm_led3_set(true);
	if(k_sem_take(&prop_get_sem, K_MSEC(1500)) != 0){
		k_sem_reset(&prop_get_sem);
	}

	struct zcan_frame frame = {
		.id_type = CAN_STANDARD_IDENTIFIER,
		.rtr = CAN_DATAFRAME,
		.id = 0x680,
		.dlc = 5};

	frame.data[0] = 0x31;
	frame.data[1] = 0x0;
	frame.data[2] = 0xFA;
	frame.data[3] = (uint8_t)(prop_val->meta.id >> 8);
	frame.data[4] = (uint8_t)prop_val->meta.id & 0xff;

	// Setting the Pointer to the correct Buffer Value
	buf_prop_val = prop_val;

	printk("Sending...\n");	
	
	can_send(can_dev, &frame, K_MSEC(1000), NULL, NULL);
	// Wait until CAN Bus Received Value
	k_sleep(K_MSEC(1000));
	k_sem_give(&prop_get_sem);
	bm_led3_set(false);
}

void set_elsterid_canbus(struct bt_mesh_prop_val *prop_val)
{
	struct zcan_frame frame = {
		.id_type = CAN_STANDARD_IDENTIFIER,
		.rtr = CAN_DATAFRAME,
		.id = 0x680,
		.dlc = 7};

	frame.data[0] = 0x32;
	frame.data[1] = 0x00;
	frame.data[2] = 0xFA;
	frame.data[3] = (uint8_t)(prop_val->meta.id >> 8);
	frame.data[4] = (uint8_t)prop_val->meta.id & 0xff;
	frame.data[5] = prop_val->value[0];
	frame.data[6] = prop_val->value[1];
	printk("Sending...\n");
	can_send(can_dev, &frame, K_MSEC(1000), NULL,NULL);
	k_sem_give(&prop_set_sem);
}

/* -------------------- CAN Init Stuff --------------------------------------- */ 

void bm_can_init()
{

	// Init CAN Device
	k_sleep(K_MSEC(3000));

	can_dev = device_get_binding("CAN_1");

	k_sleep(K_MSEC(500));

	printk("1");

	filter_id = can_attach_isr(can_dev, rx_callback_function, NULL, &my_filter);
	if (filter_id < 0)
	{
		printk("Unable to attach isr [%d]", filter_id);
	}

	printk("2");

	k_sleep(K_MSEC(500));

	can_register_state_change_isr(can_dev, state_change_callback_function);

	timing.phase_seg1 = 0x8;
	timing.phase_seg2 = 0x8;
	timing.sjw = 0x1;
	timing.prescaler = 0x7; // Choose this prescaler
	timing.prop_seg = 0x8;

	k_sleep(K_MSEC(500));

	printk("3");

	can_set_timing(can_dev, &timing, &timing);

	k_sleep(K_MSEC(500));

	printk("4");

	can_set_mode(can_dev, CAN_NORMAL_MODE);

	k_sleep(K_MSEC(500));

	printk("5");

	//bm_init_buttons(get_elsterid_canbus(0x000c));
}




/* -------------------- Properties Server Stuff --------------------------------------- */ 

struct bt_mesh_prop props[CONFIG_BT_MESH_PROP_MAXCOUNT];
struct bt_mesh_prop_val propsval[CONFIG_BT_MESH_PROP_MAXCOUNT];
uint16_t values_16[CONFIG_BT_MESH_PROP_MAXCOUNT];

static void get(struct bt_mesh_prop_srv *srv, struct bt_mesh_msg_ctx *ctx, struct bt_mesh_prop_val *val)
{
	get_elsterid_canbus(val);
}

static void set(struct bt_mesh_prop_srv *srv, struct bt_mesh_msg_ctx *ctx, struct bt_mesh_prop_val *val)
{
	
	set_elsterid_canbus(val);
	k_sem_take(&prop_set_sem, K_MSEC(1500));
}

static struct bt_mesh_prop_srv prop_srv_adm = BT_MESH_PROP_SRV_ADMIN_INIT(props, get, set);

/* -------------------- Sensor Server Stuff ---------------------------*/

void doubleToSensorValue(double d, struct sensor_value *val)
{
	val->val1 = (int)d;
	val->val2 = (d - val->val1) * 1000000;
}

static int outsidetemp_get(struct bt_mesh_sensor *sensor,
					struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp)
{
	get_elsterid_canbus(&propsval[1]);
	uint16_t temp = propsval[1].value[0] | (propsval[1].value[1] << 8);
	doubleToSensorValue((double)temp / 10, rsp);
	return 0;
}

static int speicheristtemp_get(struct bt_mesh_sensor *sensor,
					struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp)
{
	get_elsterid_canbus(&propsval[2]);
	uint16_t temp = propsval[2].value[0] | (propsval[2].value[1] << 8);
	doubleToSensorValue((double)temp / 10, rsp);
	return 0;
}

static int speichersoll_get(struct bt_mesh_sensor *sensor,
					struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp)
{
	get_elsterid_canbus(&propsval[7]);
	uint16_t temp = propsval[7].value[0] | (propsval[7].value[1] << 8);
	doubleToSensorValue((double)temp/10, rsp);
	return 0;
}

static int vorlaufisttemp_get(struct bt_mesh_sensor *sensor,
					struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp)
{
	get_elsterid_canbus(&propsval[10]);
	uint16_t temp = propsval[10].value[0] | (propsval[10].value[1] << 8);
	doubleToSensorValue((double)temp / 10, rsp);
	return 0;
}

static int verdampfertemp_get(struct bt_mesh_sensor *sensor,
					struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp)
{
	get_elsterid_canbus(&propsval[14]);
	uint16_t temp = propsval[14].value[0] | (propsval[14].value[1] << 8);
	doubleToSensorValue((double)temp / 10, rsp);
	return 0;
}

static int vorlaufsolltemp_get(struct bt_mesh_sensor *sensor,
					struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp)
{
	get_elsterid_canbus(&propsval[15]);
	uint16_t temp = propsval[15].value[0] | (propsval[15].value[1] << 8);
	doubleToSensorValue((double)temp/10, rsp);
	return 0;
}

static struct bt_mesh_sensor outsidetemp = {
	.type = &bt_mesh_sensor_present_dev_op_temp,
	.get = outsidetemp_get,
};

static struct bt_mesh_sensor speicheristtemp = {
	.type = &bt_mesh_sensor_present_dev_op_temp,
	.get = speicheristtemp_get,
};

static struct bt_mesh_sensor speichersolltemp = {
	.type = &bt_mesh_sensor_present_dev_op_temp,
	.get = speichersoll_get,
};

static struct bt_mesh_sensor vorlaufisttemp = {
	.type = &bt_mesh_sensor_present_dev_op_temp,
	.get = vorlaufisttemp_get,
};

static struct bt_mesh_sensor verdampfertemp = {
	.type = &bt_mesh_sensor_present_dev_op_temp,
	.get = verdampfertemp_get,
};

static struct bt_mesh_sensor vorlaufsolltemp = {
	.type = &bt_mesh_sensor_present_dev_op_temp,
	.get = vorlaufsolltemp_get,
};

static struct bt_mesh_sensor *const outsidetemp_sensors[] = {&outsidetemp};
static struct bt_mesh_sensor_srv outsidetemp_sensor_srv = BT_MESH_SENSOR_SRV_INIT(outsidetemp_sensors, ARRAY_SIZE(outsidetemp_sensors));

static struct bt_mesh_sensor *const speicheristtemp_sensors[] = {&speicheristtemp};
static struct bt_mesh_sensor_srv speicheristtemp_sensor_srv = BT_MESH_SENSOR_SRV_INIT(speicheristtemp_sensors, ARRAY_SIZE(speicheristtemp_sensors));

static struct bt_mesh_sensor *const speichersolltemp_sensors[] = {&speichersolltemp};
static struct bt_mesh_sensor_srv speichersolltemp_sensor_srv = BT_MESH_SENSOR_SRV_INIT(speichersolltemp_sensors, ARRAY_SIZE(speichersolltemp_sensors));

static struct bt_mesh_sensor *const vorlaufisttemp_sensors[] = {&vorlaufisttemp};
static struct bt_mesh_sensor_srv vorlaufisttemp_sensor_srv = BT_MESH_SENSOR_SRV_INIT(vorlaufisttemp_sensors, ARRAY_SIZE(vorlaufisttemp_sensors));

static struct bt_mesh_sensor *const verdampfertemp_sensors[] = {&verdampfertemp};
static struct bt_mesh_sensor_srv verdampfertemp_sensor_srv = BT_MESH_SENSOR_SRV_INIT(verdampfertemp_sensors, ARRAY_SIZE(verdampfertemp_sensors));

static struct bt_mesh_sensor *const vorlaufsolltemp_sensors[] = {&vorlaufsolltemp};
static struct bt_mesh_sensor_srv vorlaufsolltemp_sensor_srv = BT_MESH_SENSOR_SRV_INIT(vorlaufsolltemp_sensors, ARRAY_SIZE(vorlaufsolltemp_sensors));

/* -------------------- Composition Stuff ---------------------------*/


/* Define all Elements */
static struct bt_mesh_elem elements[] = {
	BT_MESH_ELEM(
		1, BT_MESH_MODEL_LIST(BT_MESH_MODEL_CFG_SRV, BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub), BT_MESH_MODEL_PROP_SRV_ADMIN(&prop_srv_adm), BT_MESH_MODEL_SENSOR_SRV(&outsidetemp_sensor_srv)),
		BT_MESH_MODEL_NONE),
		BT_MESH_ELEM(
		2, BT_MESH_MODEL_LIST(BT_MESH_MODEL_SENSOR_SRV(&speicheristtemp_sensor_srv)),
		BT_MESH_MODEL_NONE),
		BT_MESH_ELEM(
		3, BT_MESH_MODEL_LIST(BT_MESH_MODEL_SENSOR_SRV(&speichersolltemp_sensor_srv)),
		BT_MESH_MODEL_NONE),
		BT_MESH_ELEM(
		4, BT_MESH_MODEL_LIST(BT_MESH_MODEL_SENSOR_SRV(&vorlaufisttemp_sensor_srv)),
		BT_MESH_MODEL_NONE),
		BT_MESH_ELEM(
		5, BT_MESH_MODEL_LIST(BT_MESH_MODEL_SENSOR_SRV(&verdampfertemp_sensor_srv)),
		BT_MESH_MODEL_NONE),
		BT_MESH_ELEM(
		6, BT_MESH_MODEL_LIST(BT_MESH_MODEL_SENSOR_SRV(&vorlaufsolltemp_sensor_srv)),
		BT_MESH_MODEL_NONE)};

/* Create Composition */
static const struct bt_mesh_comp comp = {
	.cid = CONFIG_BT_COMPANY_ID,
	.elem = elements,
	.elem_count = ARRAY_SIZE(elements),
};



const struct bt_mesh_comp *bm_blemesh_model_handler_init(void)
{
	// Init the Properties
	props[0].id = 0x0003;
	props[0].user_access = BT_MESH_PROP_ACCESS_READ; // Speichersolltemp
	props[1].id = 0x000c;
	props[1].user_access = BT_MESH_PROP_ACCESS_READ; // Aussentemp
	props[2].id = 0x000e;
	props[2].user_access = BT_MESH_PROP_ACCESS_READ; // Speicheristtemp
	props[3].id = 0x0013;
	props[3].user_access = BT_MESH_PROP_ACCESS_READ_WRITE; // EINSTELL_SPEICHERSOLLTEMP
	props[4].id = 0x0022;
	props[4].user_access = BT_MESH_PROP_ACCESS_READ_WRITE; // HYSTERESEZEIT
	props[5].id = 0x010e;
	props[5].user_access = BT_MESH_PROP_ACCESS_READ_WRITE; // HEIZKURVE
	props[6].id = 0x0112;
	props[6].user_access = BT_MESH_PROP_ACCESS_READ_WRITE; // PROGRAMMSCHALTER
	props[7].id = 0x0003;
	props[7].user_access = BT_MESH_PROP_ACCESS_READ_WRITE; // SPEICHERSOLLTEMP
	props[8].id = 0x01c4;
	props[8].user_access = BT_MESH_PROP_ACCESS_READ; //  LAUFZEIT_WP1
	props[9].id = 0x01c5;
	props[9].user_access = BT_MESH_PROP_ACCESS_READ; // LAUFZEIT_WP2
	props[10].id = 0x01d6;
	props[10].user_access = BT_MESH_PROP_ACCESS_READ; // WPVORLAUFIST
	props[11].id = 0x0259;
	props[11].user_access = BT_MESH_PROP_ACCESS_READ; // LAUFZEIT_DHC1
	props[12].id = 0x025a;
	props[12].user_access = BT_MESH_PROP_ACCESS_READ; // LAUFZEIT_DHC2
	props[13].id = 0x0331;
	props[13].user_access = BT_MESH_PROP_ACCESS_READ; // WARTEZEIT_DHC
	props[14].id = 0x0333;
	props[14].user_access = BT_MESH_PROP_ACCESS_READ; // Verdampfertemp
	props[15].id = 0x01bf;
	props[15].user_access = BT_MESH_PROP_ACCESS_READ; // Vorlaufsolltemp
	// Init the Properties Values
	propsval[0].meta = props[0];
	propsval[0].size = 2;
	propsval[0].value = (uint8_t *)&values_16[0];
	propsval[1].meta = props[1];
	propsval[1].size = 2;
	propsval[1].value = (uint8_t *)&values_16[1];
	propsval[2].meta = props[2];
	propsval[2].size = 2;
	propsval[2].value = (uint8_t *)&values_16[2];
	propsval[3].meta = props[3];
	propsval[3].size = 2;
	propsval[3].value = (uint8_t *)&values_16[3];
	propsval[4].meta = props[4];
	propsval[4].size = 2;
	propsval[4].value = (uint8_t *)&values_16[4];
	propsval[5].meta = props[5];
	propsval[5].size = 2;
	propsval[5].value = (uint8_t *)&values_16[5];
	propsval[6].meta = props[6];
	propsval[6].size = 2;
	propsval[6].value = (uint8_t *)&values_16[6];
	propsval[7].meta = props[7];
	propsval[7].size = 2;
	propsval[7].value = (uint8_t *)&values_16[7];
	propsval[8].meta = props[8];
	propsval[8].size = 2;
	propsval[8].value = (uint8_t *)&values_16[8];
	propsval[9].meta = props[9];
	propsval[9].size = 2;
	propsval[9].value = (uint8_t *)&values_16[9];
	propsval[10].meta = props[10];
	propsval[10].size = 2;
	propsval[10].value = (uint8_t *)&values_16[10];
	propsval[11].meta = props[11];
	propsval[11].size = 2;
	propsval[11].value = (uint8_t *)&values_16[11];
	propsval[12].meta = props[12];
	propsval[12].size = 2;
	propsval[12].value = (uint8_t *)&values_16[12];
	propsval[13].meta = props[13];
	propsval[13].size = 2;
	propsval[13].value = (uint8_t *)&values_16[13];
	propsval[14].meta = props[14];
	propsval[14].size = 2;
	propsval[14].value = (uint8_t *)&values_16[14];
	propsval[15].meta = props[15];
	propsval[15].size = 2;
	propsval[15].value = (uint8_t *)&values_16[15];
	k_sem_reset(&prop_get_sem);
	k_sem_reset(&prop_set_sem);

	// Init the Publisher Worker
	//k_delayed_work_init(&publicita_work, publicita);
	// Submit the Worker
	//k_delayed_work_submit(&publicita_work, K_MSEC(5000));


	return &comp;
}


