/** @file
 * @brief Simple ADC control
 *
 * A simple interface to read adc samples. 
 */

/*
 * Copyright (c) 2021 Raffael Anklin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>

#include <string.h>

#include <szl_adc.h>


//For ADC
#include <drivers/adc.h>

/* Default COnfiguration (should work with most ADCs */
//#define ADC_NODE		DT_PHANDLE(DT_PATH(zephyr_user), io_channels)
#define ADC_NODE_LABEL		"ADC_0"
#define ADC_RESOLUTION		12
#define ADC_GAIN			ADC_GAIN_1
#define ADC_REFERENCE		ADC_REF_INTERNAL
#define ADC_ACQUISITION_TIME	ADC_ACQ_TIME_DEFAULT //ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 1)
#define BUFFER_SIZE			6
#define BAD_ANALOG_READ -123

static bool _IsInitialized = false;
static uint8_t _LastChannel = 250;
static int16_t m_sample_buffer[BUFFER_SIZE];

// the channel configuration with channel not yet filled in
static struct adc_channel_cfg m_1st_channel_cfg = {
	.gain             = ADC_GAIN,
	.reference        = ADC_REFERENCE,
	.acquisition_time = ADC_ACQUISITION_TIME,
	.channel_id       = 0, // gets set during init
	.differential	  = 0
};

// return device* for the adc
static const struct device* getAdcDevice(void)
{
	return device_get_binding(ADC_NODE_LABEL);
}

// initialize the adc channel
static const struct device* init_adc(int channel)
{
	int ret;
	const struct device *adc_dev = getAdcDevice();
  if (!device_is_ready(adc_dev)) {
		printk("ADC device not found\n");
		adc_dev = NULL;
	}
	if(_LastChannel != channel)
	{
		_IsInitialized = false;
		_LastChannel = channel;
	}

	if ( adc_dev != NULL && !_IsInitialized)
	{
		// strangely channel_id gets the channel id and input_positive gets id+1
		m_1st_channel_cfg.channel_id = channel;
		ret = adc_channel_setup(adc_dev, &m_1st_channel_cfg);
		if(ret != 0)
		{
			//LOG_INF("Setting up of the first channel failed with code %d", ret);
      printk("Error\n");
			adc_dev = NULL;
		}
		else
		{
			_IsInitialized = true;	// we don't have any other analog users
      printk("ADC Initialized\n");
		}
	}
	
	memset(m_sample_buffer, 0, sizeof(m_sample_buffer));
	return adc_dev;
}

// ------------------------------------------------
// read one channel of adc
// ------------------------------------------------
int16_t readOneChannel(int channel)
{
	const struct adc_sequence sequence = {
		.options     = NULL,				// extra samples and callback
		.channels    = BIT(channel),		// bit mask of channels to read
		.buffer      = m_sample_buffer,		// where to put samples read
		.buffer_size = sizeof(m_sample_buffer),
		.resolution  = ADC_RESOLUTION,		// desired resolution
		.oversampling = 0,					// don't oversample
		.calibrate = 0						// don't calibrate
	};

	int ret;
	int16_t sample_value = BAD_ANALOG_READ;
	const struct device *adc_dev = init_adc(channel);
	if (adc_dev)
	{
		ret = adc_read(adc_dev, &sequence);
		if(ret == 0)
		{
			sample_value = m_sample_buffer[0];
		}
	}
	return sample_value;
}