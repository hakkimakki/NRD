/* Influxdb Measurments */

#include <zephyr.h>
#include <sys/printk.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(bm_influxdb);
#include <bm_influxdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* ---------- Metadata ------------------- */
char measurment_uuids[NUMBER_OF_MEASURMENT_UUIDS][MAX_LEN_OF_MEASURMENT_UUID];
uint8_t number_of_measurment_links[NUMBER_OF_MEASURMENT_UUIDS];
uint16_t avg_time_intervalls[NUMBER_OF_MEASURMENT_UUIDS];
uint64_t latest_timestamps[NUMBER_OF_MEASURMENT_UUIDS];
/* ---------- Field Values ------------------- */
char field_values[MAX_NUMBER_OF_FIELDSETS][NUMBER_OF_MEASURMENTS][MAX_LEN_OF_FIELD_VALUE];

/* Helper Pointers */
int measurment_uuid_cnt; //Points to next free measurment_uuid -> Needs Reset Upon Clearing

/* Buffer to enque new measurments */
char measurment_uuid_buf[MAX_LEN_OF_MEASURMENT_UUID];
char field_values_buf[MAX_NUMBER_OF_FIELDSETS][MAX_LEN_OF_FIELD_VALUE];
int field_values_buf_cnt; // POints to next free location
uint64_t timestamp_buf;
K_SEM_DEFINE(measurments_buffer_sem, 0, 1);
K_SEM_DEFINE(measurments_sem, 0, 1);
char *begin;

void begin_meas(char *meas_name, char *field_key, void *field_val, size_t field_val_len, uint64_t *timestamp)
{
	// Check if new tagset doesnt overfit the uuid field with strlen...
	// Check if field_val_len < MAX_LEN_OF_FIELD_VALUE
	/* Safe parameters in buffer */
	if (k_sem_take(&measurments_buffer_sem, K_MSEC(1000)) != 0)
	{
		LOG_ERR("Unable to create new measurment! Buffer in use.");
		return;
	}
	memset(measurment_uuid_buf, 0, sizeof(measurment_uuid_buf)); // Reset Buffer
	memset(field_values_buf, 0, sizeof(field_values_buf));		 // Reset Buffer
	field_values_buf_cnt = 0;									 // Reset Counter
	strcat(measurment_uuid_buf, meas_name);
	strcat(measurment_uuid_buf, ", ");
	strcat(measurment_uuid_buf, field_key);
	strcat(measurment_uuid_buf, "=0 ");
	memcpy(field_values_buf[field_values_buf_cnt], field_val, field_val_len);
	field_values_buf_cnt = field_values_buf_cnt + 1;
	timestamp_buf = *timestamp;
};

void add_tagset(char *tag_key, char *tag_value)
{
	// Check if new tagset doesnt overfit the uuid field with strlen...

	begin = strstr(measurment_uuid_buf, ",");
	if (begin == NULL)
	{
		LOG_ERR("Unable to create new tagset! No began measurment found");
		return;
	}
	// Insert new tagset
	begin = begin + sizeof(",") - 1;
	static int x;
	static char tmp[MAX_LEN_OF_MEASURMENT_UUID];
	memset(tmp, 0, sizeof(tmp));
	x = begin - measurment_uuid_buf;
	strncpy(tmp, measurment_uuid_buf, x);
	strncpy(&tmp[x],  "\0", 1);
	strcat(tmp, tag_key);
	strcat(tmp, "=");
	strcat(tmp, tag_value);
	if (strncmp(&measurment_uuid_buf[x + 1]," ",1) != 0)
	{
		//Comma betweeen tagsets
		strcat(tmp, ",");
	}
	strcat(tmp, measurment_uuid_buf + x);
	strcpy(measurment_uuid_buf, tmp);
};

