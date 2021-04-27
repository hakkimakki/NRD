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


#ifndef BM_SHT3X_H__
#define BM_SHT3X_H__


#include <drivers/sensor.h>

#ifdef __cplusplus
extern "C" {
#endif



void sht3x_init();

void sht3x_temp_hum_get(struct sensor_value *temp, struct sensor_value *hum);


#ifdef __cplusplus
}
#endif

#endif /* MODEL_HANDLER_H__ */