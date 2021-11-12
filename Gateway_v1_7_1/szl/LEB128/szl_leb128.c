/* Influxdb Measurments */

#include <zephyr.h>
#include <sys/printk.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(szl_leb128);
#include <stdio.h>
#include <string.h>

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
size_t szl_encode_uleb128(uint64_t val, uint8_t * dst){
	static uint8_t count;
	static uint8_t byte;
  count = 0;
	do {
		byte = val & 0x7f;
		val >>= 7;

		if (val != 0)
		byte |= 0x80;  // mark this byte to show that more bytes will follow

		memcpy(dst+count,&byte,1);

		//dest.push_back(byte);
		count++;
  	} while (val != 0);
	return count;
}

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
size_t szl_decode_uleb128(uint8_t* addr, uint64_t* ret) {
  static uint8_t byte;
  static uint64_t result;
  static int shift;
  static size_t count;

  shift = 0;
  count = 0;
  result = 0;

  while (1) {
    byte = addr[count];
    //addr++;
    count++;

    result |= (byte & 0x7f) << shift;
    shift += 7;

    if (!(byte & 0x80)) break;
  }

  memcpy(ret,&result,count);

  return count;
}