void add_fieldset(char *field_key, void *field_value, size_t field_value_len)
{
	//Check that there is mor fileds allowed
	if (field_values_buf_cnt >= MAX_NUMBER_OF_FIELDSETS)
	{
		LOG_ERR("Unable to create new fieldset! MAX_NUMBER_OF_FIELDSETS reached");
		return;
	}
	// Check if new fieldset doesnt overfit the uuid field with strlen...

	begin = strstr(measurment_uuid_buf, " ");
	if (begin == NULL)
	{
		LOG_ERR("Unable to create new fieldset! No began measurment found");
		return;
	}
	// Insert new fieldset
	begin = begin + sizeof(" ") - 1;
	static int x;
	static char tmp[MAX_LEN_OF_MEASURMENT_UUID];
	memset(tmp, 0, sizeof(tmp));
	x = begin - measurment_uuid_buf;
	strncpy(tmp, measurment_uuid_buf, x);
	strncpy(&tmp[x],  "\0", 1);
	strcat(tmp, field_key);
	strcat(tmp, "=");
	static char num[8];
	memset(num,0,sizeof(field_values_buf_cnt)); 
	strcat(tmp, num);
	strcat(tmp, field_value);
	memcpy(field_values_buf[field_values_buf_cnt], field_value, field_value_len);
	//Comma betweeen fieldsets
	strcat(tmp, ",");
	strcat(tmp, measurment_uuid_buf + x);
	strcpy(measurment_uuid_buf, tmp);
	field_values_buf_cnt = field_values_buf_cnt + 1;
};

void end_meas(){
	//Get Metadata Position
	static int meas_ptr;
	static bool isNew;
	static int values_offset;
	isNew = false;
	for (size_t i = 0; i < MAX_LEN_OF_MEASURMENT_UUID; i++)
	{
		if (strcmp(measurment_uuids[i],measurment_uuid_buf) == 0)
		{
			meas_ptr = i;
			break;
		} else if (i == measurment_uuid_cnt)
		{
			meas_ptr = measurment_uuid_cnt;	//Next Free LOcation
			isNew = true;
			break;
		}
		//Calculate Values field offset
		values_offset = values_offset + number_of_measurment_links[i];			
	}
	//Check there is space available
	if (measurment_uuid_cnt >= MAX_LEN_OF_MEASURMENT_UUID)
	{
		LOG_ERR("Unable to append new measurment_uuid! MAX_LEN_OF_MEASURMENT_UUID reached");
		return;
	}
	if (values_offset >= NUMBER_OF_MEASURMENTS)
	{
		LOG_ERR("Unable to append new measurment_uuid! NUMBER_OF_MEASURMENTS reached");
		return;
	}
	//Request Access
	if (k_sem_take(&measurments_sem, K_MSEC(1000)) != 0)
	{
		LOG_ERR("Unable to append new measurment! Data in use.");
		return;
	}
	// Copy uuid
	if (isNew){
		strcpy(measurment_uuids[meas_ptr], measurment_uuid_buf); //Copy uuid
		measurment_uuid_cnt = measurment_uuid_cnt + 1;
	}
	//Update intervall
	if(latest_timestamps[meas_ptr] != 0){
		static uint16_t s;
		s = avg_time_intervalls[meas_ptr];
		avg_time_intervalls[meas_ptr] = s + ((timestamp_buf - latest_timestamps[meas_ptr]) - s) / (number_of_measurment_links[meas_ptr] + 1);
		// see: https://math.stackexchange.com/questions/22348/how-to-add-and-subtract-values-from-an-average
	}
	//Update number of linkes
	number_of_measurment_links[meas_ptr] = number_of_measurment_links[meas_ptr] + 1;
	//Update latest timestamp
	latest_timestamps[meas_ptr] = timestamp_buf;
	//Insert value field in array at offset position....
	// shift elements forward
	for (size_t j = 0; j < field_values_buf_cnt; j++)
	{
		for (size_t i = NUMBER_OF_MEASURMENTS-1; i > values_offset; i--)
		{
			memcpy(field_values[j][i],field_values[j][i - 1],MAX_LEN_OF_FIELD_VALUE); //SHift all to the left
		}
		memcpy(field_values[j][values_offset],field_values_buf[j],MAX_LEN_OF_FIELD_VALUE); //Copy content
	}        
	//MOve all others over and calculate new delta :)
	k_sem_give(&measurments_buffer_sem);
	k_sem_give(&measurments_sem);
};