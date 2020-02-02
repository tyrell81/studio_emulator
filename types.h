/* Copyright Prosoft-Biometrics */

#ifndef HF_CORE_KERNEL_TYPES_H_
#define HF_CORE_KERNEL_TYPES_H_

#include <QObject>
#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_VERSION_SIZE 29
#define LOCAL_USER_RESERVE 51

#pragma pack(push, 1)
typedef struct ip {
    union {
        uint32_t raw;
        struct {
            uint8_t p0;
            uint8_t p1;
            uint8_t p2;
            uint8_t p3;
        };
    };
} ip_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct mac {
    union {
        uint8_t raw[6];
        struct {
            uint8_t p0;
            uint8_t p1;
            uint8_t p2;
            uint8_t p3;
            uint8_t p4;
            uint8_t p5;
        };
    };
} mac_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct lan_property {
    ip_t ip;
    uint16_t studio_port;
    ip_t studio_ident_server_ip;
    uint16_t studio_ident_server_port;
    ip_t mask;
    ip_t gate;
    mac_t mac;
    uint32_t mtu; // 1 — 1500,  default 1500;
} lan_property_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct datetime {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;
} datetime_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct studio_log {
    uint32_t id;
    uint32_t device_serial;
    uint32_t employee_id;
    uint16_t event;
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t mday;
    uint8_t mon;
    uint16_t year;
    uint8_t image_cnt;
} studio_log_t;
#pragma pack(pop)

#define PB_DIAG_STATE_RUN 0
#define PB_DIAG_STATE_BOOT 1
#define PB_DIAG_STATE_ERROR 2

#define PB_DIAG_STATUS_OK 0
#define PB_DIAG_STATUS_NOT_CONNECTED 1
#define PB_DIAG_STATUS_ERROR 2

#pragma pack(push, 1)
typedef struct pb_diag_version {
    uint8_t state; // 0 — software,
    // 1 — boot,
    // 2 — ошибка чтения версии
    uint8_t major;
    uint8_t minor;
} pb_diag_version_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct diagnostic_coproseccor {
    pb_diag_version_t version;
    uint8_t status; // 0 — исправен,
    // 1 — не подключен,
    // 2 — ошибка
    uint8_t reserved[4];
} diagnostic_coproseccor_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct diagnostic_pvs {
    uint8_t type; // 0 — Fujitsu, 1 — Biometrics
    pb_diag_version_t version;
    uint8_t status; // 0 — исправен,
    // 1 — не подключен,
    // 2 — ошибка
    uint8_t reserved[3];
} diagnostic_pvs_t;
#pragma pack(pop)

#ifdef __cplusplus
}
#else

Q_DECLARE_METATYPE(pb_diag_version_t);

#endif

#endif // HF_CORE_KERNEL_TYPES_H_
