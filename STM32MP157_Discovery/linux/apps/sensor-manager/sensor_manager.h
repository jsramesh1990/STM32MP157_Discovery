#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    SENSOR_TYPE_TEMPERATURE = 0,
    SENSOR_TYPE_PRESSURE,
    SENSOR_TYPE_VIBRATION
} sensor_type_t;

typedef enum
{
    SENSOR_STATE_INIT = 0,
    SENSOR_STATE_READY,
    SENSOR_STATE_RUNNING,
    SENSOR_STATE_STOPPED,
    SENSOR_STATE_ERROR
} sensor_state_t;

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

    sensor_state_t state;
} sensor_data_t;

int sensor_manager_init(void);

int sensor_manager_start(void);

int sensor_manager_stop(void);

int sensor_manager_read(sensor_data_t *data);

int sensor_manager_update(void);

int sensor_manager_set_sensor(sensor_type_t sensor,
                              bool enable);

int sensor_manager_get_state(sensor_state_t *state);

const char *sensor_manager_sensor_name(sensor_type_t sensor);

const char *sensor_manager_state_string(sensor_state_t state);

void sensor_manager_deinit(void);

#endif /* SENSOR_MANAGER_H */
