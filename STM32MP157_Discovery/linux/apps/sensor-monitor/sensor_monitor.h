#ifndef SENSOR_MONITOR_H
#define SENSOR_MONITOR_H

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    float temperature_c;
    float pressure_kpa;
    float vibration_g_rms;

    uint64_t timestamp_ms;

    bool temperature_valid;
    bool pressure_valid;
    bool vibration_valid;

    bool rpmsg_connected;
} monitor_data_t;

typedef struct
{
    float temperature_high;
    float pressure_high;
    float vibration_high;
} monitor_thresholds_t;

typedef enum
{
    MONITOR_STATUS_NORMAL = 0,
    MONITOR_STATUS_WARNING,
    MONITOR_STATUS_ERROR
} monitor_status_t;

int sensor_monitor_init(void);

int sensor_monitor_update(const monitor_data_t *data);

int sensor_monitor_check_thresholds(
    const monitor_data_t *data,
    const monitor_thresholds_t *thresholds);

void sensor_monitor_print(const monitor_data_t *data);

void sensor_monitor_print_status(monitor_status_t status);

const char *sensor_monitor_status_string(
    monitor_status_t status);

int sensor_monitor_log(const monitor_data_t *data);

void sensor_monitor_deinit(void);

#endif /* SENSOR_MONITOR_H */
