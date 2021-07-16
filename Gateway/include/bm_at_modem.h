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


#ifndef BM_AT_MODEM_H__
#define BM_AT_MODEM_H__



#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  Initialize AT Modem
 *
 * @note   Uses Defined UART Interface. 
 */
void bm_at_modem_init();




#ifdef __cplusplus
}
#endif

#endif /* BM_AT_MODEM_H__ */
