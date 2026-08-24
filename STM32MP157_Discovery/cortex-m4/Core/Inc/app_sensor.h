#ifndef __APP_SENSOR_H
#define __APP_SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "sensor_manager.h"

/*
 * High-level sensor application.
 *
 * Flow:
 *
 * Sensor Manager
 *      |
 *      v
 * Sensor acquisition
 *      |
 *      v
 * Data processing
 *      |
 *      v
 * Event detection
 *      |
 *      v
 * RPMsg notification
 */

/* Sensor application state */
typedef enum
{
    APP_SENSOR_STATE_INIT = 0,
    APP_SENSOR_STATE_IDLE,
    APP_SENSOR_STATE_MEASURE,
    APP_SENSOR_STATE_PROCESS,
    APP_SENSOR_STATE_REPORT,
    APP_SENSOR_STATE_SLEEP,
    APP_SENSOR_STATE_ERROR
} app_sensor_state_t;

/* Sensor application context */
typedef struct
{
    app_sensor_state_t state;

    sensor_data_t data;

    uint32_t sample_count;
    uint32_t error_count;

    bool initialized;
    bool event_detected;

} app_sensor_context_t;

/* Initialize sensor application */
int AppSensor_Init(void);

/* Execute one sensor application cycle */
int AppSensor_Run(void);

/* Process sensor data */
int AppSensor_Process(const sensor_data_t *data);

/* Check whether an event has been detected */
bool AppSensor_IsEventDetected(void);

/* Get latest sensor data */
const sensor_data_t *AppSensor_GetData(void);

/* Get application context */
const app_sensor_context_t *AppSensor_GetContext(void);

/* Reset sensor application state */
void AppSensor_Reset(void);

#ifdef __cplusplus
}
#endif

#endif /* __APP_SENSOR_H */
