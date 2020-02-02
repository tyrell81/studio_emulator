/* Copyright Prosoft-Biometrics */

#include "pb_protocol.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint16_t pb_protocol_crc16_append(
    const uint16_t start_crc, const void* const buf, const size_t buf_size)
{
    size_t i;
    int j;
    uint16_t crc = start_crc;

    for (i = 0; i < buf_size; i++) {
        crc ^= ((uint8_t*)buf)[i];

        for (j = 0; j < 8; j++)
            crc = (crc & 0x0001) ? (crc >> 1) ^ 0xA001 : (crc >> 1);
    }

    return crc;
}

uint16_t pb_protocol_crc16(const void* const buf, const size_t buf_size)
{
    return pb_protocol_crc16_append(PB_PROTOCOL_CRC16_START, buf, buf_size);
}

const char* pb_protocol_strerror(const int code)
{
    switch (code) {
    case PB_PROTOCOL_SUCCESS:
        return "PB_PROTOCOL_OK";

    case PB_PROTOCOL_ERROR_BYTE_STAF:
        return "PB_PROTOCOL_BYTE_STAFF_ERROR";

    case PB_PROTOCOL_ERROR_CRC:
        return "PB_PROTOCOL_CRC_ERROR";

    case PB_PROTOCOL_ERROR_PACK_SIZE:
        return "PB_PROTOCOL_ERROR_PACK_SIZE";

    default:
        return "PB_PROTOCOL_UNDEFINED";
    }
}

int pb_protocol_unpack(void* const buf, const size_t buf_size)
{
    if (buf_size < PB_PROTOCOL_MIN_DATA_SIZE)
        return PB_PROTOCOL_ERROR_PACK_SIZE;

    size_t i;
    uint8_t* const data = (uint8_t*)buf;

    int idata = 0;

    for (i = 1; i < buf_size - 1; i++) {
        if (data[i] != PB_PROTOCOL_ESC_BYTE) {
            data[idata++] = data[i];
            continue;
        }

        i++;

        if (i >= buf_size - 1)
            return PB_PROTOCOL_ERROR_BYTE_STAF;

        if (data[i] != PB_PROTOCOL_START_BYTE && data[i] != PB_PROTOCOL_END_BYTE && data[i] != PB_PROTOCOL_ESC_BYTE)
            return PB_PROTOCOL_ERROR_BYTE_STAF;

        data[idata++] = data[i];
    }

    /*memset(data + idata, 0, buf_size - idata);*/
    const uint16_t* crc16 = (uint16_t*)(data + idata - 2);
    const uint16_t _crc = pb_protocol_crc16(buf, idata - 2);

    if (_crc != *crc16)
        return PB_PROTOCOL_ERROR_CRC;

    return idata - 2;
}

int pb_protocol_check_packet(const void* const buf, const size_t buf_size)
{
    const uint8_t* const data = (const uint8_t* const)buf;

    if (data[0] != PB_PROTOCOL_START_BYTE)
        return PB_PROTOCOL_ERROR_BYTE_STAF;

    if (data[buf_size - 1] != PB_PROTOCOL_END_BYTE)
        return PB_PROTOCOL_ERROR_BYTE_STAF;

    size_t i;

    for (i = 2; i < buf_size; i++) {
        if (data[buf_size - i] != PB_PROTOCOL_START_BYTE && data[buf_size - i] != PB_PROTOCOL_END_BYTE && data[buf_size - i] != PB_PROTOCOL_ESC_BYTE)
            continue;

        i++;

        if (data[buf_size - i] != PB_PROTOCOL_ESC_BYTE)
            return PB_PROTOCOL_ERROR_BYTE_STAF;
    }

    return PB_PROTOCOL_SUCCESS;
}

int pb_protocol_pack(void* const out_buf,
    const size_t out_size,
    const void* const data,
    const size_t data_size)
{
    if (out_size < PB_PROTOCOL_OUT_SIZE(data_size))
        return PB_PROTOCOL_ERROR_PACK_SIZE;

    const uint16_t crc16 = pb_protocol_crc16(data, data_size);
    uint8_t* const out_data = (uint8_t * const)out_buf;
    const uint8_t* in_data = (const uint8_t*)data;

    size_t i_max = data_size + sizeof(crc16);
    size_t idata = 0;

    out_data[idata++] = PB_PROTOCOL_START_BYTE;
    size_t i;
    // TODO refactoring
    bool crc = false;

    for (i = 0; i < i_max; i++, idata++) {
        if (i == data_size && !crc) {
            i_max = sizeof(crc16);
            i = 0;
            in_data = (const uint8_t*)&crc16;
            crc = true;
        }

        if (in_data[i] != PB_PROTOCOL_START_BYTE && in_data[i] != PB_PROTOCOL_END_BYTE && in_data[i] != PB_PROTOCOL_ESC_BYTE) {
            out_data[idata] = in_data[i];
            continue;
        }

        out_data[idata++] = PB_PROTOCOL_ESC_BYTE;
        out_data[idata] = in_data[i];
    }

    out_data[idata++] = PB_PROTOCOL_END_BYTE;

    return idata;
}
