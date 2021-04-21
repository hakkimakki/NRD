/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh/models.h>
#include <dk_buttons_and_leds.h>
#include "model_handler.h"

/* ---------------- Sensor Client Stuff --------------------- */

#define GET_DATA_INTERVAL 30000

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

static void sensor_cli_series_entry_cb(
	struct bt_mesh_sensor_cli *cli, struct bt_mesh_msg_ctx *ctx,
	const struct bt_mesh_sensor_type *sensor, uint8_t index, uint8_t count,
	const struct bt_mesh_sensor_series_entry *entry)
{
	printk("Relative runtime in %d to %d degrees: %s percent\n",
	       entry->value[1].val1, entry->value[2].val1,
	       bt_mesh_sensor_ch_str_real(&entry->value[0]));
}

static const struct bt_mesh_sensor_cli_handlers bt_mesh_sensor_cli_handlers = {
	.data = sensor_cli_data_cb,
	.series_entry = sensor_cli_series_entry_cb,
};

static struct bt_mesh_sensor_cli sensor_cli =
	BT_MESH_SENSOR_CLI_INIT(&bt_mesh_sensor_cli_handlers);



/*
static struct bt_mesh_prop_cli prop_cli = BT_MESH_PROP_CLI_INIT(NULL,NULL);

struct bt_mesh_prop props[CONFIG_BT_MESH_PROP_MAXCOUNT];
struct bt_mesh_prop_val propsval[CONFIG_BT_MESH_PROP_MAXCOUNT];
uint16_t values_16[CONFIG_BT_MESH_PROP_MAXCOUNT];

static struct k_delayed_work get_data_work;

static void get_data(struct k_work *work)
{

	if (bt_mesh_is_provisioned())
		{
		int err;
		for (int i = 0; i < sizeof(propsval)/sizeof(propsval[0]); i++)
		{
			err = bt_mesh_prop_cli_prop_get(&prop_cli,NULL,BT_MESH_PROP_SRV_KIND_ADMIN,propsval[i].meta.id,&propsval[i]);
			printk("Get Props Values returned %d, id %d, val %d\n",err, propsval[i].meta.id, *propsval[i].value);
			//printk("BEGIN %s NRD/%04x/0052/%04x\n",bt_mesh_sensor_ch_str_real(value),ctx->addr,sensor->id);
		}
	}
	k_delayed_work_submit(&get_data_work, K_MSEC(GET_DATA_INTERVAL));
}

*/


/* Set up a repeating delayed work to blink the DK's LEDs when attention is
 * requested.
 */
static struct k_delayed_work attention_blink_work;

static void attention_blink(struct k_work *work)
{
	static int idx;
	const uint8_t pattern[] = {
		BIT(0) | BIT(1),
		BIT(1) | BIT(2),
		BIT(2) | BIT(3),
		BIT(3) | BIT(0),
	};

	dk_set_leds(pattern[idx++ % ARRAY_SIZE(pattern)]);
	k_delayed_work_submit(&attention_blink_work, K_MSEC(30));
}

static void attention_on(struct bt_mesh_model *mod)
{
	k_delayed_work_submit(&attention_blink_work, K_NO_WAIT);
}

static void attention_off(struct bt_mesh_model *mod)
{
	k_delayed_work_cancel(&attention_blink_work);
	dk_set_leds(DK_NO_LEDS_MSK);
}

static const struct bt_mesh_health_srv_cb health_srv_cb = {
	.attn_on = attention_on,
	.attn_off = attention_off,
};

static struct bt_mesh_health_srv health_srv = {
	.cb = &health_srv_cb,
};

BT_MESH_HEALTH_PUB_DEFINE(health_pub, 0);

static struct bt_mesh_elem elements[] = {
	BT_MESH_ELEM(1,
		     BT_MESH_MODEL_LIST(BT_MESH_MODEL_CFG_SRV,
					BT_MESH_MODEL_HEALTH_SRV(&health_srv,
								 &health_pub),
					BT_MESH_MODEL_SENSOR_CLI(&sensor_cli)),
		     BT_MESH_MODEL_NONE),
};

static const struct bt_mesh_comp comp = {
	.cid = CONFIG_BT_COMPANY_ID,
	.elem = elements,
	.elem_count = ARRAY_SIZE(elements),
};



const struct bt_mesh_comp *model_handler_init(void)
{
	k_delayed_work_init(&attention_blink_work, attention_blink);
	//k_delayed_work_init(&get_data_work, get_data);

	//k_delayed_work_submit(&get_data_work, K_MSEC(GET_DATA_INTERVAL));

	return &comp;
}
