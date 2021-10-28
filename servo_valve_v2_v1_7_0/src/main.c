#include <zephyr.h>
#include <sys/reboot.h>
#include <sys/util.h>
#include <device.h>
#include <drivers/gpio.h>
#include <drivers/pwm.h>
#include <drivers/hwinfo.h>
#include <pm/device.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh.h>
#include <bluetooth/mesh/models.h>
#include <bluetooth/mesh/model_types.h>

/* ---------- Led ------------------- */
static struct gpio_dt_spec led = GPIO_DT_SPEC_GET_OR(DT_ALIAS(led0), gpios,{0});

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

/* ---------- PWM Servo Valves ------------------- */
#define PERIOD_USEC (20U * USEC_PER_MSEC)
#define VALVE_CLOSED_PULSE_USEC (177U * 100)
#define VALVE_OPEND_PULSE_USEC (187U * 100)

#define PWM_DRAIN_VALVE_NODE                DT_NODELABEL(pwm_drain_valve)
#define PWM_DRAIN_VALVE_CTLR                DT_PWMS_CTLR(PWM_DRAIN_VALVE_NODE)
#define PWM_DRAIN_VALVE_CHANNEL             DT_PWMS_CHANNEL(PWM_DRAIN_VALVE_NODE)

#define PWM_IRRIGATION_VALVE_NODE                DT_NODELABEL(pwm_irrigation_valve)
#define PWM_IRRIGATION_VALVE_CTLR                DT_PWMS_CTLR(PWM_IRRIGATION_VALVE_NODE)
#define PWM_IRRIGATION_VALVE_CHANNEL             DT_PWMS_CHANNEL(PWM_IRRIGATION_VALVE_NODE)

static const struct device *pwm_valve_drain;
static const struct device *pwm_valve_irrigation;

/* ---------- GPIO User ------------------- */
static const struct gpio_dt_spec gpio_enable_drain = GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), endrain_gpios);
static const struct gpio_dt_spec gpio_enable_irr = GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), enirr_gpios);
static const struct gpio_dt_spec gpio_enable_5v = GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), en5v_gpios);
static struct k_work_delayable gpio_enable_valves_off;

static void gpio_enable_valves_off_fn(struct k_work *work)
{
  gpio_pin_set_dt(&gpio_enable_drain, 0);
  gpio_pin_set_dt(&gpio_enable_irr, 0);
  gpio_pin_set_dt(&gpio_enable_5v, 0);
  device_busy_clear(pwm_valve_irrigation);
  device_busy_clear(pwm_valve_drain);
}

/* ------------ Bluetooth Mesh -------------- */
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

/* ON/OFF Server definition drain valve */
static void valve_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, const struct bt_mesh_onoff_set *set, struct bt_mesh_onoff_status *rsp);
static void valve_get(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, struct bt_mesh_onoff_status *rsp);

static const struct bt_mesh_onoff_srv_handlers onoff_handlers = {
    .set = valve_set,
    .get = valve_get,
};

struct valve_ctx {
	struct bt_mesh_onoff_srv srv;
  bool status;
};

static struct valve_ctx valve_ctx[] = {
  { .srv = BT_MESH_ONOFF_SRV_INIT(&onoff_handlers)},
  { .srv = BT_MESH_ONOFF_SRV_INIT(&onoff_handlers)},
};

static void valve_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, const struct bt_mesh_onoff_set *set, struct bt_mesh_onoff_status *rsp)
{
  gpio_pin_set_dt(&led, set->on_off);
  struct valve_ctx *valve = CONTAINER_OF(srv, struct valve_ctx, srv);
  int valve_idx = valve - &valve_ctx[0];
  if (valve_idx == 0){
    device_busy_set(pwm_valve_drain);
    gpio_pin_set_dt(&gpio_enable_drain, 1);
    pwm_pin_set_usec(pwm_valve_drain, PWM_DRAIN_VALVE_CHANNEL, PERIOD_USEC, set->on_off ? VALVE_OPEND_PULSE_USEC : VALVE_CLOSED_PULSE_USEC, 0);       //Drain Valve
  } else if (valve_idx == 1){
    device_busy_set(pwm_valve_irrigation);
    gpio_pin_set_dt(&gpio_enable_irr, 1);
    pwm_pin_set_usec(pwm_valve_irrigation, PWM_IRRIGATION_VALVE_CHANNEL, PERIOD_USEC, set->on_off ? VALVE_OPEND_PULSE_USEC : VALVE_CLOSED_PULSE_USEC, 0);       //Irrigation Valve
  }
  gpio_pin_set_dt(&gpio_enable_5v, 1);
  valve_ctx[valve_idx].status = set->on_off;
  k_work_reschedule(&gpio_enable_valves_off, K_MSEC(300));
}

static void valve_get(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, struct bt_mesh_onoff_status *rsp)
{
  struct valve_ctx *valve = CONTAINER_OF(srv, struct valve_ctx, srv);
  int valve_idx = valve - &valve_ctx[0];
  rsp->present_on_off = valve_ctx[valve_idx].status;
}

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
        1, BT_MESH_MODEL_LIST(BT_MESH_MODEL_CFG_SRV, BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub), BT_MESH_MODEL_ONOFF_SRV(&valve_ctx[0].srv)),BT_MESH_MODEL_NONE),
    BT_MESH_ELEM(
        2, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_SRV(&valve_ctx[1].srv)),BT_MESH_MODEL_NONE)};

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

  /* --------------- Reset Mesh ------------*/
	if(gpio_pin_get_dt(&button)){
		printk("Reset Mesh!\n");
		bt_mesh_reset();
	}

  /* This will be a no-op if settings_load() loaded provisioning info */
  bt_mesh_prov_enable(BT_MESH_PROV_ADV | BT_MESH_PROV_GATT);

  printk("Mesh initialized\n");
}

/**@brief Function for setup
 */
void setup(void)
{
  //Init Led
  gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
  //Init Reset Button
  gpio_pin_configure_dt(&button, GPIO_INPUT);
  gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
  gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
  gpio_add_callback(button.port, &button_cb_data);
  k_work_init_delayable(&buttons_debounce, buttons_debounce_fn);
  //Init Valves
  pwm_valve_drain = DEVICE_DT_GET(PWM_DRAIN_VALVE_CTLR);
  pwm_valve_irrigation = DEVICE_DT_GET(PWM_IRRIGATION_VALVE_CTLR);
  pwm_pin_set_usec(pwm_valve_drain, PWM_DRAIN_VALVE_CHANNEL, PERIOD_USEC, VALVE_OPEND_PULSE_USEC, 0);       //Open Drain Valve
  pwm_pin_set_usec(pwm_valve_irrigation, PWM_IRRIGATION_VALVE_CHANNEL, PERIOD_USEC, VALVE_CLOSED_PULSE_USEC, 0); //Close Irrigation Valve
  //Init GPIO
  gpio_pin_configure_dt(&gpio_enable_drain, GPIO_OUTPUT_INACTIVE);
  gpio_pin_configure_dt(&gpio_enable_irr, GPIO_OUTPUT_INACTIVE);
  k_work_init_delayable(&gpio_enable_valves_off, gpio_enable_valves_off_fn);
  //Init Bluetooth Mesh
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
  setup();
  // Start Application
  printk("Starting Application...\n");
}