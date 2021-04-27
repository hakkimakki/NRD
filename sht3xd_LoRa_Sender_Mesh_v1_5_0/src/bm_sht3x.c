
#include <zephyr.h>
#include <device.h>
#include <drivers/sensor.h>
#include <stdio.h>

#include "bm_sht3x.h"

int rc;
struct device *dev;

void sht3x_init()
{

    dev = device_get_binding("SHT3XD");

    if (dev == NULL)
    {
        printf("Could not get SHT3XD device\n");
        return;
    }
}

void sht3x_temp_hum_get(struct sensor_value *temp, struct sensor_value *hum)
{
    if (dev == NULL)
    {
        printf("Could not get SHT3XD device\n");
        return;
    }
    if (rc == 0 && temp != NULL)
    {
        rc = sensor_sample_fetch(dev); //Only Fetch When Temperatur is Requested -> BT Mesh Model will always first get Temperatur
        rc = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP,
                                temp);
        printf("SHT3XD: %.2f Cel\n",
               sensor_value_to_double(temp));
    }
    if (rc == 0 && hum != NULL)
    {
        rc = sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY,
                                hum);
        printf("SHT3XD: %0.2f %%RH\n",
               sensor_value_to_double(hum));
    }
    if (rc != 0)
    {
        printf("SHT3XD: failed: %d\n", rc);
    }
}
