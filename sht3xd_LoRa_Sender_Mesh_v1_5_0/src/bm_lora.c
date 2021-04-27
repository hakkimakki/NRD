
#include <device.h>
#include <drivers/lora.h>
#include <errno.h>
#include <sys/util.h>
#include <zephyr.h>
#include <logging/log.h>

#include "bm_lora.h"

#define DEFAULT_RADIO_NODE DT_ALIAS(lora0)
BUILD_ASSERT(DT_NODE_HAS_STATUS(DEFAULT_RADIO_NODE, okay),
             "No default LoRa radio specified in DT");
#define DEFAULT_RADIO DT_LABEL(DEFAULT_RADIO_NODE)

#define MAX_DATA_LEN 255

struct device *lora_dev;
struct lora_modem_config config;
static int ret, len;
uint8_t data[MAX_DATA_LEN] = {0};
int16_t rssi;
int8_t snr;

void bm_lora_init()
{

    lora_dev = device_get_binding(DEFAULT_RADIO);
    if (!lora_dev)
    {
        printk("%s Device not found\n", DEFAULT_RADIO);
        return;
    }

    config.frequency = 865100000;
    config.bandwidth = BW_125_KHZ;
    config.datarate = SF_10;
    config.preamble_len = 8;
    config.coding_rate = CR_4_5;
    config.tx_power = 4;
    config.tx = true;

    ret = lora_config(lora_dev, &config);
    if (ret < 0)
    {
        printk("LoRa config failed\n");
        return;
    }
}

void bm_lora_send(uint8_t *data, uint32_t data_len)
{
    if (lora_dev == NULL)
    {
        printk("Could not get LoRa device\n");
        return;
    }

    //Prepare Device for Sending
    config.tx_power = 4;
    config.tx = true;

    ret = lora_config(lora_dev, &config);
    if (ret < 0)
    {
        printk("LoRa config failed\n");
        return;
    }
    ret = lora_send(lora_dev, data, data_len);
    if (ret < 0)
    {
        printk("LoRa send failed\n");
        return;
    }

    printk("Data sent!\n");
}

uint32_t bm_lora_recv(uint8_t *data)
{
    if (lora_dev == NULL)
    {
        printk("Could not get LoRa device\n");
        return 0;
    }

    //Prepare Device for Receiving
    config.tx_power = 14;
    config.tx = false;

    ret = lora_config(lora_dev, &config);
    if (ret < 0)
    {
        printk("LoRa config failed\n");
        return 0;
    }
    /* Block until data arrives */
		len = lora_recv(lora_dev, data, MAX_DATA_LEN, K_FOREVER,
				&rssi, &snr);
		if (len < 0) {
			printk("LoRa receive failed\n");
			return 0;
		}

		printk("Received data: %s (RSSI:%ddBm, SNR:%ddBm)\n",
			log_strdup(data), rssi, snr);
            return len;
}