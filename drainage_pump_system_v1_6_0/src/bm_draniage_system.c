/*
 * Copyright (c) 2016 Intel Corporation
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Drainage System with Flowchart
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <bm_draniage_system.h>
#include <bm_blemesh_model_handler.h>
#include <bluetooth/mesh/models.h>
#include <bm_simple_buttons_and_leds.h>

typedef enum {INIT,
				WAIT,
				CLOSE_ALL,
				DRAIN_VALVES,
				OPEN_ALL}  state_t;
 
state_t state = INIT;

int16_t drain_intervall_h = 12;
int16_t valve_drain_time_s[NUMBER_OF_VALVES] = {
	[0 ... NUMBER_OF_VALVES -1] = 10,
};

static int ret;
static struct bt_mesh_onoff_set set = {.on_off = false,};

void bm_drainage_stateMachine()
{
switch( state ) {
	case INIT:
		printk("State: INIT\n");
		bm_pumpdrain_set(false);
		bm_valvesdrain_set(false);
		k_sleep(K_MSEC(500));
      	state = CLOSE_ALL;
      	break;

    case CLOSE_ALL:
		printk("State: CLOSE_ALL\n");
		bm_valvesdrain_set(true);
		k_sleep(K_MSEC(2000));
	  	for (size_t i = 0; i < NUMBER_OF_VALVES; i++)
	  	{
			set.on_off = false;
			ret = bt_mesh_onoff_cli_set_unack(&valve_drain_on_off_cli[i],NULL,&set);
			k_sleep(K_MSEC(100));
	  	}	  
      	state = DRAIN_VALVES;
      	break;    
	
	case DRAIN_VALVES:
		printk("State: DRAIN_VALVES\n");
		bm_pumpdrain_set(true);
	  	for (size_t i = 0; i < NUMBER_OF_VALVES; i++)
	  	{
			set.on_off = true;
			ret = bt_mesh_onoff_cli_set_unack(&valve_drain_on_off_cli[i],NULL,&set);
			k_sleep(K_MSEC(valve_drain_time_s[i]*1000));
			set.on_off = false;
			ret = bt_mesh_onoff_cli_set_unack(&valve_drain_on_off_cli[i],NULL,&set);
			k_sleep(K_MSEC(500));
	  	}	  
      	state = OPEN_ALL;
      	break; 
	
	case OPEN_ALL:
		printk("State: OPEN_ALL\n");
	  	for (size_t i = 0; i < NUMBER_OF_VALVES; i++)
	  	{
			set.on_off = true;
			ret = bt_mesh_onoff_cli_set_unack(&valve_drain_on_off_cli[i],NULL,&set);
			k_sleep(K_MSEC(100));
	  	}	  
      	state = WAIT;
      	break; 
	
	case WAIT:
		printk("State: WAIT\n");
		bm_valvesdrain_set(false);
		bm_pumpdrain_set(false);
		printk("Wait for %u hours\n",drain_intervall_h);
      	k_sleep(K_HOURS(drain_intervall_h));
      	state = CLOSE_ALL;
      	break;
  }
}

