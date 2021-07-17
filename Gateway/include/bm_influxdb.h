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


typedef struct field_sets {
   char fieldkey[20];
   char fieldvalue[20];
} field_set;

typedef struct tag_sets {
   char tagkey[20];
   char tagvalue[20];
} tag_set;

typedef struct measurments {
   char measurment_name[20];
   tag_set tag_set[1];
   field_set field_set[1];
   uint64_t timestamp;
} measurment;

#define MEAS_MAX_LEN 255
#define NUMBER_OF_MEASURMENTS 255

/* Measurments are stored in a string, separeted according to InfluxDB Line Protocol. see: https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/ */
char measurments[NUMBER_OF_MEASURMENTS][MEAS_MAX_LEN];
/**
 * @brief Begin a measurment with required parameters
 * 
 * @param meas_name String with the name of the Measurment.
 * @param field_key Name describing the field value.
 * @param field_value String encoded field value.
 * @param timestamp String encoded Timestamp.* 
 * 
*/
void begin_meas(char * meas_name, char * field_key, char * field_val, char * timestamp);
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
 * @param field_key Name describing the tag value.
 * @param field_value String encoded tag value.
 * 
*/
void add_field(char * field_key, char * field_value);
/**
 * @brief End a previously began measurment
 * 
*/
void end_meas();


#ifdef __cplusplus
}
#endif

#endif /* BM_INFLUXDB_H__ */
