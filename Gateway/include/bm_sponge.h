/*
This file is part of Gateway.

Gateway is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Gateway is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Gateway.  If not, see <http://www.gnu.org/licenses/>.
*/

/* AUTHOR 	 :    Raffael Anklin       */


#ifndef BM_SPONGE_H__
#define BM_SPONGE_H__



#ifdef __cplusplus
extern "C" {
#endif

#include <bm_influxdb.h>

#define PUSH_INTERVALL_SECONDS 60
#define SYNC_INTERVALL_SECONDS 600


/**
 * @brief Sponge is a transportprotocol for influxdb data. It is designed to have a small payload size with a tradeoff in a higher latency. 
 * 
 * The Spongeserver pushes the field_values on a regular timebase (push_intervall). The Spongeclient receives the field_values and combines them 
 * with the corresponding metadata, reconstructs the timestamps and is able to push the whole measurments to a infludb instance.
 * A synchronisation handshake is done on a regular timebase (sync_intervall) where the Server rerports to the client the metadata.
 *  
 * It is assumed that the measurment_uuids and time_intervalls are more or less constant (time invariant), so after a initial sync
 * only the checksum of them is compared during the sync handshake. If they mismatch they are retransmitted immediatly.
 * 
 * When a push_intervall is triggered, the server does:
 * -- Delta encode all data fields.
 * -- Encode Protobuf Message.
 * -- Send the Data to the Client.
* When a sync_intervall is triggered, the server does:
 * -- Calculate the 
 * The CLient does:
 * -- Listen for incoming push / sync messages
 * If push_message:
 * -- Decode Protobuf Message
 * -- Delta Decode all data fields
 * -- Restore Timestamps **
 * -- Publish Data to influxdb
 * 
 */


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
void add_tagset(char * tag_key, char * tag_value);
/**
 * @brief Add a field_set to a previously began measurment
 * 
 * @param field_key Name describing the field value.
 * @param field_value Field value (see: https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/#data-types-and-format).
 * 
*/
void add_fieldset(char * field_key, void * field_value);
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

#endif /* BM_SPONGE_H__ */
