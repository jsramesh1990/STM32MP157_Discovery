#ifndef __SENSOR_MANAGER_H
#define __SENSOR_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/*
 * Sensor Manager
 *
 * Responsible for:
 *
 * - Sensor initialization
 * - Sensor power control
 * - Sensor acquisition
 * - Sensor processing
 * - Sensor shutdown
 *
 * Supported interfaces may include:
 *
 * I2C
 * SPI
 * ADC
 * GPIO
 */

/* Sensor status */
typedef enum
{
    SENSOR_STATUS_OK = 0,
    SENSOR_STATUS_ERROR,
    SENSOR_STATUS_NOT_READY,
    SENSOR_STATUS_TIMEOUT,
    SENSOR_STATUS_BUSY,
    SENSOR_STATUS_INVALID_PARAM

} sensor_status_t;

/* Sensor type */
typedef enum
{
    SENSOR_TYPE_NONE = 0,
    SENSOR_TYPE_TEMPERATURE,
    SENSOR_TYPE_PRESSURE,
    SENSOR_TYPE_VIBRATION,
    SENSOR_TYPE_ACCELEROMETER,
    SENSOR_TYPE_ADC

} sensor_type_t;

/* Sensor event */
typedef enum
{
    SENSOR_EVENT_NONE = 0,
    SENSOR_EVENT_THRESHOLD,
    SENSOR_EVENT_MOTION,
    SENSOR_EVENT_TEMPERATURE,
    SENSOR_EVENT_PRESSURE,
    SENSOR_EVENT_ERROR

} sensor_event_t;

/* Sensor measurement */
typedef struct
{
    float temperature;
    float pressure;
    float vibration;

    int32_t acceleration_x;
    int32_t acceleration_y;
    int32_t acceleration_z;

    uint32_t adc_value;

    uint32_t timestamp;

} sensor_data_t;

/* Sensor configuration */
typedef struct
{
    uint32_t sampling_period_ms;

    float temperature_threshold;
    float pressure_threshold;
    float vibration_threshold;

    uint32_t enabled_sensors;

    bool interrupt_enabled;

} sensor_config_t;

/* Sensor manager context */
typedef struct
{
    sensor_config_t config;

    sensor_data_t latest_data;

    sensor_event_t last_event;

    uint32_t sample_count;
    uint32_t error_count;

    bool initialized;
    bool powered;

} sensor_manager_t;

/* Initialize sensor manager */
int SensorManager_Init(const sensor_config_t *config);

/* Deinitialize sensor manager */
int SensorManager_DeInit(void);

/* Power sensor subsystem */
int SensorManager_PowerOn(void);

/* Power down sensor subsystem */
int SensorManager_PowerOff(void);

/* Read all enabled sensors */
int SensorManager_Read(sensor_data_t *data);

/* Process sensor data */
int SensorManager_Process(sensor_data_t *data);

/* Check sensor thresholds */
sensor_event_t SensorManager_CheckEvent(const sensor_data_t *data);

/* Get latest sensor data */
const sensor_data_t *SensorManager_GetLatestData(void);

/* Get last detected event */
sensor_event_t SensorManager_GetLastEvent(void);

/* Check initialization status */
bool SensorManager_IsInitialized(void);

/* Check sensor power status */
bool SensorManager_IsPowered(void);

/* Get manager context */
const sensor_manager_t *SensorManager_GetContext(void);

/* Update sensor configuration */
int SensorManager_SetConfig(const sensor_config_t *config);

/* Get current configuration */
const sensor_config_t *SensorManager_GetConfig(void);

#ifdef __cplusplus
}
#endif

#endif /* __SENSOR_MANAGER_H */
