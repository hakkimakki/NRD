/*
 * Copyright (c) 2017 Raffael Anklin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* ---------- Led ------------------- */
#include <zephyr.h>
#include <hal/nrf_gpio.h>
#include <nrfx_gpiote.h>
#include <hal/nrf_gpiote.h>

//Init Reset Button
static void leds_init()
{
  nrf_gpio_cfg_output(DT_GPIO_PIN(DT_ALIAS(led0), gpios));
  nrf_gpio_pin_set(DT_GPIO_PIN(DT_ALIAS(led0), gpios));
}

/* ---------- Buttons ------------------- */
static struct k_work_delayable buttons_debounce;

static void mesh_model_button_handler();
static void lpn_wakeup();
static void lpn_sleep();

static bool buttons_locked;
static uint32_t pin_latches;

static void buttons_debounce_fn(struct k_work *work)
{
  lpn_wakeup();
  mesh_model_button_handler();
}

static void gpiote_isr(const void *irq_handler)
{
  nrf_gpiote_int_disable(NRF_GPIOTE, GPIOTE_INTENSET_PORT_Msk); 
  nrf_gpiote_event_clear(NRF_GPIOTE, NRF_GPIOTE_EVENT_PORT); 
  nrf_gpio_latches_read_and_clear(0,1,&pin_latches); 
  printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
  if (!buttons_locked){
    buttons_locked = true;
    k_work_reschedule(&buttons_debounce, K_MSEC(100)); // Debounce the Button
  }
}

//Init Reset Button
static void buttons_init()
{
  k_work_init_delayable(&buttons_debounce, buttons_debounce_fn);

  /* Configure to generate PORT event (wakeup) on buttons press. */
  nrf_gpio_cfg_sense_input(DT_GPIO_PIN(DT_ALIAS(sw1on), gpios),NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);
  nrf_gpio_cfg_sense_input(DT_GPIO_PIN(DT_ALIAS(sw2on), gpios),NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);
  nrf_gpio_cfg_sense_input(DT_GPIO_PIN(DT_ALIAS(sw3on), gpios),NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);
  nrf_gpio_cfg_sense_input(DT_GPIO_PIN(DT_ALIAS(sw4on), gpios),NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);
  nrf_gpio_cfg_sense_input(DT_GPIO_PIN(DT_ALIAS(sw1off), gpios),NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);
  nrf_gpio_cfg_sense_input(DT_GPIO_PIN(DT_ALIAS(sw2off), gpios),NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);
  nrf_gpio_cfg_sense_input(DT_GPIO_PIN(DT_ALIAS(sw3off), gpios),NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);
  nrf_gpio_cfg_sense_input(DT_GPIO_PIN(DT_ALIAS(sw4off), gpios),NRF_GPIO_PIN_PULLUP,NRF_GPIO_PIN_SENSE_LOW);

  /* Connect GPIOTE_0 IRQ to nrfx_gpiote_irq_handler */
	IRQ_CONNECT(DT_IRQN(DT_NODELABEL(gpiote)),
		    DT_IRQ(DT_NODELABEL(gpiote), priority),
		    gpiote_isr, NULL, 0);

    NRFX_IRQ_PRIORITY_SET(nrfx_get_irq_number(NRF_GPIOTE), 0);
    NRFX_IRQ_ENABLE(nrfx_get_irq_number(NRF_GPIOTE));
    nrf_gpiote_event_clear(NRF_GPIOTE, NRF_GPIOTE_EVENT_PORT);
    nrf_gpiote_int_enable(NRF_GPIOTE, GPIOTE_INTENSET_PORT_Msk);  
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
  static int i = -1;
  static int err;
  i = -1;
  
  printk("L: %u\n",pin_latches);

  if (pin_latches & (1 << DT_GPIO_PIN(DT_ALIAS(sw1on), gpios)))
  {
    i = 0;
    buttons[i].status = true;
  } else if (pin_latches & (1 << DT_GPIO_PIN(DT_ALIAS(sw1off), gpios)))
  {
    i = 0;
    buttons[i].status = false;
  } else if (pin_latches & (1 << DT_GPIO_PIN(DT_ALIAS(sw2on), gpios)))
  {
    i = 1;
    buttons[i].status = true;
  } else if (pin_latches & (1 << DT_GPIO_PIN(DT_ALIAS(sw2off), gpios)))
  {
    i = 1;
    buttons[i].status = false;
  } else if (pin_latches & (1 << DT_GPIO_PIN(DT_ALIAS(sw3on), gpios)))
  {
    i = 2;
    buttons[i].status = true;
  } else if (pin_latches & (1 << DT_GPIO_PIN(DT_ALIAS(sw3off), gpios)))
  {
    i = 2;
    buttons[i].status = false;
  } else if (pin_latches & (1 << DT_GPIO_PIN(DT_ALIAS(sw4on), gpios)))
  {
    i = 3;
    buttons[i].status = true;
  } else if (pin_latches & (1 << DT_GPIO_PIN(DT_ALIAS(sw4off), gpios)))
  {
    i = 3;
    buttons[i].status = false;
  } else 
  {
    printk("Error no button pressed\n");
  }
  
  if (bt_mesh_is_provisioned() && (i >= 0)) {    
    struct bt_mesh_onoff_set set = {.on_off = buttons[i].status,};
    err = bt_mesh_onoff_cli_set_unack(&buttons[i].client,NULL, &set);
    if (err) {
        printk("OnOff %d set failed: %d\n", i + 1, err);
    }
    err = bt_mesh_lpn_poll();
    if (err != 0){
      printk("Poll Error %d\n",err);
    }
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
  
  if ((nrf_gpio_pin_read(DT_GPIO_PIN(DT_ALIAS(sw1on), gpios)) == false) ){
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
  cons = device_get_binding(CONSOLE_LABEL);
  if (cons == NULL)
  {
    printk("No UART Device found\n");
  } else {
    pm_device_state_set(cons, PM_DEVICE_STATE_ACTIVE);  
  }
  printk("Exit System OFF\n");
  nrf_gpio_pin_set(DT_GPIO_PIN(DT_ALIAS(led0), gpios)); 
}

static void lpn_sleep(){
    printk("Enter System OFF\n");
    nrf_gpio_pin_clear(DT_GPIO_PIN(DT_ALIAS(led0), gpios)); 
    //Reenable Interrupt
    buttons_locked = false;
    nrf_gpiote_event_clear(NRF_GPIOTE, NRF_GPIOTE_EVENT_PORT);
    nrf_gpio_latches_read_and_clear(0,1,&pin_latches); 
    nrf_gpiote_int_enable(NRF_GPIOTE, GPIOTE_INTENSET_PORT_Msk); 
    cons = device_get_binding(CONSOLE_LABEL);
    if (cons == NULL)
    {
      printk("No UART Device found\n");
    } else {
      pm_device_state_set(cons, PM_DEVICE_STATE_SUSPENDED);  
    }   
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
