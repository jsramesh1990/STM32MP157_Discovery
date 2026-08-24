#include "sensor_monitor.h"

#include <stdio.h>
#include <unistd.h>

static int read_sensor_data(monitor_data_t *data)
{
    if (data == NULL)
    {
        return -1;
    }

    /*
     * Development values.
     *
     * In the complete project these values should come from
     * sensor-manager/RPMsg instead of being generated here.
     */

    data->temperature_c = 31.5f;
    data->pressure_kpa = 101.2f;
    data->vibration_g_rms = 0.42f;

    data->temperature_valid = true;
    data->pressure_valid = true;
    data->vibration_valid = true;

    data->rpmsg_connected = true;

    /*
     * sensor-manager normally supplies the timestamp.
     */
    data->timestamp_ms = 0;

    return 0;
}

int main(void)
{
    monitor_data_t data;

    printf("Starting STM32MP157 Sensor Monitor\n");

    if (sensor_monitor_init() != 0)
    {
        fprintf(stderr,
                "Sensor Monitor initialization failed\n");

        return 1;
    }

    while (1)
    {
        if (read_sensor_data(&data) != 0)
        {
            fprintf(stderr,
                    "Unable to read sensor data\n");

            break;
        }

        if (sensor_monitor_update(&data) != 0)
        {
            fprintf(stderr,
                    "Sensor monitor update failed\n");
        }

        sleep(5);
    }

    sensor_monitor_deinit();

    return 0;
}
