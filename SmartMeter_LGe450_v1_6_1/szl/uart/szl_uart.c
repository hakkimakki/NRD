/** @file
 * @brief Simple UART interface control
 *
 * A simple interface to interact with UART. 
 */

/*
 * Copyright (c) 2021 Raffael Anklin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <init.h>
#include <drivers/uart.h>

#include <logging/log.h>

LOG_MODULE_REGISTER(szl_uart, CONFIG_LOG_DEFAULT_LEVEL);

#include "szl_uart.h"

#define MAX_MDM_CTX	CONFIG_SZL_UART_MAX_CONTEXTS
#define MAX_READ_SIZE	128

static struct szl_uart_context *contexts[MAX_MDM_CTX];

/**
 * @brief  Finds szl_uart context which manages provided device.
 *
 * @param  *dev: device used by the szl_uart context.
 *
 * @retval Szl UART context or NULL.
 */
static struct szl_uart_context *context_from_dev(const struct device *dev)
{
	int i;

	for (i = 0; i < MAX_MDM_CTX; i++) {
		if (contexts[i] && contexts[i]->uart_dev == dev) {
			return contexts[i];
		}
	}

	return NULL;
}

/**
 * @brief  Persists szl_uart context if there is a free place.
 *
 * @note   Amount of stored szl_uart contexts is determined by
 *         MAX_MDM_CTX.
 *
 * @param  *ctx: szl_uart context to persist.
 *
 * @retval 0 if ok, < 0 if error.
 */
static int szl_uart_get(struct szl_uart_context *ctx)
{
	int i;

	for (i = 0; i < MAX_MDM_CTX; i++) {
		if (!contexts[i]) {
			contexts[i] = ctx;
			return 0;
		}
	}

	return -ENOMEM;
}

/**
 * @brief  Drains UART.
 *
 * @note   Discards remaining data.
 *
 * @param  *ctx: szl_uart context.
 *
 * @retval None.
 */
static void szl_uart_flush(struct szl_uart_context *ctx)
{
	uint8_t c;

	__ASSERT(ctx, "invalid ctx");
	__ASSERT(ctx->uart_dev, "invalid ctx device");

	while (uart_fifo_read(ctx->uart_dev, &c, 1) > 0) {
		continue;
	}
}

/**
 * @brief  Receiver UART interrupt handler.
 *
 * @note   Fills contexts ring buffer with received data.
 *         When ring buffer is full the data is discarded.
 *
 * @param  *uart_dev: uart device.
 *
 * @retval None.
 */
static void szl_uart_isr(const struct device *uart_dev, void *user_data)
{
	struct szl_uart_context *ctx;
	int rx, ret;
	static uint8_t read_buf[MAX_READ_SIZE];

	ARG_UNUSED(user_data);

	/* lookup the device */
	ctx = context_from_dev(uart_dev);
	if (!ctx) {
		return;
	}

	/* get all of the data off UART as fast as we can */
	while (uart_irq_update(ctx->uart_dev) &&
	       uart_irq_rx_ready(ctx->uart_dev)) {
		rx = uart_fifo_read(ctx->uart_dev, read_buf, sizeof(read_buf));
		if (rx > 0) {
			ret = ring_buf_put(&ctx->rx_rb, read_buf, rx);
			if (ret != rx) {
				LOG_ERR("Rx buffer doesn't have enough space. "
						"Bytes pending: %d, written: %d",
						rx, ret);
				szl_uart_flush(ctx);
				k_sem_give(&ctx->rx_sem);
				break;
			}
			k_sem_give(&ctx->rx_sem);
		}
	}
}

/**
 * @brief  Configures szl_uart context and assigned device.
 *
 * @param  *ctx: szl_uart context.
 *
 * @retval None.
 */
static void szl_uart_setup(struct szl_uart_context *ctx)
{
	__ASSERT(ctx, "invalid ctx");

	uart_irq_rx_disable(ctx->uart_dev);
	uart_irq_tx_disable(ctx->uart_dev);
	szl_uart_flush(ctx);
	uart_irq_callback_set(ctx->uart_dev, szl_uart_isr);
	uart_irq_rx_enable(ctx->uart_dev);
}

struct szl_uart_context *szl_uart_context_from_id(int id)
{
	if (id >= 0 && id < MAX_MDM_CTX) {
		return contexts[id];
	} else {
		return NULL;
	}
}

int szl_uart_recv(struct szl_uart_context *ctx,
		      uint8_t *buf, size_t size, size_t *bytes_read)
{
	if (!ctx) {
		return -EINVAL;
	}

	if (size == 0) {
		*bytes_read = 0;
		return 0;
	}

	*bytes_read = ring_buf_get(&ctx->rx_rb, buf, size);
	return 0;
}

int szl_uart_send(struct szl_uart_context *ctx,
		      const uint8_t *buf, size_t size)
{
	if (!ctx) {
		return -EINVAL;
	}

	if (size == 0) {
		return 0;
	}

	do {
		uart_poll_out(ctx->uart_dev, *buf++);
	} while (--size);

	return 0;
}

int szl_uart_sleep(struct szl_uart_context *ctx)
{
	uart_irq_rx_disable(ctx->uart_dev);
#ifdef PM_DEVICE_STATE_LOW_POWER
	pm_device_state_set(ctx->uart_dev, PM_DEVICE_STATE_LOW_POWER);
#endif
	return 0;
}

int szl_uart_wake(struct szl_uart_context *ctx)
{
#ifdef PM_DEVICE_STATE_LOW_POWER
	pm_device_state_set(ctx->uart_dev, PM_DEVICE_STATE_ACTIVE);
#endif
	uart_irq_rx_enable(ctx->uart_dev);

	return 0;
}

int szl_uart_register(struct szl_uart_context *ctx,
			  const char *uart_dev_name)
{
	int ret;

	if ((!ctx) || (!uart_dev_name)) {
		return -EINVAL;
	}

    ctx->uart_dev = device_get_binding(uart_dev_name);
    
    ctx->uart_conf.baudrate = 115200;
    ctx->uart_conf.parity = UART_CFG_PARITY_NONE;
    ctx->uart_conf.stop_bits = UART_CFG_STOP_BITS_1;
    ctx->uart_conf.data_bits = UART_CFG_DATA_BITS_8;
    ctx->uart_conf.flow_ctrl = UART_CFG_FLOW_CTRL_NONE;

	ret = uart_configure(ctx->uart_dev, &ctx->uart_conf);
	LOG_DBG("Init UART returned code: %d", ret);

	if (!device_is_ready(ctx->uart_dev)) {
		LOG_ERR("Device is not ready: %s",
			ctx->uart_dev ? ctx->uart_dev->name : "<null>");
		return -ENODEV;
	}

	ring_buf_init(&ctx->rx_rb, CONFIG_SZL_UART_RX_RING_BUF_LEN, ctx->rx_ring_buf_buf);
	k_sem_init(&ctx->rx_sem, 0, 1);

	ret = szl_uart_get(ctx);
	if (ret < 0) {
		return ret;
	}

	szl_uart_setup(ctx);
	return 0;
}
