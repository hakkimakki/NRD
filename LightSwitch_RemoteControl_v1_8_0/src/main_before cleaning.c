/*
 * Copyright (c) 2017 Raffael Anklin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* ---------- Led ------------------- */
#include <zephyr.h>
//#include <drivers/gpio.h>
#include <hal/nrf_gpio.h>
#include <nrfx_gpiote.h>
#include <hal/nrf_gpiote.h>

//static struct gpio_dt_spec led = GPIO_DT_SPEC_GET_OR(DT_ALIAS(led0), gpios,{0});

//Init Reset Button
static void leds_init()
{
  //gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
}

/* ---------- Buttons ------------------- 
static const struct gpio_dt_spec button_1_on = GPIO_DT_SPEC_GET_OR(DT_ALIAS(sw1on), gpios, {0});
static const struct gpio_dt_spec button_2_on = GPIO_DT_SPEC_GET_OR(DT_ALIAS(sw2on), gpios, {0});
static const struct gpio_dt_spec button_3_on = GPIO_DT_SPEC_GET(DT_ALIAS(sw3on), gpios);
static const struct gpio_dt_spec button_4_on = GPIO_DT_SPEC_GET_OR(DT_ALIAS(sw4on), gpios, {0});
static const struct gpio_dt_spec button_1_off = GPIO_DT_SPEC_GET_OR(DT_ALIAS(sw1off), gpios, {0});
static const struct gpio_dt_spec button_2_off = GPIO_DT_SPEC_GET_OR(DT_ALIAS(sw2off), gpios, {0});
static const struct gpio_dt_spec button_3_off = GPIO_DT_SPEC_GET_OR(DT_ALIAS(sw3off), gpios, {0});
static const struct gpio_dt_spec button_4_off = GPIO_DT_SPEC_GET_OR(DT_ALIAS(sw4off), gpios, {0});
static struct gpio_callback button_cb_data_port0;
static struct gpio_callback button_cb_data_port1;
*/
static struct k_work_delayable buttons_debounce;

static void mesh_model_button_handler();
static void lpn_wakeup();
static void lpn_sleep();

static bool buttons_locked;
static uint32_t pressed_pins;

static void buttons_debounce_fn(struct k_work *work)
{
  lpn_wakeup();
  mesh_model_button_handler();
}

/*
void button_pressed(const struct device *dev, struct gpio_callback *cb,
                    uint32_t pins)
{
  printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
  if (!buttons_locked){
    buttons_locked = true;
    pressed_pins = pins;
    k_work_reschedule(&buttons_debounce, K_MSEC(100)); // Debounce the Button
  }
}
*/

static void gpiote_isr(const void *irq_handler)
{
	//((nrfx_irq_handler_t)irq_handler)();
  nrf_gpiote_event_clear(NRF_GPIOTE, NRF_GPIOTE_EVENT_PORT);
  nrf_gpiote_int_disable(NRF_GPIOTE, GPIOTE_INTENSET_PORT_Msk); 
  printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
  if (!buttons_locked){
    buttons_locked = true;
    k_work_reschedule(&buttons_debounce, K_MSEC(100)); // Debounce the Button
  }
}

