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

#define NUMBER_OF_MEASURMENTS 255

measurment measurments[NUMBER_OF_MEASURMENTS];



#ifdef __cplusplus
}
#endif

#endif /* BM_INFLUXDB_H__ */
