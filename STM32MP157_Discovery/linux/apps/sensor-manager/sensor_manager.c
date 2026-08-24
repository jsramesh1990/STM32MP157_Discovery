#include "sensor_manager.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

static sensor_data_t g_sensor_data;

static uint64_t get_timestamp_ms(void)
{
    struct timespec ts;

    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
    {
        return 0;
    }

    return ((uint64_t)ts.tv_sec * 1000ULL) +
           ((uint64_t)ts.tv_nsec / 1000000ULL);
}

static void initialize_sensor_data(void)
{
    memset(&g_sensor_data, 0, sizeof(g_sensor_data));

    g_sensor_data.state = SENSOR_STATE_INIT;
}

int sensor_manager_init(void)
{
    initialize_sensor_data();

    /*
     * Production implementation:
     *
     * - Initialize RPMsg.
     * - Connect to Cortex-M4.
     * - Verify sensor firmware.
     * - Configure sensor defaults.
     */

    g_sensor_data.rpmsg_connected = true;
    g_sensor_data.state = SENSOR_STATE_READY;

    return 0;
}

int sensor_manager_start(void)
{
    if (!g_sensor_data.rpmsg_connected)
    {
        g_sensor_data.state = SENSOR_STATE_ERROR;
        return -1;
    }

    /*
     * Production implementation:
     *
     * Send SENSOR_START through RPMsg.
     */

    g_sensor_data.state = SENSOR_STATE_RUNNING;

    return 0;
}

int sensor_manager_stop(void)
{
    /*
     * Production implementation:
     *
     * Send SENSOR_STOP through RPMsg.
     */

    g_sensor_data.state = SENSOR_STATE_STOPPED;

    return 0;
}

int sensor_manager_read(sensor_data_t *data)
{
    if (data == NULL)
    {
        return -1;
    }

    if (g_sensor_data.state != SENSOR_STATE_RUNNING)
    {
        return -1;
    }

    /*
     * Production implementation:
     *
     * Request sensor data from Cortex-M4 using RPMsg.
     *
     * The current values below are placeholders for application
     * development and interface testing.
     */

    g_sensor_data.temperature_c = 31.5f;
    g_sensor_data.pressure_kpa = 101.2f;
    g_sensor_data.vibration_g_rms = 0.42f;

    g_sensor_data.temperature_valid = true;
    g_sensor_data.pressure_valid = true;
    g_sensor_data.vibration_valid = true;

    g_sensor_data.timestamp_ms = get_timestamp_ms();

    *data = g_sensor_data;

    return 0;
}

int sensor_manager_update(void)
{
    sensor_data_t data;

    if (sensor_manager_read(&data) != 0)
    {
        return -1;
    }

    printf("Temperature : %.2f C\n",
           data.temperature_c);

    printf("Pressure    : %.2f kPa\n",
           data.pressure_kpa);

    printf("Vibration   : %.2f g RMS\n",
           data.vibration_g_rms);

    return 0;
}

int sensor_manager_set_sensor(sensor_type_t sensor,
                              bool enable)
{
    const char *name;

    name = sensor_manager_sensor_name(sensor);

    if (name == NULL)
    {
        return -1;
    }

    printf("Sensor %s: %s\n",
           name,
           enable ? "ENABLED" : "DISABLED");

    /*
     * Production implementation:
     *
     * Send sensor enable/disable command through RPMsg.
     */

    return 0;
}

int sensor_manager_get_state(sensor_state_t *state)
{
    if (state == NULL)
    {
        return -1;
    }

    *state = g_sensor_data.state;

    return 0;
}

const char *sensor_manager_sensor_name(sensor_type_t sensor)
{
    switch (sensor)
    {
        case SENSOR_TYPE_TEMPERATURE:
            return "temperature";

        case SENSOR_TYPE_PRESSURE:
            return "pressure";

        case SENSOR_TYPE_VIBRATION:
            return "vibration";

        default:
            return NULL;
    }
}

const char *sensor_manager_state_string(sensor_state_t state)
{
    switch (state)
    {
        case SENSOR_STATE_INIT:
            return "INIT";

        case SENSOR_STATE_READY:
            return "READY";

        case SENSOR_STATE_RUNNING:
            return "RUNNING";

        case SENSOR_STATE_STOPPED:
            return "STOPPED";

        case SENSOR_STATE_ERROR:
            return "ERROR";

        default:
            return "UNKNOWN";
    }
}

void sensor_manager_deinit(void)
{
    /*
     * Production implementation:
     *
     * - Stop sensors.
     * - Close RPMsg.
     * - Release resources.
     */

    g_sensor_data.rpmsg_connected = false;
    g_sensor_data.state = SENSOR_STATE_STOPPED;
}
