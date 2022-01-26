/*
 * Copyright (c) 2021 Raffael Anklin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SZL_LORA_H__
#define SZL_LORA_H__



#ifdef __cplusplus
extern "C" {
#endif



void szl_lora_init();

void szl_lora_send(uint8_t *data, uint32_t data_len);

uint32_t szl_lora_recv(uint8_t *data);


#ifdef __cplusplus
}
#endif

#endif /* SZL_LORA_H__ */
