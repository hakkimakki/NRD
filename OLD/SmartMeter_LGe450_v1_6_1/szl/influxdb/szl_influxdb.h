/*
 * Copyright (c) 2021 Raffael Anklin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SZL_INFLUXDB_H__
#define SZL_INFLUXDB_H__



#ifdef __cplusplus
extern "C" {
#endif


#define MAX_LEN_OF_MEASURMENT_UUID 255
#define NUMBER_OF_MEASURMENT_UUIDS 255
#define NUMBER_OF_MEASURMENTS 255
#define MAX_NUMBER_OF_FIELDSETS 2
#define MAX_LEN_OF_FIELD_VALUE 16

/**
 * @brief A Measurment UUID consists of all the metadata fields which have a low cardinality (time invariant).
 * This results in a unique identifier made up by the measurment_name + tags + field_keys. 
 * The field_values are stored in a separate array ordered by the correspondig measurment_uuid[n]. 
 * To find the linked field_values go over the measurment_uuid[n] and sum up the offset:
 * offset = (measurment_uuid[n]->number_of_measurment_links + measurment_uuid[n+1]->number_of_measurment_links + ...).
 *   
 * This way the data with high cardinality (time variant) gets linked to the metadata (measurment_uuids). 
 * It is assumed that there are a low number of uuids and high number of field_values as it should be 
 * in a static enviroment of sensors.
 * 
 * It is assumed that the measurments arrive at a periodic timeline. So when a new measurment arrives the new value gets calculated:
 * avg_time_intervalls[n]_new = avg_time_intervalls[n]_old + ((timestamp - latest_timestamps[n]) - avg_time_intervalls[n]_old) / (number_of_measurment_links[n] + 1)
 * (see: https://math.stackexchange.com/questions/22348/how-to-add-and-subtract-values-from-an-average)
 * 
 * 
 * Measurments are stored in a string, separeted according to InfluxDB Line Protocol. 
 *  see: https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/ 
 */
/* ---------- Metadata ------------------- */
extern char measurment_uuids[NUMBER_OF_MEASURMENT_UUIDS][MAX_LEN_OF_MEASURMENT_UUID];
extern uint8_t number_of_measurment_links[NUMBER_OF_MEASURMENT_UUIDS];
extern int64_t avg_time_intervalls[NUMBER_OF_MEASURMENT_UUIDS];
extern int64_t latest_timestamps[NUMBER_OF_MEASURMENT_UUIDS];
/* ---------- Field Values ------------------- */
extern char field_values[MAX_NUMBER_OF_FIELDSETS][NUMBER_OF_MEASURMENTS][MAX_LEN_OF_FIELD_VALUE];
const typedef enum { float_64, int_64, uint_64, string, boolean } field_value_types_t;

void init_db();
/**
 * @brief Begin a measurment with required parameters
 * 
 * @param meas_name String with the name of the Measurment.
 * @param field_key Name describing the field value.
 * @param field_value Field value (see: https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/#data-types-and-format).
 * @param field_val_typ Type (see: https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/#data-types-and-format).
 * @param timestamp Timestamp in epoch time format (see: https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/#unix-timestamp).
 * 
*/
void begin_meas(char *meas_name, char *field_key, void *field_val, field_value_types_t field_val_typ, int64_t *timestamp);
/**
 * @brief Add a tag_set to a previously began measurment
 * 
 * @param tag_key Name describing the tag value.
 * @param tag_value String encoded tag value.
 * 
*/
void add_tagset(char * tag_key, char * tag_value);
/**
 * @brief Add a field_set to a previously began measurment
 * 
 * @param field_key Name describing the field value.
 * @param field_value Field value (see: https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/#data-types-and-format).
 * @param field_val_typ Type (see: https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/#data-types-and-format).
 * 
*/
void add_fieldset(char *field_key, void *field_value, field_value_types_t field_val_typ);
/**
 * @brief End and store a previously began measurment
 * 
 * @note Save the uuid if not already existent. Update the number of linked measurments. 
 * 
*/
void end_meas();
/**
 * @brief Get all stored measurments to the output stdout. 
 * 
 * @note Could be used to transfer the data.
 * 
*/
void print_all_meas();





#ifdef __cplusplus
}
#endif

#endif /* SZL_INFLUXDB_H__ */
