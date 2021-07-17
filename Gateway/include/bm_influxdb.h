/*
This file is part of Bluetooth-Benchamrk.

Bluetooth-Benchamrk is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Bluetooth-Benchamrk is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Bluetooth-Benchamrk.  If not, see <http://www.gnu.org/licenses/>.
*/

/* AUTHOR 	 :    Raffael Anklin       */


#ifndef BM_INFLUXDB_H__
#define BM_INFLUXDB_H__



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
 * The field_values and timestamps are stored in a separate array ordered by the correspondig measurment_uuid[n]. 
 * To find the linked field_values and timestamps go over the measurment_uuid[n] and sum up the offset:
 * offset = (measurment_uuid[n]->linked_timestamps + measurment_uuid[n+1]->linked_timestamps + ...).
 *   
 * This way the data with high cardinality (time variant) gets linked to the metadata (measurment_uuids). 
 * It is assumed that there are a low number of uuids and high number of field_values and timestamps as it should be 
 * in a static enviroment of sensors.
 * 
 * 
 * Measurments are stored in a string, separeted according to InfluxDB Line Protocol. 
 *  see: https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/ 
 */
char measurment_uuids[NUMBER_OF_MEASURMENT_UUIDS][MAX_LEN_OF_MEASURMENT_UUID];
char field_values[NUMBER_OF_MEASURMENTS][MAX_NUMBER_OF_FIELDSETS][MAX_LEN_OF_FIELD_VALUE];
uint64_t timestamps[NUMBER_OF_MEASURMENTS];
/**
 * @brief Begin a measurment with required parameters
 * 
 * @param meas_name String with the name of the Measurment.
 * @param field_key Name describing the field value.
 * @param field_value Field value (see: https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/#data-types-and-format).
 * @param timestamp Timestamp in epoch time format (see: https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/#unix-timestamp).
 * 
*/
void begin_meas(char * meas_name, char * field_key, void * field_val, uint64_t * timestamp);
/**
 * @brief Add a tag_set to a previously began measurment
 * 
 * @param tag_key Name describing the tag value.
 * @param tag_value String encoded tag value.
 * 
*/
void add_tag(char * tag_key, char * tag_value);
/**
 * @brief Add a field_set to a previously began measurment
 * 
 * @param field_key Name describing the field value.
 * @param field_value Field value (see: https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/#data-types-and-format).
 * 
*/
void add_field(char * field_key, void * field_value);
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
/**
 * @brief Delta Encode Field Values and Timestamps 
 * 
 * @note To Compress the Sizes for transport is over
 * 
*/
void delta_encode_all_meas();
/**
 * @brief Delta decode Field Values and Timestamps 
 * 
 * @note To restore Field Values and Timestamps
 * 
*/
void delta_decode_all_meas();




#ifdef __cplusplus
}
#endif

#endif /* BM_INFLUXDB_H__ */