//Init Reset Button
static void buttons_init()
{
  //nrf_gpiote_event_enable(NRF_GPIOTE,0);
  //NRF_GPIOTE->INTENCLR = 
/*
  gpio_pin_configure_dt(&button_1_on, GPIO_INPUT);
  
  //gpio_pin_interrupt_configure_dt(&button_1_on, GPIO_INT_EDGE_TO_ACTIVE);

  gpio_pin_configure_dt(&button_2_on, GPIO_INPUT);
  //gpio_pin_interrupt_configure_dt(&button_2_on, GPIO_INT_EDGE_TO_ACTIVE);

  gpio_pin_configure_dt(&button_3_on, GPIO_INPUT);
  //gpio_pin_interrupt_configure_dt(&button_3_on, GPIO_INT_EDGE_TO_ACTIVE);

  gpio_pin_configure_dt(&button_4_on, GPIO_INPUT);
  //gpio_pin_interrupt_configure_dt(&button_4_on, GPIO_INT_EDGE_TO_ACTIVE);

  gpio_pin_configure_dt(&button_1_off, GPIO_INPUT);
  //gpio_pin_interrupt_configure_dt(&button_1_off, GPIO_INT_EDGE_TO_ACTIVE);

  gpio_pin_configure_dt(&button_2_off, GPIO_INPUT);
  //gpio_pin_interrupt_configure_dt(&button_2_off, GPIO_INT_EDGE_TO_ACTIVE);

  gpio_pin_configure_dt(&button_3_off, GPIO_INPUT);
  //gpio_pin_interrupt_configure_dt(&button_3_off, GPIO_INT_EDGE_TO_ACTIVE);  

  gpio_pin_configure_dt(&button_4_off, GPIO_INPUT);
  //gpio_pin_interrupt_configure_dt(&button_4_off, GPIO_INT_EDGE_TO_ACTIVE);

  //gpio_init_callback(&button_cb_data_port1, button_pressed, BIT(button_1_on.pin) | BIT(button_2_on.pin) | BIT(button_2_off.pin) | BIT(button_3_off.pin));
  //gpio_init_callback(&button_cb_data_port0, button_pressed, BIT(button_3_on.pin) | BIT(button_4_on.pin) | BIT(button_1_off.pin) | BIT(button_4_off.pin));
  
  //gpio_add_callback(button_3_off.port, &button_cb_data_port1); //Port 1
  //gpio_add_callback(button_3_on.port, &button_cb_data_port0); //Port 0
  
*/
  k_work_init_delayable(&buttons_debounce, buttons_debounce_fn);

  // Test Wake UP
  /* Configure to generate PORT event (wakeup) on buttons press. */
  nrf_gpio_cfg_sense_input(26,NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);
  nrf_gpio_cfg_sense_input(27,NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);
  nrf_gpio_cfg_sense_input(28,NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);
  nrf_gpio_cfg_sense_input(29,NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);
  nrf_gpio_cfg_sense_input(19,NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);
  nrf_gpio_cfg_sense_input(20,NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);
  nrf_gpio_cfg_sense_input(21,NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);
  nrf_gpio_cfg_sense_input(22,NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);

  /* Connect GPIOTE_0 IRQ to nrfx_gpiote_irq_handler */
	IRQ_CONNECT(DT_IRQN(DT_NODELABEL(gpiote)),
		    DT_IRQ(DT_NODELABEL(gpiote), priority),
		    gpiote_isr, NULL, 0);

    NRFX_IRQ_PRIORITY_SET(nrfx_get_irq_number(NRF_GPIOTE), 0);
    NRFX_IRQ_ENABLE(nrfx_get_irq_number(NRF_GPIOTE));
    nrf_gpiote_event_clear(NRF_GPIOTE, NRF_GPIOTE_EVENT_PORT);
    nrf_gpiote_int_enable(NRF_GPIOTE, GPIOTE_INTENSET_PORT_Msk);   
  
        /* Connect GPIOTE_0 IRQ to nrfx_gpiote_irq_handler 
	IRQ_CONNECT(DT_IRQN(DT_NODELABEL(gpiote)),
		    DT_IRQ(DT_NODELABEL(gpiote), priority),
		    nrfx_isr, nrfx_gpiote_irq_handler, 0);
*/
  
  //nrfx_gpiote_init(0)

  //Enable GPIOTE Channel 0 Event Mode
  //NRF_GPIOTE->CONFIG[0] |= GPIOTE_CONFIG_MODE_Event;
  //Enable GPIOTE Channel 0 Port
  //NRF_GPIOTE->CONFIG[0] |= GPIOTE_CONFIG_PORT_Pos;
  //Clear Interrupt
  //NRF_GPIOTE->EVENTS_PORT = 0;
  //Enable Interrupt
  //NRF_GPIOTE->INTENSET |= NRF_GPIOTE_INT_PORT_MASK;

  //nrf_gpiote_event_enable(NRF_GPIOTE,0);
  

  

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

/* ON/OFF Client definition */

/** Context for a single light switch. */
struct button {
	/** Current light status of the corresponding server. */
	bool status;
	/** Generic OnOff client instance for this switch. */
	struct bt_mesh_onoff_cli client;
};

static void status_handler(struct bt_mesh_onoff_cli *cli,
			   struct bt_mesh_msg_ctx *ctx,
			   const struct bt_mesh_onoff_status *status);

static struct button buttons[] = {
	{ .client = BT_MESH_ONOFF_CLI_INIT(&status_handler) },
	{ .client = BT_MESH_ONOFF_CLI_INIT(&status_handler) },
	{ .client = BT_MESH_ONOFF_CLI_INIT(&status_handler) },
	{ .client = BT_MESH_ONOFF_CLI_INIT(&status_handler) },
};

static void status_handler(struct bt_mesh_onoff_cli *cli,
			   struct bt_mesh_msg_ctx *ctx,
			   const struct bt_mesh_onoff_status *status)
{
	struct button *button =
		CONTAINER_OF(cli, struct button, client);
	int index = button - &buttons[0];
	button->status = status->present_on_off;
	printk("Button %d: Received response: %s\n", index + 1,
	       status->present_on_off ? "on" : "off");
}

static void mesh_model_button_handler()
{  	
  //Check which Button is pressed
  static int i = 0;
  static int err;
  /*
  if ((gpio_pin_get_dt(&button_1_on) == true) || (pressed_pins & (1 << button_1_on.pin)))
  {
    i = 0;
    buttons[i].status = true;
  } else if ((gpio_pin_get_dt(&button_1_off) == true) || (pressed_pins & (1 << button_1_off.pin)))
  {
    i = 0;
    buttons[i].status = false;
  } else if ((gpio_pin_get_dt(&button_2_on) == true) || (pressed_pins & (1 << button_2_on.pin)))
  {
    i = 1;
    buttons[i].status = true;
  } else if ((gpio_pin_get_dt(&button_2_off) == true) || (pressed_pins & (1 << button_2_off.pin)))
  {
    i = 1;
    buttons[i].status = false;
  } else if ((gpio_pin_get_dt(&button_3_on) == true) || (pressed_pins & (1 << button_3_on.pin)))
  {
    i = 2;
    buttons[i].status = true;
  } else if ((gpio_pin_get_dt(&button_3_off) == true) || (pressed_pins & (1 << button_3_off.pin)))
  {
    i = 2;
    buttons[i].status = false;
  } else if ((gpio_pin_get_dt(&button_4_on) == true) || (pressed_pins & (1 << button_4_on.pin)))
  {
    i = 3;
    buttons[i].status = true;
  } else if ((gpio_pin_get_dt(&button_4_off) == true) || (pressed_pins & (1 << button_4_off.pin)))
  {
    i = 3;
    buttons[i].status = false;
  } else 
  {
    printk("Error no button pressed\n");
  }
  */
  pressed_pins = 0;
  if (bt_mesh_is_provisioned()) {    
    struct bt_mesh_onoff_set set = {.on_off = buttons[i].status,};
    err = bt_mesh_onoff_cli_set_unack(&buttons[i].client,NULL, &set);
    if (err) {
        printk("OnOff %d set failed: %d\n", i + 1, err);
    }
  }
  err = bt_mesh_lpn_poll();
  if (err != 0){
    printk("Poll Error %d\n",err);
  }
  lpn_sleep();  
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
    BT_MESH_ELEM(1, BT_MESH_MODEL_LIST(BT_MESH_MODEL_CFG_SRV, BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub), BT_MESH_MODEL_ONOFF_CLI(&buttons[0].client)),BT_MESH_MODEL_NONE),
    BT_MESH_ELEM(2, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_CLI(&buttons[1].client)),BT_MESH_MODEL_NONE),
    BT_MESH_ELEM(3, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_CLI(&buttons[2].client)),BT_MESH_MODEL_NONE),
    BT_MESH_ELEM(4, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_CLI(&buttons[3].client)),BT_MESH_MODEL_NONE),
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
  /*
  if ((gpio_pin_get_dt(&button_1_on) == true) ){
    printk("Reset Mesh!\n");
		bt_mesh_reset();
  }
  */

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

