/* Copyright Prosoft-Biometrics */

#ifndef HF_PVWTC_WORKER_STUDIO_PACKETS_H_
#define HF_PVWTC_WORKER_STUDIO_PACKETS_H_

#include "studio_packets.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)
typedef struct device_settings {
    uint32_t copr_address; // 220000 - 239999, readonly
    uint32_t copr_max_user_count; // 0 - 1 000 000, readonly
    uint32_t copr_max_templ_count; // 0 - 300 000, readonly
    uint32_t db_current_user_count; // 0 - 1 000 000, readonly
    uint8_t system_templs_max_per_user; // 0 - 10
    uint8_t system_language; // 0 - русский, // 1 - english
    uint8_t system_lock_keyboard;

    uint8_t system_speaker_mode; // 0 - включен биппер,
    // 1 - отключен звук кнопок биппера,
    // 2 - полное беззвучье,
    // 3 - включен динамик,
    // 4 - отключен звук кнопок динамика

    uint8_t system_mode; // 0 - сетевой,
    // 1 - локальный,
    // 2 - серверная идентификация

    uint8_t system_volume; // 0 - 100
    uint32_t deposit_box_ip;
    uint16_t deposit_box_port;
    uint32_t deposit_box_lsb;
    uint32_t deposit_box_msb;
    uint8_t studio_encrypt;
    uint32_t studio_encrypt_code; // 1 = 10ms
    uint8_t studio_timeout;
    uint8_t work_model;
    uint8_t pvs_minimal_quality; // 0 - 100

    uint32_t pvs_math_options; // Не используется
    // See prosoft_biometrics_pvs_math_options
    // 0x00000000 - disable all
    // 0x00000001 - enable anti-fake
    // 0x00000003 - enable anti-fake +
    //              white paper
    uint32_t ident_group_code;

    uint32_t stream_server_ip; // IP-адрес службы потокового видео
    uint16_t stream_server_port; // порт службы потокового видео

    uint8_t inout_direction; // Направление прохода: 0 - не задано, 1 - вход, 2 - выход
    uint8_t pvs_enroll_antifake; // Антифейк включен (true/false)
    uint8_t pvs_matching_level; // Уровень совпадения при поиске шаблона
    uint8_t system_save_log_image; // Логирование фото сканера (true/false)
    uint8_t system_save_camera_image; // Сохранение фото с камеры (true/false)
    uint8_t system_tamper_on_start; // Предупреждение о вскрытии корпуса (true/false)
    uint8_t system_save_additional_templ; // Сохранение дополнительных шаблонов (true/false)
    int32_t system_block_timeout; // Таймаут блокировки по антифейку
    int8_t system_max_left; // Максимальное количество левых ладоней
    int8_t system_max_right; // Максимальное количество правых ладоней
    int8_t system_min_left; // Минимальное количество левых ладоней
    int8_t system_min_right; // Минимальное количество правых ладоней
    int8_t pvs_hand_kind; // true/false

    uint8_t reserved[54];
} device_settings_t;
#pragma pack(pop)

//=============================================================================
//
// CMD - 0x93
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_93 {
    studio_packet_header_t header;
    uint32_t id_employee;
    uint32_t block_size;
    uint32_t block_position;
    uint8_t block_data;
} studio_packet_in_cmd_93_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_93_t;
//=============================================================================
//
// CMD - 0xA5
typedef studio_packet_request_t studio_packet_in_cmd_a5_t;
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_a5 {
    studio_packet_header_t header;
    uint8_t result;
    uint32_t templ_size;
    uint16_t templ_quality;
    uint8_t templ_role;
    uint8_t templ_type;
} studio_packet_out_cmd_a5_t;
#pragma pack(pop)
// typedef studio_packet_result_t  studio_packet_out_cmd_a5_fail_t;
//=============================================================================
//
// CMD - 0xA6
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_a6 {
    studio_packet_header_t header;
    uint32_t id_employee;
    uint8_t templ_number;
} studio_packet_in_cmd_a6_t;
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_a6 {
    studio_packet_header_t header;
    uint8_t result;
    uint32_t image_size;
} studio_packet_out_cmd_a6_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0xD0
typedef studio_packet_request_t studio_packet_in_cmd_d0_t;
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_d0 {
    studio_packet_header_t header;
    uint8_t result;
    device_settings_t device;
} studio_packet_out_cmd_d0_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0xD1
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_d1 {
    studio_packet_header_t header;
    device_settings_t device;
} studio_packet_in_cmd_d1_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_d1_t;
//=============================================================================
//
// CMD - 0xD2
typedef studio_packet_header_t studio_packet_in_cmd_d2_t;
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_d2 {
    studio_packet_header_t header;
    uint8_t result;
    uint32_t cardId;
} studio_packet_out_cmd_d2_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0xD4
typedef studio_packet_request_t studio_packet_in_cmd_d4_t;
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_d4 {
    studio_packet_header_t header;
    uint8_t result;
    diagnostic_coproseccor_t diag_copro;
    diagnostic_pvs_t diag_pvs;
    uint8_t reserved[16];
} studio_packet_out_cmd_d4_t;
#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif // HF_PVWTC_WORKER_STUDIO_PACKETS_H_
