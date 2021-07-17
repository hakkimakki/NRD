/* Influxdb Measurments */

#include <zephyr.h>
#include <sys/printk.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(bm_influxdb);
#include <bm_influxdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



/**
 * @brief  Get the Measurment Index by its name
 * 
 * @param name Name of the measurment
 * 
 * @return index of Array if found. -1 if not found 
 * 
 */
int get_meas_from_name(char * name){
	for (int i = 0; i < NUMBER_OF_MEASURMENTS; i++)
	{
		if (strcmp(name,measurments[i].measurment_name)==0)
		{
			return i;
		}		
	}
	return -1;	
}