/* Influxdb Measurments */

#include <zephyr.h>
#include <sys/printk.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(szl_influxdb);
#include <szl_influxdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

/* ---------- Metadata ------------------- */
char measurment_uuids[NUMBER_OF_MEASURMENT_UUIDS][MAX_LEN_OF_MEASURMENT_UUID];
bool measurment_uuids_free[NUMBER_OF_MEASURMENT_UUIDS];
uint8_t number_of_measurment_links[NUMBER_OF_MEASURMENT_UUIDS];
int64_t avg_time_intervalls[NUMBER_OF_MEASURMENT_UUIDS];
int64_t latest_timestamps[NUMBER_OF_MEASURMENT_UUIDS];
/* ---------- Field Values ------------------- */
char field_values[MAX_NUMBER_OF_FIELDSETS][NUMBER_OF_MEASURMENTS][MAX_LEN_OF_FIELD_VALUE];
bool field_values_free[NUMBER_OF_MEASURMENTS];
uint16_t field_values_metalink[NUMBER_OF_MEASURMENTS]; //Dont match default value 0
bool field_values_metalink_free[NUMBER_OF_MEASURMENTS];
/* ----------- Timestamps ---------------- */
int64_t timestamps[NUMBER_OF_MEASURMENTS];

/* Helper Pointers */
int measurment_uuid_cnt; //Points to next free measurment_uuid -> Needs Reset Upon Clearing

/* Buffer to enque new measurments */
char measurment_uuid_buf[MAX_LEN_OF_MEASURMENT_UUID];
char field_values_buf[MAX_NUMBER_OF_FIELDSETS][MAX_LEN_OF_FIELD_VALUE];
int field_values_buf_cnt; // POints to next free location
int64_t timestamp_buf;
K_SEM_DEFINE(measurments_buffer_sem, 1, 1);
K_SEM_DEFINE(measurments_sem, 1, 1);
char *begin;

void init_db(){
	//Reset all FIleds
	memset(measurment_uuids_free,true,sizeof(measurment_uuids_free));
	memset(field_values_free,true,sizeof(field_values_free));
	memset(field_values_metalink,NUMBER_OF_MEASURMENT_UUIDS + 1,sizeof(field_values_metalink));
	memset(field_values_metalink_free,true,sizeof(field_values_metalink_free));
}

void set_field_val(void *field_val, field_value_types_t field_val_typ)
{
	//Set field_val according to type
	switch (field_val_typ)
	{
	case float_64:
		sprintf(field_values_buf[field_values_buf_cnt], "%lf", *(double *)field_val);
		break;
	case int_64:
		sprintf(field_values_buf[field_values_buf_cnt], "%llii", *(int64_t *)field_val);
		break;
	case uint_64:
		sprintf(field_values_buf[field_values_buf_cnt], "%lluu", *(uint64_t *)field_val);
		break;
	case string:
		strcat(field_values_buf[field_values_buf_cnt], "\"");
		strcat(field_values_buf[field_values_buf_cnt], field_val);
		strcat(field_values_buf[field_values_buf_cnt], "\"");
		break;
	case boolean:
		if (*(bool *)field_val == true)
		{
			strcat(field_values_buf[field_values_buf_cnt], "t");
		}
		else
		{
			strcat(field_values_buf[field_values_buf_cnt], "f");
		}
		break;
	default:
		break;
	}
}

void begin_meas(char *meas_name, char *field_key, void *field_val, field_value_types_t field_val_typ, int64_t *timestamp)
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
	strcat(measurment_uuid_buf, "=");
	static char num[6];
	sprintf(num, "%u", field_values_buf_cnt);
	strcat(measurment_uuid_buf, num);
	strcat(measurment_uuid_buf, " ");
	set_field_val(field_val, field_val_typ);
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
	strncpy(&tmp[x], "\0", 1);
	strcat(tmp, tag_key);
	strcat(tmp, "=");
	strcat(tmp, tag_value);
	//if (strncmp(&measurment_uuid_buf[x+1]," ",1) != 0)
	if (measurment_uuid_buf[x] != " "[0])
	{
		//Comma betweeen tagsets
		strcat(tmp, ",");
	}
	strcat(tmp, measurment_uuid_buf + x);
	strcpy(measurment_uuid_buf, tmp);
};

void add_fieldset(char *field_key, void *field_value, field_value_types_t field_val_typ)
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
	strncpy(&tmp[x], "\0", 1);
	strcat(tmp, field_key);
	strcat(tmp, "=");
	static char num[6];
	sprintf(num, "%u", field_values_buf_cnt);
	strcat(tmp, num);
	strcat(tmp, ",");
	strcat(tmp, measurment_uuid_buf + x);
	strcpy(measurment_uuid_buf, tmp);
	set_field_val(field_value, field_val_typ);
	field_values_buf_cnt = field_values_buf_cnt + 1;
};

