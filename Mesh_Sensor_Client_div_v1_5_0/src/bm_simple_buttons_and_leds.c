/*
This file is part of Benchmark-Shared-Library.

Benchmark-Shared-Library is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Benchmark-Shared-Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Benchmark-Shared-Library.  If not, see <http://www.gnu.org/licenses/>.
*/

/* AUTHOR ZEPHYR_BLE_MESH  :   Raffael Anklin        */
/* AUTHOR NRF_SDK_ZIGBEE   :   Cyrill Horath        */

#include "bm_simple_buttons_and_leds.h"


struct device *dev_led0, *dev_led1, *dev_led2, *dev_led3, *dev_button0;
bool led0_is_on, led1_is_on, led2_is_on, led3_is_on = true;
bool button0_toggel_state = true;
int ret;

static struct gpio_callback button_cb_data;

static struct k_delayed_work buttons_debounce;

static void (*button0_callback)();

static void buttons_debounce_fn(struct k_work *work) {
  button0_toggel_state = !button0_toggel_state;
  button0_callback();
}

void button_pressed(struct device *dev, struct gpio_callback *cb,
    uint32_t pins) {
  if (dev == dev_button0) {
    k_delayed_work_submit(&buttons_debounce, K_MSEC(170)); // Debounce the Button
                                                           //button0_callback();
  }
  //printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
}

/* Init the Buttons */
void bm_init_buttons(void (*button0_cb)()) {
  dev_button0 = device_get_binding(SW0_GPIO_LABEL);
  if (dev_button0 == NULL) {
    printk("Error: didn't find %s device\n", SW0_GPIO_LABEL);
    return;
  }
  ret = gpio_pin_configure(dev_button0, SW0_GPIO_PIN, SW0_GPIO_FLAGS);
  if (ret != 0) {
    printk("Error %d: failed to configure %s pin %d\n",
        ret, SW0_GPIO_LABEL, SW0_GPIO_PIN);
    return;
  }
  ret = gpio_pin_interrupt_configure(dev_button0,
      SW0_GPIO_PIN,
      GPIO_INT_EDGE_TO_ACTIVE);
  if (ret != 0) {
    printk("Error %d: failed to configure interrupt on %s pin %d\n",
        ret, SW0_GPIO_LABEL, SW0_GPIO_PIN);
    return;
  }

  gpio_init_callback(&button_cb_data, button_pressed, BIT(SW0_GPIO_PIN));
  gpio_add_callback(dev_button0, &button_cb_data);
  printk("Set up button at %s pin %d\n", SW0_GPIO_LABEL, SW0_GPIO_PIN);
  button0_callback = button0_cb;

  k_delayed_work_init(&buttons_debounce, buttons_debounce_fn);
}


/* Init the Leds */
void bm_init_leds() {
  dev_led0 = device_get_binding(LED0);
  if (dev_led0 == NULL) {
    printk("Error no LED0 found");
    return;
  }
  ret = gpio_pin_configure(dev_led0, PIN_LED0, GPIO_OUTPUT_INACTIVE | FLAGS_LED0);
  if (ret < 0) {
    printk("Error in configuration of led0 pin (err %d)", ret);
    return;
  }
  dev_led1 = device_get_binding(LED1);
  if (dev_led1 == NULL) {
    printk("Error no LED1 found");
    return;
  }
  ret = gpio_pin_configure(dev_led1, PIN_LED1, GPIO_OUTPUT_INACTIVE | FLAGS_LED1);
  if (ret < 0) {
    printk("Error in configuration of led1 pin (err %d)", ret);
    return;
  }
  dev_led2 = device_get_binding(LED2);
  if (dev_led2 == NULL) {
    printk("Error no LED2 found");
    return;
  }
  ret = gpio_pin_configure(dev_led2, PIN_LED2, GPIO_OUTPUT_INACTIVE | FLAGS_LED2);
  if (ret < 0) {
    printk("Error in configuration of led2 pin (err %d)", ret);
    return;
  }
  dev_led3 = device_get_binding(LED3);
  if (dev_led3 == NULL) {
    printk("Error no LED3 found");
    return;
  }
  ret = gpio_pin_configure(dev_led3, PIN_LED3, GPIO_OUTPUT_INACTIVE | FLAGS_LED3);
  if (ret < 0) {
    printk("Error in configuration of led3 pin (err %d)", ret);
    return;
  }
}



/* Set LED0. pca10059 -> Green LED */
void bm_led0_set(bool state) {
  gpio_pin_set(dev_led0, PIN_LED0, (int)state);
  led0_is_on = state;
}

/* Get LED0 */
bool bm_led0_get() {
  return led0_is_on;
}

/* Set LED1. pca10059 -> Red LED (RGB) */
void bm_led1_set(bool state) {
  gpio_pin_set(dev_led1, PIN_LED1, (int)state);
  led1_is_on = state;
}

/* Get LED1 */
bool bm_led1_get() {
  return led1_is_on;
}

/* Set LED2. pca10059 -> Green LED (RGB) */
void bm_led2_set(bool state) {
  gpio_pin_set(dev_led2, PIN_LED2, (int)state);
  led2_is_on = state;
}

/* Get LED2 */
bool bm_led2_get() {
  return led2_is_on;
}

/* Set LED3. pca10059 -> Blue LED (RGB)  */
void bm_led3_set(bool state) {
  gpio_pin_set(dev_led3, PIN_LED3, (int)state);
  led3_is_on = state;
}

/* Get LED3 */
bool bm_led3_get() {
  return led3_is_on;
}



/* Get BUTTON0 Toggled State*/
bool bm_button0_toggle_state_get() {
  //gpio_pin_get(dev_led0, PIN_LED0, (int)state);
  return button0_toggel_state;
}

/* Set BUTTON0 Toggled State*/
void bm_button0_toggle_state_set(bool newstate) {
  //gpio_pin_get(dev_led0, PIN_LED0, (int)state);
  button0_toggel_state = newstate;
}


