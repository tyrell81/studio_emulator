/* Copyright Prosoft-Biometrics */

#ifndef HF_CORE_STUDIO_STUDIO_PACKETS_H_
#define HF_CORE_STUDIO_STUDIO_PACKETS_H_

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HF_STUDIO_CMD_MAX_READ_LOG 100
#define HF_STUDIO_FIRMWARE_PAGE_SIZE 1024u
#define HF_STUDIO_USERNAME_MAX_LEN 108
#define HF_STUDIO_HOLIDAY_LIST_DAYS_MAX 32

#pragma pack(push, 1)
typedef struct studio_packet_header {
    uint32_t addr;
    uint8_t cmd;
} studio_packet_header_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct studio_packet_request {
    studio_packet_header_t header;
} studio_packet_request_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct studio_packet_result {
    studio_packet_header_t header;
    uint8_t result;
} studio_packet_result_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct studio_firmware_page {
    uint32_t num;
    union {
        uint8_t data[HF_STUDIO_FIRMWARE_PAGE_SIZE];
        uint16_t crc16;
    };
} studio_firmware_page_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct studio_employee {
    uint32_t id;
    uint32_t id_schedule;
    uint32_t card;
    uint32_t pin;
    uint8_t type;
    uint8_t block;
    char last_name[HF_STUDIO_USERNAME_MAX_LEN];
    char first_name[HF_STUDIO_USERNAME_MAX_LEN];
    char middle_name[HF_STUDIO_USERNAME_MAX_LEN];
    uint32_t id_role;
    uint8_t reserv[166];
} studio_employee_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct studio_schedule_interval {
    time_t start;
    time_t stop;
} studio_schedule_interval_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct studio_schedule_day {
    uint32_t id_schedule;
    uint16_t day_number;
    uint16_t interval_count;
    studio_schedule_interval_t interval_array_data[1];
} studio_schedule_day_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct schedule {
    uint32_t id;
    uint8_t id_holiday_list;
    time_t start;
    time_t stop;
    uint32_t days_count;
} studio_schedule_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct studio_holiday {
    uint8_t day;
    uint8_t month;
} studio_holiday_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct studio_holiday_list {
    uint8_t id;
    uint8_t num;
    studio_holiday_t holidays[HF_STUDIO_HOLIDAY_LIST_DAYS_MAX];
} studio_holiday_list_t;
#pragma pack(pop)