void end_meas()
{
	//Get Metadata Position
	static int meas_ptr;
	//Get Measurment UUID Index
	for (size_t i = 0; i < NUMBER_OF_MEASURMENT_UUIDS; i++)
	{
		if ((strcmp(measurment_uuids[i], measurment_uuid_buf) == 0) || measurment_uuids_free[i] == true)
		{
			meas_ptr = i;
			break;
		}
	}
	//Check there is space available
	if (measurment_uuid_cnt >= MAX_LEN_OF_MEASURMENT_UUID)
	{
		LOG_ERR("Unable to append new measurment_uuid! MAX_LEN_OF_MEASURMENT_UUID reached");
		k_sem_give(&measurments_buffer_sem);
		return;
	}
	//Request Access
	if (k_sem_take(&measurments_sem, K_MSEC(1000)) != 0)
	{
		LOG_ERR("Unable to append new measurment! Data in use.");
		k_sem_give(&measurments_buffer_sem);
		return;
	}
	// Create UUID
	if (measurment_uuids_free[meas_ptr] == true)
	{
		strcpy(measurment_uuids[meas_ptr], measurment_uuid_buf); //Copy uuid
		measurment_uuids_free[meas_ptr] = false;
	}
	//Update intervall
	if (latest_timestamps[meas_ptr] != 0)
	{
		static uint64_t s;
		s = avg_time_intervalls[meas_ptr];
		avg_time_intervalls[meas_ptr] = s + ((timestamp_buf - latest_timestamps[meas_ptr]) - s) / (number_of_measurment_links[meas_ptr] + 1);
		// see: https://math.stackexchange.com/questions/22348/how-to-add-and-subtract-values-from-an-average
	}
	//Update number of linkes
	number_of_measurment_links[meas_ptr] = number_of_measurment_links[meas_ptr] + 1;
	//Update latest timestamp
	latest_timestamps[meas_ptr] = timestamp_buf;
	//Save value field and timestamp
	for (size_t i = 0; i < NUMBER_OF_MEASURMENTS; i++)
	{
		if ((field_values_metalink[i] == meas_ptr || field_values_metalink_free[i] == true) && field_values_free[i] == true)
		{
			for (size_t j = 0; j < field_values_buf_cnt; j++)
			{
				memcpy(field_values[j][i], field_values_buf[j], MAX_LEN_OF_FIELD_VALUE); //Copy content
			}
			timestamps[i] = timestamp_buf;
			field_values_metalink[i] = meas_ptr;
			field_values_metalink_free[i] = false;
			field_values_free[i] = false;
			break;
		}
	}
	k_sem_give(&measurments_buffer_sem);
	k_sem_give(&measurments_sem);
};

void print_all_meas()
{
	static char buf[MAX_LEN_OF_MEASURMENT_UUID + MAX_LEN_OF_FIELD_VALUE * MAX_NUMBER_OF_FIELDSETS]; // Calculate the MAximum allowed size
	static char *begin_fieldset;
	static char *begin_fieldvalue;
	static int len;
	for (size_t i = 0; i < NUMBER_OF_MEASURMENTS; i++)
	{
		//CHeck if end ist reached by getting to first free field
		if(field_values_free[i] || field_values_metalink_free[i]){
			break;
		}
		static uint32_t j;
		j = field_values_metalink[i];
		//Reset buffer
		memset(buf, 0, sizeof(buf));
		//Get Beginning of Fieldsets
		begin_fieldset = strstr(measurment_uuids[j], " ");
		if (begin_fieldset == NULL)
		{
			//LOG_ERR("Unable to find fieldset! Measurment UUID Corrupt");
			break;
		}
		begin_fieldset = begin_fieldset + sizeof(" ") - 1;
		//Append till fieldset
		len = begin_fieldset - measurment_uuids[j];
		strncat(buf, measurment_uuids[j], len);
		//Get all the fieldsets
		while (strstr(begin_fieldset, "=") != NULL)
		{
			//Get Beginning of fieldvalue
			begin_fieldvalue = strstr(begin_fieldset, "=");
			if (begin_fieldvalue == NULL)
			{
				//LOG_ERR("Unable to find filedvalue! Measurment UUID Corrupt");
				break;
			}
			begin_fieldvalue = begin_fieldvalue + sizeof("=") - 1;
			//Get the field_value index
			static int ind;
			ind = atoi(begin_fieldvalue);
			//Append field_key
			len = begin_fieldvalue - begin_fieldset;
			strncat(buf, begin_fieldset, len);
			//Add fieldvalue
			strcat(buf, field_values[ind][i]);
			//Get next fieldset
			begin_fieldset = strstr(begin_fieldvalue, ",");
			if (begin_fieldset == NULL)
			{
				break;
			}
		}
		//Whtiespace
		strcat(buf, " ");
		//Add Timestamp
		static char ts[16];
		sprintf(ts, "%lli", timestamps[i]);
		strcat(buf, ts);
		//Output Measurment
		printk("%s\n", buf);
	}
	//Free all Measurments
	memset(field_values_free, true, sizeof(field_values_free));
}