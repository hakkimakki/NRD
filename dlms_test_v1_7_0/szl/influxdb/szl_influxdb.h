/** @file
 * @brief Simple Influxdb
 *
 * A simple influxdb. 
 */

/*
 * Copyright (c) 2021 Raffael Anklin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SZL_INFLUXDB_H_
#define SZL_INFLUXDB_H_

#include <zephyr.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief  Read one ADC Channel
 *
 * @param  channel: channel id.
 *
 * @retval adc value or -123 on Bad Read.
 */
int16_t readOneChannel(int channel);


#ifdef __cplusplus
}
#endif

#endif /* SZL_UART_H_ */
