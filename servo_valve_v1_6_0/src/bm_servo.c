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

void bm_init_servo(void){

    	pwm = DEVICE_DT_GET(PWM_CTLR);
	if (!device_is_ready(pwm)) {
		printk("Error: PWM device %s is not ready\n", pwm->name);
		return;
	}

}

void do_test(void)
{
    uint32_t pulse_width = CLOSED_PULSE_USEC;
	enum direction dir = CLOSED;
	int ret;
	while (1) {
		ret = pwm_pin_set_usec(pwm, PWM_CHANNEL, PERIOD_USEC, pulse_width, 0);
		if (ret < 0) {
			printk("Error %d: failed to set pulse width\n", ret);
			return;
		}

		if (dir == CLOSED) {
            pulse_width = OPEND_PULSE_USEC;
            dir = OPEND;
		} else {
            pulse_width = CLOSED_PULSE_USEC;
            dir = CLOSED;

		}

		k_sleep(K_SECONDS(3));
	}
}