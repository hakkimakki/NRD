/*
 * Copyright (c) 2016 Intel Corporation
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Sample app to demonstrate PWM.
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/pwm.h>
#include <bm_simple_buttons_and_leds.h>

#define PWM_LED0_NODE	DT_ALIAS(pwm_servo)

#if DT_NODE_HAS_STATUS(PWM_LED0_NODE, okay)
#define PWM_CTLR	DT_PWMS_CTLR(PWM_LED0_NODE)
#define PWM_CHANNEL	DT_PWMS_CHANNEL(PWM_LED0_NODE)
#else
#error "Unsupported board: pwm-led0 devicetree alias is not defined"
#define PWM_CTLR	DT_INVALID_NODE
#define PWM_CHANNEL	0
#define PWM_FLAGS	0
#endif



#define PERIOD_USEC	(20U * USEC_PER_MSEC)
#define STEP_USEC	10
#define CLOSED_PULSE_USEC	(177U * 100)
#define OPEND_PULSE_USEC	(187U * 100)

enum direction {
	CLOSED,
	OPEND,
};

const struct device *pwm;

bool bm_status_servo_valve;


static struct k_work_delayable leds_off_work;

static void do_leds_off()
{
	bm_led0_set(false);
	bm_led1_set(false);
	bm_led2_set(false);
	bm_led3_set(false);
}

static void leds_off(struct k_work *work)
{
	do_leds_off();
}


void bm_init_servo(void){

    	pwm = DEVICE_DT_GET(PWM_CTLR);
	if (!device_is_ready(pwm)) {
		printk("Error: PWM device %s is not ready\n", pwm->name);
		return;
	}	
	/* initialize work item for turning LEDS OFF */
	k_work_init_delayable(&leds_off_work, leds_off);
	do_leds_off();
	bm_led3_set(true);
	k_work_reschedule(&leds_off_work, K_MSEC(60*1000));
}

void bm_open_servo_valve(void)
{
	static int ret;
	ret = pwm_pin_set_usec(pwm, PWM_CHANNEL, PERIOD_USEC, OPEND_PULSE_USEC, 0);
	if (ret < 0) {
		printk("Error %d: failed to set pulse width\n", ret);
		return;
	}
	bm_status_servo_valve = true;
	do_leds_off();
	bm_led2_set(true);
	k_work_reschedule(&leds_off_work, K_MSEC(60*1000));
}

void bm_close_servo_valve(void)
{
	static int ret;
	ret = pwm_pin_set_usec(pwm, PWM_CHANNEL, PERIOD_USEC, CLOSED_PULSE_USEC, 0);
	if (ret < 0) {
		printk("Error %d: failed to set pulse width\n", ret);
		return;
	}
	bm_status_servo_valve = false;
	do_leds_off();
	bm_led1_set(true);
	k_work_reschedule(&leds_off_work, K_MSEC(60*1000));
}
