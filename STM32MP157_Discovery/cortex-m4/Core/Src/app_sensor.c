/*
 * app_sensor.c
 *
 * High-level sensor application.
 */

#include "app_sensor.h"
#include "app_rpmsg.h"
#include "system_config.h"

#include <string.h>

static app_sensor_context_t g_sensor_context;

/*
 * Initialize sensor application.
 */
int AppSensor_Init(void)
{
    const system_config_t *config;
    sensor_config_t sensor_config;

    memset(&g_sensor_context, 0, sizeof(g_sensor_context));

    config = SystemConfig_Get();

    if (config == NULL)
    {
        return APP_ERROR;
    }

    /*
     * Convert system configuration into
     * sensor-manager configuration.
     */
    sensor_config.sampling_period_ms =
        config->sample_period_ms;

    sensor_config.temperature_threshold =
        config->temperature_threshold;

    sensor_config.pressure_threshold =
        config->pressure_threshold;

    sensor_config.vibration_threshold =
        config->vibration_threshold;

    sensor_config.enabled_sensors =
        config->enabled_sensors;

    sensor_config.interrupt_enabled =
        config->wakeup_enabled;

    /*
     * Initialize lower-level sensor manager.
     */
    if (SensorManager_Init(&sensor_config) != SENSOR_STATUS_OK)
    {
        g_sensor_context.error_count++;
        g_sensor_context.state =
            APP_SENSOR_STATE_ERROR;

        return APP_ERROR;
    }

    /*
     * Power sensors.
     */
    if (SensorManager_PowerOn() != SENSOR_STATUS_OK)
    {
        g_sensor_context.error_count++;
        g_sensor_context.state =
            APP_SENSOR_STATE_ERROR;

        return APP_ERROR;
    }

    g_sensor_context.state =
        APP_SENSOR_STATE_IDLE;

    g_sensor_context.initialized = true;

    return APP_OK;
}

/*
 * Execute one sensor cycle.
 */
int AppSensor_Run(void)
{
    int result;
    sensor_event_t event;

    if (!g_sensor_context.initialized)
    {
        return APP_ERROR;
    }

    switch (g_sensor_context.state)
    {
        case APP_SENSOR_STATE_IDLE:

            /*
             * Move to measurement state.
             */
            g_sensor_context.state =
                APP_SENSOR_STATE_MEASURE;

            break;

        case APP_SENSOR_STATE_MEASURE:

            /*
             * Acquire sensor data.
             */
            result = SensorManager_Read(
                &g_sensor_context.data);

            if (result != SENSOR_STATUS_OK)
            {
                g_sensor_context.error_count++;
                g_sensor_context.state =
                    APP_SENSOR_STATE_ERROR;

                return APP_ERROR;
            }

            g_sensor_context.sample_count++;

            g_sensor_context.state =
                APP_SENSOR_STATE_PROCESS;

            break;

        case APP_SENSOR_STATE_PROCESS:

            /*
             * Process/filter sensor data.
             */
            result = SensorManager_Process(
                &g_sensor_context.data);

            if (result != SENSOR_STATUS_OK)
            {
                g_sensor_context.error_count++;
                g_sensor_context.state =
                    APP_SENSOR_STATE_ERROR;

                return APP_ERROR;
            }

            /*
             * Check thresholds/events.
             */
            event = SensorManager_CheckEvent(
                &g_sensor_context.data);

            if (event != SENSOR_EVENT_NONE)
            {
                g_sensor_context.event_detected = true;

                /*
                 * Notify Cortex-A7.
                 */
                AppRPMsg_SendSensorEvent(
                    (uint32_t)event);
            }
            else
            {
                g_sensor_context.event_detected = false;
            }

            g_sensor_context.state =
                APP_SENSOR_STATE_REPORT;

            break;

        case APP_SENSOR_STATE_REPORT:

            /*
             * Send sensor data to Linux.
             */
            result = AppRPMsg_SendSensorData(
                &g_sensor_context.data);

            if (result != RPMSG_STATUS_OK)
            {
                /*
                 * RPMsg may not yet be ready.
                 * Do not immediately destroy the
                 * sensor state.
                 */
                g_sensor_context.error_count++;
            }

            g_sensor_context.state =
                APP_SENSOR_STATE_SLEEP;

            break;

        case APP_SENSOR_STATE_SLEEP:

            /*
             * Return to idle.
             *
             * Power manager decides whether the
             * complete system can enter low power.
             */
            g_sensor_context.state =
                APP_SENSOR_STATE_IDLE;

            break;

        case APP_SENSOR_STATE_INIT:
            break;

        case APP_SENSOR_STATE_ERROR:
        default:
            return APP_ERROR;
    }

    return APP_OK;
}

/*
 * Process externally supplied sensor data.
 */
int AppSensor_Process(const sensor_data_t *data)
{
    if (data == NULL)
    {
        return APP_ERROR;
    }

    memcpy(
        &g_sensor_context.data,
        data,
        sizeof(sensor_data_t));

    g_sensor_context.sample_count++;

    return APP_OK;
}

/*
 * Check whether an event is active.
 */
bool AppSensor_IsEventDetected(void)
{
    return g_sensor_context.event_detected;
}

/*
 * Return latest sensor data.
 */
const sensor_data_t *AppSensor_GetData(void)
{
    return &g_sensor_context.data;
}

/*
 * Return application context.
 */
const app_sensor_context_t *AppSensor_GetContext(void)
{
    return &g_sensor_context;
}

/*
 * Reset application state.
 */
void AppSensor_Reset(void)
{
    memset(&g_sensor_context.data,
           0,
           sizeof(g_sensor_context.data));

    g_sensor_context.sample_count = 0U;
    g_sensor_context.error_count = 0U;
    g_sensor_context.event_detected = false;

    g_sensor_context.state =
        APP_SENSOR_STATE_IDLE;
}
