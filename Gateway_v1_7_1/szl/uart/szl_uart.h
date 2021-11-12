/** @file
 * @brief Simple UART interface header file.
 *
 * A simple interface to interact with UART. Multiple contexts can be defined which are bound to one uart device. 
 * 
 * Prepare a interfaces with szl_uart_register(...)
 *
 * Rx Poll with szl_uart_recv(...)
 * Rx Interrupt by taking the ctx->rx_sem
 * Tx Send data with szl_uart_send(...)
 *
 */

/*
 * Copyright (c) 2021 Raffael Anklin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SZL_UART_H_
#define SZL_UART_H_

#include <kernel.h>
#include <sys/ring_buffer.h>
#include <drivers/uart.h>

#ifdef __cplusplus
extern "C" {
#endif

struct szl_uart_context {
    /* uart device */
	const struct device *uart_dev;
    /* default uart settings */
    struct uart_config uart_conf;
	/* rx data ring buffer */
	struct ring_buf rx_rb;
    uint8_t rx_ring_buf_buf[CONFIG_SZL_UART_RX_RING_BUF_LEN];
    /* rx semaphore given on RX interrupt */
	struct k_sem rx_sem;
};

/**
 * @brief  Gets szl_uart context by id.
 *
 * @param  id: szl_uart context id.
 *
 * @retval szl_uart context or NULL.
 */
struct szl_uart_context *szl_uart_context_from_id(int id);

/**
 * @brief  Get received data.
 *
 * @param  *ctx: szl_uart context.
 * @param  *buf: buffer to copy the received data to.
 * @param  size: buffer size.
 * @param  *bytes_read: amount of received bytes
 *
 * @retval 0 if ok, < 0 if error.
 */
int szl_uart_recv(struct szl_uart_context *ctx,
		      uint8_t *buf, size_t size, size_t *bytes_read);

/**
 * @brief  Sends the data over specified szl_uart context.
 *
 * @param  *ctx: szl_uart context.
 * @param  *buf: buffer with the data to send.
 * @param  size: the amount of data to send.
 *
 * @retval 0 if ok, < 0 if error.
 */
int szl_uart_send(struct szl_uart_context *ctx,
		      const uint8_t *buf, size_t size);

/**
 * @brief  Registers szl_uart context.
 *
 * @note   Acquires szl_uarts device, and prepares the context to be used.
 *
 * @param  *ctx: szl_uart context to register.
 * @param  *uart_dev_name: name of communication device for the szl_uart context.
 *
 * @retval 0 if ok, < 0 if error.
 */
int szl_uart_register(struct szl_uart_context *ctx,
			  const char *uart_dev_name);

int szl_uart_sleep(struct szl_uart_context *ctx);

int szl_uart_wake(struct szl_uart_context *ctx);

#ifdef __cplusplus
}
#endif

#endif /* SZL_UART_H_ */
