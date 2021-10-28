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
#define MAX_PUSH_MESSAGE_SIZE_BYTES 190 //theretical 195...





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
 * @brief Delta Encode Field Values
 * 
 * @note To Compress the Sizes for transport is over
 * 
*/
void delta_encode_all_meas();
/**
 * @brief Delta decode Field Values 
 * 
 * @note To restore Field Values
 * 
*/
void delta_decode_all_meas();


#ifdef __cplusplus
}
#endif

#endif /* BM_SPONGE_H__ */
