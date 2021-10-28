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

#include <zephyr.h>
#include <stdio.h>



int dlms_push_parser_lge450_uart_init();
#ifdef __cplusplus
extern "C" void dlms_push_parser_lge450_parse(uint8_t* rx_data,unsigned long count);
#else
void dlms_push_parser_lge450_parse(uint8_t* rx_data,unsigned long count);
#endif



/**
 * @brief DLMS Push Listener LG450 does Parse Push Messeges HDLC (M-BUS) tested with a Landys+Gyr e450 Smart Meter. 
 * 
 */

