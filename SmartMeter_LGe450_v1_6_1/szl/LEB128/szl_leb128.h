/*
 * Copyright (c) 2021 Raffael Anklin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SZL_LEB128_H__
#define SZL_LEB128_H__



#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr.h>

/**
 * Write unsigned LEB128 data
 * @dst: the address where the ULEB128 data is to be stored
 * @val: value to be stored
 *
 * Encode an unsigned LEB128 encoded datum. The algorithm is taken
 * from Appendix C of the DWARF 3 spec. For information on the
 * encodings refer to section "7.6 - Variable Length Data". Return
 * the number of bytes written.
 */
size_t szl_encode_uleb128(uint64_t val, uint8_t * dst);

/**
 * Read unsigned LEB128 data
 * @addr: the address where the ULEB128 data is stored
 * @ret: address to store the result
 *
 * Decode an unsigned LEB128 encoded datum. The algorithm is taken
 * from Appendix C of the DWARF 3 spec. For information on the
 * encodings refer to section "7.6 - Variable Length Data". Return
 * the number of bytes read.
 */
size_t szl_decode_uleb128(uint8_t* addr, uint64_t* ret);

#ifdef __cplusplus
}
#endif

#endif /* SZL_LEB128_H__ */
