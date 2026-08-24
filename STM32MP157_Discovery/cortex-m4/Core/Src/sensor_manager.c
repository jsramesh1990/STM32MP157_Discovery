/*
 * sensor_manager.c
 *
 * Sensor management layer.
 */

#include "sensor_manager.h"
#include "main.h"

#include <string.h>

static sensor_manager_t g_sensor_manager;

/*
 * --------------------------------------------------------------------------
 * Platform sensor hooks
 * --------------------------------------------------------------------------
 *
 * Replace these functions with actual sensor drivers.
 */

static int Platform_Sensor_Init(
    uint32_t enabled_sensors)
{
    /*
     * Initialize I2C/SPI/ADC/GPIO sensors.
     */

    (void)enabled_sensors;

    return SENSOR_STATUS_OK;
}

static int Platform_Sensor_PowerOn(void)
{
    /*
     * Enable sensor regulator/load switch.
     */

    return SENSOR_STATUS_OK;
}

static int Platform_Sensor_PowerOff(void)
{
    /*
     * Disable sensor regulator/load switch.
     */

    return SENSOR_STATUS_OK;
}

static int Platform_Sensor_Read(
    sensor_data_t *data)
{
    if (data == NULL)
    {
        return SENSOR_STATUS_INVALID_PARAM;
    }

    /*
     * Replace these example values with
     * real I2C/SPI/ADC sensor readings.
     */

    data->temperature = 25.0f;
    data->pressure = 1013.25f;
    data->vibration = 0.0f;

    data->acceleration_x = 0;
    data->acceleration_y = 0;
    data->acceleration_z = 1000;

    data->adc_value = 0;

    data->timestamp = App_GetTick();

    return SENSOR_STATUS_OK;
}

/*
 * Initialize sensor manager.
 */
int SensorManager_Init(
    const sensor_config_t *config)
{
    if (config == NULL)
    {
        return SENSOR_STATUS_INVALID_PARAM;
    }

    memset(
        &g_sensor_manager,
        0,
        sizeof(g_sensor_manager));

    memcpy(
        &g_sensor_manager.config,
        config,
        sizeof(sensor_config_t));

    if (Platform_Sensor_Init(
            config->enabled_sensors)
        != SENSOR_STATUS_OK)
    {
        g_sensor_manager.error_count++;

        return SENSOR_STATUS_ERROR;
    }

    g_sensor_manager.initialized = true;
    g_sensor_manager.powered = false;

    return SENSOR_STATUS_OK;
}

/*
 * Deinitialize sensor manager.
 */
int SensorManager_DeInit(void)
{
    if (!g_sensor_manager.initialized)
    {
        return SENSOR_STATUS_NOT_READY;
    }

    SensorManager_PowerOff();

    memset(
        &g_sensor_manager,
        0,
        sizeof(g_sensor_manager));

    return SENSOR_STATUS_OK;
}

/*
 * Power sensors on.
 */
int SensorManager_PowerOn(void)
{
    if (!g_sensor_manager.initialized)
    {
        return SENSOR_STATUS_NOT_READY;
    }

    if (Platform_Sensor_PowerOn()
        != SENSOR_STATUS_OK)
    {
        g_sensor_manager.error_count++;

        return SENSOR_STATUS_ERROR;
    }

    g_sensor_manager.powered = true;

    return SENSOR_STATUS_OK;
}

/*
 * Power sensors off.
 */
int SensorManager_PowerOff(void)
{
    if (!g_sensor_manager.initialized)
    {
        return SENSOR_STATUS_NOT_READY;
    }

    if (!g_sensor_manager.powered)
    {
        return SENSOR_STATUS_OK;
    }

    if (Platform_Sensor_PowerOff()
        != SENSOR_STATUS_OK)
    {
        g_sensor_manager.error_count++;

        return SENSOR_STATUS_ERROR;
    }

    g_sensor_manager.powered = false;

    return SENSOR_STATUS_OK;
}

