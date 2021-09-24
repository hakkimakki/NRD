/*
This file is part of Gateway.

Gateway is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Gateway is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Gateway.  If not, see <http://www.gnu.org/licenses/>.
*/

/* AUTHOR 	 :    Raffael Anklin       */


#include <zephyr.h>
#include <stdio.h>
#include <drivers/uart.h>
#include <string.h>
#include "sz_dlms_push_parser_lg450.h"




/**
 * @brief DLMS Push Listener LG450 does Parse Push Messeges HDLC (M-BUS) tested with a Landys+Gyr e450 Smart Meter. 
 * 
 */

/////////////////////////////////////////////////////////////////////////////
//Serial port settings.
#define UART_NAME "UART_1"
static const struct device *uart_dev;
static bool frame_rdy;
static int characters;

static void uart_isr(const struct device *x, void *user_data)
{
  uart_irq_update(x);
  if (uart_irq_rx_ready(x)) {
    char ch;
    int ret = uart_fifo_read(x, &ch, 1);
    if (ret != 0)
    {
        dlms_push_parser_lge450_parse(&ch,ret);        
    }
  }
}

int dlms_push_parser_lge450_uart_init()
{
  int err;
  uart_dev = device_get_binding(UART_NAME);
  if (uart_dev == NULL) {
    printf("Cannot bind %s\n", UART_NAME);
    return EINVAL;
  }
  err = uart_err_check(uart_dev);
  if (err) {
    printf("UART check failed\n");
    return EINVAL;
  }
  if (!device_is_ready(uart_dev)) {
    printf("UART not ready\n");
    return ENODEV;
  }
  uart_irq_rx_enable(uart_dev);
  uart_irq_callback_set(uart_dev, uart_isr);
  return err;
}