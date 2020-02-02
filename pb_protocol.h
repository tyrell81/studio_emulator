/* Copyright Prosoft-Biometrics */


#ifndef PB_PROTOCOL_H_
#define PB_PROTOCOL_H_


#include <stdint.h>
#include <stddef.h>


#include "pb_sharedlib.h"



#ifdef __cplusplus
extern "C" {
#endif


// START    | 1b
// DATA00   | 1b
// CRC16    | 2b
// END      | 1b
// -------------
// MINIMAL  | 5b

// START    | 1b
// DATA00   | 1b + 1b(BYTE_STAFF) = 2b
// CRC16    | 2b + 2b(BYTE_STAFF) = 4b
// END      | 1b
// -------------
// MINIMAL  | 8b


#define PB_PROTOCOL_START_BYTE      0X81
#define PB_PROTOCOL_END_BYTE        0X82
#define PB_PROTOCOL_ESC_BYTE        0X83

#define PB_PROTOCOL_MIN_DATA_SIZE        1
#define PB_PROTOCOL_MIN_DATA_BYTE_STAFF  1
#define PB_PROTOCOL_OVERHEAD             4
#define PB_PROTOCOL_OVERHEAD_BYTE_STAFF  2

#define PB_PROTOCOL_MIN_IN_SIZE          \
  (PB_PROTOCOL_MIN_DATA_SIZE + PB_PROTOCOL_OVERHEAD)
#define PB_PROTOCOL_OUT_SIZE(data_size)  \
  (data_size * 2 + PB_PROTOCOL_OVERHEAD + PB_PROTOCOL_OVERHEAD_BYTE_STAFF)


#define PB_PROTOCOL_CRC16_START 0xFFFF


enum pb_protocol_errors {
  PB_PROTOCOL_SUCCESS = 0,
  PB_PROTOCOL_ERROR_BYTE_STAF = -1,
  PB_PROTOCOL_ERROR_CRC = -2,
  PB_PROTOCOL_ERROR_PACK_SIZE = -3,
};

PB_PROTOCOL_EXPORT
uint16_t pb_protocol_crc16_append(
    const uint16_t start_crc, const void *const buf, const size_t buf_size);

PB_PROTOCOL_EXPORT
uint16_t pb_protocol_crc16(const void *const buf, const size_t buf_size);

PB_PROTOCOL_EXPORT
const char *pb_protocol_strerror(const int code);


/**
 * Check data for BiosmartM protocol
 *
 * @param   buf - data
 * @param   count - bytes from the buffer pointed buf
 * @param   min_size - minimal buf accepted size
 * @return	enum WdsdProtocolCodes
 */
PB_PROTOCOL_EXPORT
int pb_protocol_check_packet(const void *const buf, const size_t count);


/**
 * Removed START/STOP/ESC/CRC16 from buf
 *
 * @param   buf - data
 * @param   count - bytes from the buffer pointed buf
 * @return	size or enum pb_protocol_errors
 */
PB_PROTOCOL_EXPORT
int pb_protocol_unpack(void *const buf, const size_t buf_size);


/**
 * Added START/STOP/ESC/CRC16 to buf
 *
 * @param   buf - data
 * @param   count - bytes from the buffer pointed buf
 * @return	size or enum pb_protocol_errors
 */
PB_PROTOCOL_EXPORT
int pb_protocol_pack(void *const out_buf,
                     const size_t out_size,
                     const void *const data,
                     const size_t data_size);

#ifdef __cplusplus
}
#endif


#endif  // PB_PROTOCOL_H_