/*
 * Read sensors.
 */
int SensorManager_Read(
    sensor_data_t *data)
{
    if (data == NULL)
    {
        return SENSOR_STATUS_INVALID_PARAM;
    }

    if (!g_sensor_manager.initialized)
    {
        return SENSOR_STATUS_NOT_READY;
    }

    if (!g_sensor_manager.powered)
    {
        return SENSOR_STATUS_NOT_READY;
    }

    if (Platform_Sensor_Read(data)
        != SENSOR_STATUS_OK)
    {
        g_sensor_manager.error_count++;

        return SENSOR_STATUS_ERROR;
    }

    memcpy(
        &g_sensor_manager.latest_data,
        data,
        sizeof(sensor_data_t));

    g_sensor_manager.sample_count++;

    return SENSOR_STATUS_OK;
}

/*
 * Process sensor data.
 */
int SensorManager_Process(
    sensor_data_t *data)
{
    if (data == NULL)
    {
        return SENSOR_STATUS_INVALID_PARAM;
    }

    /*
     * Example processing.
     *
     * Real implementation may perform:
     *
     * - Moving average
     * - Digital filtering
     * - Calibration
     * - RMS calculation
     * - FFT
     * - Threshold detection
     */

    if (data->temperature < -100.0f)
    {
        data->temperature = -100.0f;
    }

    if (data->temperature > 200.0f)
    {
        data->temperature = 200.0f;
    }

    return SENSOR_STATUS_OK;
}

/*
 * Check sensor thresholds.
 */
sensor_event_t SensorManager_CheckEvent(
    const sensor_data_t *data)
{
    if (data == NULL)
    {
        return SENSOR_EVENT_ERROR;
    }

    if (data->temperature >=
        g_sensor_manager.config.temperature_threshold)
    {
        g_sensor_manager.last_event =
            SENSOR_EVENT_TEMPERATURE;

        return SENSOR_EVENT_TEMPERATURE;
    }

    if (data->pressure >=
        g_sensor_manager.config.pressure_threshold)
    {
        g_sensor_manager.last_event =
            SENSOR_EVENT_PRESSURE;

        return SENSOR_EVENT_PRESSURE;
    }

    if (data->vibration >=
        g_sensor_manager.config.vibration_threshold)
    {
        g_sensor_manager.last_event =
            SENSOR_EVENT_VIBRATION;

        return SENSOR_EVENT_MOTION;
    }

    g_sensor_manager.last_event =
        SENSOR_EVENT_NONE;

    return SENSOR_EVENT_NONE;
}

/*
 * Get latest sensor data.
 */
const sensor_data_t *
SensorManager_GetLatestData(void)
{
    return &g_sensor_manager.latest_data;
}

/*
 * Get last event.
 */
sensor_event_t SensorManager_GetLastEvent(void)
{
    return g_sensor_manager.last_event;
}

/*
 * Check initialization.
 */
bool SensorManager_IsInitialized(void)
{
    return g_sensor_manager.initialized;
}

/*
 * Check power state.
 */
bool SensorManager_IsPowered(void)
{
    return g_sensor_manager.powered;
}

/*
 * Get manager context.
 */
const sensor_manager_t *
SensorManager_GetContext(void)
{
    return &g_sensor_manager;
}

/*
 * Update configuration.
 */
int SensorManager_SetConfig(
    const sensor_config_t *config)
{
    if (config == NULL)
    {
        return SENSOR_STATUS_INVALID_PARAM;
    }

    if (!g_sensor_manager.initialized)
    {
        return SENSOR_STATUS_NOT_READY;
    }

    memcpy(
        &g_sensor_manager.config,
        config,
        sizeof(sensor_config_t));

    return SENSOR_STATUS_OK;
}

/*
 * Get configuration.
 */
const sensor_config_t *
SensorManager_GetConfig(void)
{
    return &g_sensor_manager.config;
}
