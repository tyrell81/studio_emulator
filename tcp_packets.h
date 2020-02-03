/* Copyright Prosoft-Biometrics */

#ifndef HF_PVWTC_WORKER_TCP_PACKETS_H_
#define HF_PVWTC_WORKER_TCP_PACKETS_H_

#include "studio_packets.h"

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
//
// CMD - 0x0a
//typedef studio_packet_request_t tcp_packet_in_cmd_0a_t;
//#pragma pack(push, 1)
//typedef struct tcp_packet_out_cmd_0a {
//    studio_packet_header_t header;
//    uint8_t result;
//    device_info_t master;
//    device_info_t rfid;
//    device_info_t pvs;
//} tcp_packet_out_cmd_0a_t;
//#pragma pack(pop)
//=============================================================================
//
// CMD - 0x0b
#pragma pack(push, 1)
typedef struct tcp_packet_in_cmd_0b {
    studio_packet_header_t header;
    uint8_t cmd;
} tcp_packet_in_cmd_0b_t;
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct tcp_packet_out_cmd_0b {
    studio_packet_header_t header;
    uint8_t result;
} tcp_packet_out_cmd_0b_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0x0c
#pragma pack(push, 1)
typedef struct tcp_packet_in_cmd_0c_gpio_cmd {
    studio_packet_header_t header;
    uint8_t num;
    uint8_t level;
    uint16_t period_ms;
    uint16_t repeat_cnt;
} tcp_packet_in_cmd_0c_t;
#pragma pack(pop)
typedef studio_packet_result_t tcp_packet_out_cmd_0c_t;
//=============================================================================
//
// CMD - 0x0d
#pragma pack(push, 1)
typedef struct tcp_packet_in_cmd_0d_work_model_state {
    studio_packet_header_t header;
} tcp_packet_in_cmd_0d_t;
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct tcp_packet_out_cmd_0d_work_model_state {
    studio_packet_header_t header;
    uint8_t state;
    uint32_t card_id;
} tcp_packet_out_cmd_0d_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0xC0
#pragma pack(push, 1)
typedef struct tcp_packet_in_cmd_c0_set_network {
    studio_packet_header_t header;
    ip_t ip;
    uint16_t port;
    ip_t mask;
    ip_t gateway;
} tcp_packet_in_cmd_c0_t;
#pragma pack(pop)
typedef studio_packet_result_t tcp_packet_out_cmd_c0_t;
//=============================================================================
//
// CMD - 0xC1
typedef studio_packet_request_t tcp_packet_in_cmd_c1_t;
#pragma pack(push, 1)
typedef struct tcp_packet_out_cmd_c1_network {
    studio_packet_header_t header;
    uint8_t result;
    ip_t ip;
    uint16_t port;
    ip_t mask;
    ip_t gateway;
    mac_t mac;
} tcp_packet_out_cmd_c1_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0xd8
//typedef studio_packet_request_t tcp_packet_in_cmd_d8_t;
//#pragma pack(push, 1)
//typedef struct tcp_packet_out_cmd_d8 {
//    studio_packet_header_t header;
//    uint8_t result;
//    settings_t settings;
//} tcp_packet_out_cmd_d8_t;
//#pragma pack(pop)
//=============================================================================
//
// CMD - 0xd1
//#pragma pack(push, 1)
//typedef struct tcp_packet_in_cmd_d1 {
//    studio_packet_header_t header;
//    settings_t settings;
//} tcp_packet_in_cmd_d1_t;
//#pragma pack(pop)
//#pragma pack(push, 1)
//typedef struct tcp_packet_out_cmd_d1 {
//    studio_packet_header_t header;
//    uint8_t result;
//} tcp_packet_out_cmd_d1_t;
//#pragma pack(pop)

//=============================================================================
//
// CMD - 0xd9
//#pragma pack(push, 1)
//typedef struct tcp_packet_in_cmd_d9 {
//    studio_packet_header_t header;
//    settings_t settings;
//} tcp_packet_in_cmd_d9_t;
//#pragma pack(pop)
//#pragma pack(push, 1)
//typedef struct tcp_packet_out_cmd_d9 {
//    studio_packet_header_t header;
//    uint8_t result;
//} tcp_packet_out_cmd_d9_t;
//#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif // HF_PVWTC_WORKER_TCP_PACKETS_H_