// Abstract Commands
//=============================================================================
// CMD - 0x00
//
typedef studio_packet_request_t studio_packet_in_cmd_00_t;
typedef studio_packet_result_t studio_packet_out_cmd_00_t;
//=============================================================================
// CMD - 0x01
//
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_01 {
    studio_packet_header_t header;
    uint32_t page_cnt;
} studio_packet_in_cmd_01_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_01_t;
//=============================================================================
//
// CMD - 0x02 - fix documentation pvwtc
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_02 {
    studio_packet_header_t header;
    studio_firmware_page_t page;
} studio_packet_in_cmd_02_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_02_t;
//=============================================================================
// CMD - 0x06
//
typedef studio_packet_request_t studio_packet_in_cmd_06_t;
typedef studio_packet_result_t studio_packet_out_cmd_06_t;
//=============================================================================
// CMD - 0x08
//
typedef studio_packet_request_t studio_packet_in_cmd_08_t;
typedef studio_packet_result_t studio_packet_out_cmd_08_t;
//=============================================================================
//
// CMD - 0x17
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_17 {
    studio_packet_header_t header;
    datetime_t datetime;
} studio_packet_in_cmd_17_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_17_t;
//=============================================================================
//
// CMD - 0x20
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_20 {
    studio_packet_header_t header;
    studio_employee_t employee;
} studio_packet_in_cmd_20_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_20_t;
//=============================================================================
//
// CMD - 0x21
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_21 {
    studio_packet_header_t header;
    uint32_t id_employee;
} studio_packet_in_cmd_21_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_21_t;
//=============================================================================
//
// CMD - 0x23
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_23 {
    studio_packet_header_t header;
    uint32_t id_employee;
} studio_packet_in_cmd_23_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_23_t;
//=============================================================================
//
// CMD - 0x24
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_24 {
    studio_packet_header_t header;
    uint32_t id_employee;
} studio_packet_in_cmd_24_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_24_t;
//=============================================================================
//
// CMD - 0x25
typedef studio_packet_request_t studio_packet_in_cmd_25;
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_25 {
    studio_packet_header_t header;
    uint8_t result;
    uint32_t count_employees;
    uint32_t count_templs;
} studio_packet_out_cmd_25_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0x30
typedef studio_packet_request_t studio_packet_in_cmd_30_t;
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_30 {
    studio_packet_header_t header;
    uint8_t result;
    uint32_t logs_count;
} studio_packet_out_cmd_30_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0x31
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_31 {
    studio_packet_header_t header;
    uint32_t logs_count;
} studio_packet_in_cmd_31_t;
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_31 {
    studio_packet_header_t header;
    uint8_t result;
    // uint8_t[]           extra;  // extra do not delete this comment
} studio_packet_out_cmd_31_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0x32
#pragma pack(push, 1)
typedef struct studio_log_image {
    uint8_t type;
    uint32_t size;
} studio_log_image_t;
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_32 {
    studio_packet_header_t header;
    uint32_t id_log;
} studio_packet_in_cmd_32_t;
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_32 {
    studio_packet_header_t header;
    uint8_t result;
    uint32_t id_log;
    // studio_log_image_t     images[];  // extra
} studio_packet_out_cmd_32_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0x33
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_33 {
    studio_packet_header_t header;
    uint32_t logs_count;
} studio_packet_in_cmd_33_t;
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_33 {
    studio_packet_header_t header;
    uint8_t result;
    uint32_t logs_count;
} studio_packet_out_cmd_33_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0x34
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_34 {
    studio_packet_header_t header;
} studio_packet_in_cmd_34_t;
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_34 {
    studio_packet_header_t header;
    uint8_t result;
    uint8_t out_state;
    uint8_t reserved[15];
    // uint8_t              extra[]
} studio_packet_out_cmd_34_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0x70
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_70 {
    studio_packet_header_t header;
    studio_schedule_t schedule;
} studio_packet_in_cmd_70_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_70_t;
//=============================================================================
//
// CMD - 0x71
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_71 {
    studio_packet_header_t header;
    uint32_t id_schedule;
} studio_packet_in_cmd_71_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_71_t;
//=============================================================================
//
// CMD - 0x72
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_72 {
    studio_packet_header_t header;
    studio_schedule_day_t schedule_day;
} studio_packet_in_cmd_72_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_72_t;
//=============================================================================
//
// CMD - 0x80
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_80 {
    studio_packet_header_t header;
    studio_holiday_list_t list;
} studio_packet_in_cmd_80_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_80_t;
//=============================================================================
//
// CMD - 0x81
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_81 {
    studio_packet_header_t header;
    uint8_t holiday_list_id;
} studio_packet_in_cmd_81_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_81_t;
//=============================================================================
//
// CMD - 0x98
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_98 {
    studio_packet_header_t header;
    uint32_t roleId;
    uint32_t rolePass; //unused
    uint8_t menu;
    uint8_t info;
    uint8_t errors;
    uint8_t reserve[5];
    uint8_t mSettings;
    uint8_t settSystem;
    uint8_t settNet;
    uint8_t settDisplay;
    uint8_t settDatetime;
    uint8_t settIntegration;
    uint8_t settReserve[10];
    uint8_t mUsers;
    uint8_t userChange;
    uint8_t userAdd;
    uint8_t userdel;
    uint8_t userChangePalm;
    uint8_t userChangeCode;
    uint8_t userChangeCard;
    uint8_t userChangeName;
    uint8_t userReserve[8];
    uint8_t reserv[16];
} studio_packet_in_cmd_98_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_98_t;
//=============================================================================
//
// CMD - 0x99
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_99 {
    studio_packet_header_t header;
    uint32_t roleId;
} studio_packet_in_cmd_99_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_99_t;
//=============================================================================
//
// CMD - 0x9A
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_9a {
    studio_packet_header_t header;
    uint32_t adminId;
    uint32_t adminPass;
    uint32_t roleId;
    uint8_t identType; // 0 - pin only, 1 - pin + palm
} studio_packet_in_cmd_9a_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_9a_t;
//=============================================================================
//
// CMD - 0x9B
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_9b {
    studio_packet_header_t header;
    uint32_t adminId;
} studio_packet_in_cmd_9b_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_9b_t;
//=============================================================================
//
// CMD - 0xA0
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_a0 {
    studio_packet_header_t header;
    uint32_t id_employee;
    uint8_t templ_type; // 0 - Fujitsu, 1 - Biometrics Palm
    uint8_t templ_role; // 1 bit - Alarm,
    uint32_t templ_size;
    uint8_t templ_quality; // 0 - 100
    uint8_t templ_hand_kind; // 1 bit - Left, 2 bit - Right
    uint8_t reserv[4];
    // uint8_t             templ_data[templ_size];  // extra
} studio_packet_in_cmd_a0_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_a0_t;

