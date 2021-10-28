/*
 * Copyright (c) 2021 Raffael Anklin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef BM_LORA_H__
#define BM_LORA_H__



#ifdef __cplusplus
extern "C" {
#endif



void bm_lora_init();

void bm_lora_send(uint8_t *data, uint32_t data_len);

uint32_t bm_lora_recv(uint8_t *data);


#ifdef __cplusplus
}
#endif

#endif /* BM_LORA_H__ */