/* Manual Low Power Node Override */
#include <stdio.h>
#include <zephyr.h>
#include <device.h>
#include <init.h>
#include <pm/pm.h>
#include <bluetooth/mesh/main.h>

#define CONSOLE_LABEL DT_LABEL(DT_CHOSEN(zephyr_console))
#define CLOCK_LABEL DT_LABEL(DT_NODELABEL(clock))

const struct device *cons;
//const struct device *clk;

static void lpn_app_init(){
  //cons = device_get_binding(CONSOLE_LABEL);
}

static void lpn_wakeup(){
  /*
  clk = device_get_binding(CLOCK_LABEL);
  if (clk == NULL)
  {
    printk("No Clock Device found\n");
  } else {
    printk("Clock Device found\n"); 
  }
  */
  cons = device_get_binding(CONSOLE_LABEL);
  if (cons == NULL)
  {
    printk("No UART Device found\n");
  } else {
    pm_device_state_set(cons, PM_DEVICE_STATE_ACTIVE);  
  }
  printk("Exit System OFF\n");
  //gpio_pin_set_dt(&led,false);
  //bt_mesh_resume();
}

static void lpn_sleep(){
    printk("Enter System OFF\n");
    //Reenable Interrupt
    buttons_locked = false;
    nrf_gpiote_event_clear(NRF_GPIOTE, NRF_GPIOTE_EVENT_PORT);
    nrf_gpiote_int_enable(NRF_GPIOTE, GPIOTE_INTENSET_PORT_Msk); 
    //bt_mesh_suspend(); 
    /* 
    clk = device_get_binding(CLOCK_LABEL);
    if (clk == NULL)
    {
      printk("No Clock Device found\n");
    } else {
      printk("Clock Device found\n"); 
      clock_control_off(clk,CLOCK_CONTROL_NRF_SUBSYS_HF);
      //clock_control_off(clk,CLOCK_CONTROL_NRF_SUBSYS_LF);
      printk("Clocks disabled\n"); 
    }
    */
    cons = device_get_binding(CONSOLE_LABEL);
    if (cons == NULL)
    {
      printk("No UART Device found\n");
    } else {
      pm_device_state_set(cons, PM_DEVICE_STATE_SUSPENDED);  
    }
    
    //gpio_pin_set_dt(&led,true); 
    
    //pm_power_state_force((struct pm_state_info){PM_STATE_SOFT_OFF, 0, 0});
}

static void lpn_app_established(uint16_t net_idx, uint16_t friend_addr,
					uint8_t queue_size, uint8_t recv_win)
{
  printk("LPN Established\n");
  lpn_sleep();
}

static void lpn_app_polled(uint16_t net_idx, uint16_t friend_addr, bool retry)
{
  printk("LPN Polled\n");
  lpn_sleep();
}

BT_MESH_LPN_CB_DEFINE(lpn_cb_app) = {
	.established = lpn_app_established,
	.polled = lpn_app_polled,
};






/* ------------------- Main App ---------------------------- */

void main(void)
{
  printk("Init Application\n");
  leds_init();
  buttons_init();
  lpn_app_init();
  bluetooth_mesh_init();
  printk("Starting Application\n");
}
