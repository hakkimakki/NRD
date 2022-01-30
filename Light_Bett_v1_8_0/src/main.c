#include <zephyr.h>
#include <sys/reboot.h>
#include <sys/util.h>
#include <device.h>
#include <drivers/gpio.h>
#include <drivers/pwm.h>
#include <drivers/hwinfo.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh.h>
#include <bluetooth/mesh/models.h>
#include <bluetooth/mesh/model_types.h>

/* ---------- Led ------------------- */
static struct gpio_dt_spec led = GPIO_DT_SPEC_GET_OR(DT_ALIAS(led0), gpios,{0});

static void leds_init()
{
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
}

/* ---------- Reset Button ------------------- */
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET_OR(DT_ALIAS(sw0), gpios, {0});
static struct gpio_callback button_cb_data;
static struct k_work_delayable buttons_debounce;

static void reset()
{
  printk("Reboot now!\n");
  sys_reboot(SYS_REBOOT_COLD);
}

static void buttons_debounce_fn(struct k_work *work)
{
  if (gpio_pin_get_dt(&button) == true)
  {
    reset();
  }
}

void button_pressed(const struct device *dev, struct gpio_callback *cb,
                    uint32_t pins)
{
  printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
  k_work_reschedule(&buttons_debounce, K_MSEC(5 * 1000)); // Debounce the Button
}

//Init Reset Button
static void buttons_init()
{
    //Init Reset Button
  gpio_pin_configure_dt(&button, GPIO_INPUT);
  gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
  gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
  gpio_add_callback(button.port, &button_cb_data);
  k_work_init_delayable(&buttons_debounce, buttons_debounce_fn);
}


/* ---------------------------- Bluetooth Mesh ------------------------------- */

#include <drivers/hwinfo.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh.h>
#include <bluetooth/mesh/models.h>
#include <bluetooth/mesh/model_types.h>


/* Provisioning */
static int output_number(bt_mesh_output_action_t action, uint32_t number)
{
  printk("OOB Number: %u\n", number);
  return 0;
}

static void prov_complete(uint16_t net_idx, uint16_t addr)
{
  printk("Prov complete! Addr: 0x%04x\n", addr);
}

static void prov_reset(void)
{
  printk("Prov reset!\n");
  bt_mesh_prov_enable(BT_MESH_PROV_ADV | BT_MESH_PROV_GATT);
}

static uint8_t dev_uuid[16];

static const struct bt_mesh_prov prov = {
    .uuid = dev_uuid,
    .output_size = 4,
    .output_actions = BT_MESH_DISPLAY_NUMBER,
    .output_number = output_number,
    .complete = prov_complete,
    .reset = prov_reset,
};

/* ON/OFF Server definition */
static struct gpio_dt_spec lightctrl = GPIO_DT_SPEC_GET_OR(DT_ALIAS(lightctrl), gpios,{0});

static void on_off_server_init()
{
  gpio_pin_configure_dt(&lightctrl, GPIO_OUTPUT_ACTIVE);
}

static void switch_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, const struct bt_mesh_onoff_set *set, struct bt_mesh_onoff_status *rsp)
{
  gpio_pin_set_dt(&lightctrl, !set->on_off);
  gpio_pin_set_dt(&led, set->on_off);
}
static void switch_get(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, struct bt_mesh_onoff_status *rsp){
  rsp->present_on_off = gpio_pin_get_dt(&lightctrl);
}

static const struct bt_mesh_onoff_srv_handlers onoff_handlers = {
    .set = switch_set,
    .get = switch_get,
};

static struct bt_mesh_onoff_srv on_off_srv = BT_MESH_ONOFF_SRV_INIT(&onoff_handlers);



/* Health Server definition */
static void attention_on(struct bt_mesh_model *model)
{
  printk("attention_on!\n");
}
static void attention_off(struct bt_mesh_model *model)
{
  printk("attention_off!\n");
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
        1, BT_MESH_MODEL_LIST(BT_MESH_MODEL_CFG_SRV, BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub),  BT_MESH_MODEL_ONOFF_SRV(&on_off_srv)),BT_MESH_MODEL_NONE)
    };

/* Create Composition */
static const struct bt_mesh_comp comp = {
    .cid = CONFIG_BT_COMPANY_ID,
    .elem = elements,
    .elem_count = ARRAY_SIZE(elements),
};

/* Bluetooth */
static void bt_ready(int err)
{
  if (err)
  {
    printk("Bluetooth init failed (err %d)\n", err);
    return;
  }

  printk("Bluetooth initialized\n");

  err = bt_mesh_init(&prov, &comp);
  if (err)
  {
    printk("Initializing mesh failed (err %d)\n", err);
    return;
  }

  if (IS_ENABLED(CONFIG_SETTINGS))
  {
    settings_load();
  }

  //Check Reboot Condition
  /* --------------- Reset Mesh ------------*/
	if(gpio_pin_get_dt(&button)){
		printk("Reset Mesh!\n");
		bt_mesh_reset();
	}


  /* This will be a no-op if settings_load() loaded provisioning info */
  bt_mesh_prov_enable(BT_MESH_PROV_ADV | BT_MESH_PROV_GATT);

  /* Check for Friendship */

  printk("Mesh initialized\n");
}


//Init Bluetooth Mesh
static void bluetooth_mesh_init()
{
  static int err;
  if (IS_ENABLED(CONFIG_HWINFO)) {
		err = hwinfo_get_device_id(dev_uuid, sizeof(dev_uuid));
	}
	if (err < 0) {
		dev_uuid[0] = 0xdd;
		dev_uuid[1] = 0xdd;
	}
  //Init Bluetooth
	bt_enable(bt_ready);
}


/**@brief Function for application main entry.
 */
void main(void)
{
  //Init
  printk("Init...\n");
  //Init LED
  leds_init();
  //Init Reset Button
  buttons_init();
  // Init ON OFF Server
  on_off_server_init();
  //Init Bluetooth Mesh
  bluetooth_mesh_init();
  // Start Application
  printk("Starting Application...\n");
}