enum STUDIO_PACKET_TEMPL_ROLE {
    STUDIO_PACKET_TEMPL_ROLE_LEFT = 0x2,
    STUDIO_PACKET_TEMPL_ROLE_RIGHT = 0x4,
    STUDIO_PACKET_TEMPL_ROLE_LIMIT
};
//=============================================================================
//
// CMD - 0xA3
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_a3 {
    studio_packet_header_t header;
    uint32_t id_employee;
} studio_packet_in_cmd_a3_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct templ_info {
    uint8_t count;
    uint8_t count_alarm;
} templ_info_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct pvs_templ_info {
    uint8_t type;
    templ_info_t templ_info;
} pvs_templ_info_t;
#pragma pack(pop)

// TODO(Svetkin M.A) переделать названия полей структуры
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_a3 {
    studio_packet_header_t header;
    uint8_t result;
    templ_info_t templ_info_all;
    pvs_templ_info fujitsu;
    pvs_templ_info prosoft_biometrics;
} studio_packet_out_cmd_a3_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0xA4
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_a4 {
    studio_packet_header_t header;
    uint32_t id_employee;
    uint8_t templ_num;
} studio_packet_in_cmd_a4_t;
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_a4 {
    studio_packet_header_t header;
    uint8_t result;
    uint32_t templ_size;
    uint16_t templ_quality;
    uint8_t templ_role; // 1 bit - Alarm, 2 bit - Left, 3 bit - Right
    uint8_t templ_type;
} studio_packet_out_cmd_a4_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0xC0
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_c0 {
    studio_packet_header_t header;
    lan_property_t lan_property;
} studio_packet_in_cmd_c0_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_c0_t;
//=============================================================================
//
// CMD - 0xC1
typedef studio_packet_request_t studio_packet_in_cmd_c1_t;
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_c1 {
    studio_packet_header_t header;
    uint8_t result;
    lan_property_t lan_property;
} studio_packet_out_cmd_c1_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0xC3
typedef studio_packet_request_t studio_packet_in_cmd_c3_t;
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_c3 {
    studio_packet_header_t header;
    char version[MAX_VERSION_SIZE];
} studio_packet_out_cmd_c3_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0xD3
typedef studio_packet_request_t studio_packet_in_cmd_d3_t;
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_d3 {
    studio_packet_header_t header;
    uint8_t result;
    uint8_t employee_templ_count;
    studio_employee_t employee;
} studio_packet_out_cmd_d3_t;
#pragma pack(pop)
//=============================================================================
//
// CMD - 0xD5
#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_d5 {
    studio_packet_header_t header;
    uint32_t id_employee;
} studio_packet_in_cmd_d5_t;
#pragma pack(pop)
typedef studio_packet_result_t studio_packet_out_cmd_d5_t;

//=============================================================================
//
// CMD - 0xCE - server ident
#pragma pack(push, 1)
typedef struct studio_packet_out_cmd_ce {
    studio_packet_header_t header;
    uint32_t card;
    uint32_t pin;
    uint8_t reserved[7];
    uint8_t templ_quality;
    uint32_t templ_format;
    uint32_t templ_size;
    /*uint8_t              templ_extra[]*/
} studio_packet_out_cmd_ce_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct studio_packet_in_cmd_ce {
    studio_packet_header_t header;
    uint8_t status;
    uint32_t id;
    uint32_t card;
    uint32_t code;
    uint8_t access_mode;
    uint8_t reserved[50];
    uint16_t name_size;
    /*uint8_t              name_extra*/
} studio_packet_in_cmd_ce_t;
#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif // HF_CORE_STUDIO_STUDIO_PACKETS_H_
