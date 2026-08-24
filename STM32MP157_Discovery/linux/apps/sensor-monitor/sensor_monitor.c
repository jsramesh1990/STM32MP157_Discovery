#include "sensor_monitor.h"

#include <stdio.h>
#include <time.h>

static monitor_thresholds_t g_thresholds;

int sensor_monitor_init(void)
{
    /*
     * Default thresholds.
     *
     * These values are examples only and must be changed according
     * to the actual sensor/application requirements.
     */

    g_thresholds.temperature_high = 70.0f;
    g_thresholds.pressure_high = 110.0f;
    g_thresholds.vibration_high = 2.0f;

    return 0;
}

int sensor_monitor_update(const monitor_data_t *data)
{
    monitor_status_t status;

    if (data == NULL)
    {
        return -1;
    }

    sensor_monitor_print(data);

    status = (monitor_status_t)
        sensor_monitor_check_thresholds(data, &g_thresholds);

    sensor_monitor_print_status(status);

    sensor_monitor_log(data);

    return 0;
}

int sensor_monitor_check_thresholds(
    const monitor_data_t *data,
    const monitor_thresholds_t *thresholds)
{
    if (data == NULL || thresholds == NULL)
    {
        return MONITOR_STATUS_ERROR;
    }

    if (!data->rpmsg_connected)
    {
        return MONITOR_STATUS_ERROR;
    }

    if (data->temperature_valid &&
        data->temperature_c >= thresholds->temperature_high)
    {
        return MONITOR_STATUS_WARNING;
    }

    if (data->pressure_valid &&
        data->pressure_kpa >= thresholds->pressure_high)
    {
        return MONITOR_STATUS_WARNING;
    }

    if (data->vibration_valid &&
        data->vibration_g_rms >= thresholds->vibration_high)
    {
        return MONITOR_STATUS_WARNING;
    }

    return MONITOR_STATUS_NORMAL;
}

void sensor_monitor_print(const monitor_data_t *data)
{
    if (data == NULL)
    {
        return;
    }

    printf("\n");
    printf("========================================\n");
    printf("       STM32MP157 SENSOR MONITOR\n");
    printf("========================================\n");

    if (data->temperature_valid)
    {
        printf("Temperature : %.2f C\n",
               data->temperature_c);
    }
    else
    {
        printf("Temperature : INVALID\n");
    }

    if (data->pressure_valid)
    {
        printf("Pressure    : %.2f kPa\n",
               data->pressure_kpa);
    }
    else
    {
        printf("Pressure    : INVALID\n");
    }

    if (data->vibration_valid)
    {
        printf("Vibration   : %.2f g RMS\n",
               data->vibration_g_rms);
    }
    else
    {
        printf("Vibration   : INVALID\n");
    }

    printf("Timestamp   : %llu ms\n",
           (unsigned long long)data->timestamp_ms);

    printf("RPMsg       : %s\n",
           data->rpmsg_connected ? "CONNECTED" : "DISCONNECTED");

    printf("========================================\n");
}

void sensor_monitor_print_status(monitor_status_t status)
{
    printf("Status      : %s\n",
           sensor_monitor_status_string(status));

    if (status == MONITOR_STATUS_WARNING)
    {
        printf("WARNING: Sensor threshold exceeded\n");
    }
    else if (status == MONITOR_STATUS_ERROR)
    {
        printf("ERROR: Sensor communication problem\n");
    }
}

const char *sensor_monitor_status_string(
    monitor_status_t status)
{
    switch (status)
    {
        case MONITOR_STATUS_NORMAL:
            return "NORMAL";

        case MONITOR_STATUS_WARNING:
            return "WARNING";

        case MONITOR_STATUS_ERROR:
            return "ERROR";

        default:
            return "UNKNOWN";
    }
}

int sensor_monitor_log(const monitor_data_t *data)
{
    FILE *file;

    if (data == NULL)
    {
        return -1;
    }

    file = fopen("sensor_data.csv", "a");

    if (file == NULL)
    {
        return -1;
    }

    fprintf(file,
            "%llu,%.2f,%.2f,%.2f\n",
            (unsigned long long)data->timestamp_ms,
            data->temperature_c,
            data->pressure_kpa,
            data->vibration_g_rms);

    fclose(file);

    return 0;
}

void sensor_monitor_deinit(void)
{
    /*
     * Release monitoring resources here.
     */
}
