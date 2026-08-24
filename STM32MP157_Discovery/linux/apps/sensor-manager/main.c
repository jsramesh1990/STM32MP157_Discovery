#include "sensor_manager.h"

#include <stdio.h>
#include <unistd.h>

static void print_sensor_data(const sensor_data_t *data)
{
    printf("\n");
    printf("========================================\n");
    printf("       STM32MP157 SENSOR MANAGER\n");
    printf("========================================\n");

    printf("RPMsg          : %s\n",
           data->rpmsg_connected ? "CONNECTED" : "DISCONNECTED");

    printf("Sensor State   : %s\n",
           sensor_manager_state_string(data->state));

    if (data->temperature_valid)
    {
        printf("Temperature    : %.2f C\n",
               data->temperature_c);
    }
    else
    {
        printf("Temperature    : INVALID\n");
    }

    if (data->pressure_valid)
    {
        printf("Pressure       : %.2f kPa\n",
               data->pressure_kpa);
    }
    else
    {
        printf("Pressure       : INVALID\n");
    }

    if (data->vibration_valid)
    {
        printf("Vibration      : %.2f g RMS\n",
               data->vibration_g_rms);
    }
    else
    {
        printf("Vibration      : INVALID\n");
    }

    printf("Timestamp      : %llu ms\n",
           (unsigned long long)data->timestamp_ms);

    printf("========================================\n");
}

int main(void)
{
    sensor_data_t data;

    printf("Starting STM32MP157 Sensor Manager\n");

    if (sensor_manager_init() != 0)
    {
        fprintf(stderr,
                "Sensor Manager initialization failed\n");
        return 1;
    }

    if (sensor_manager_start() != 0)
    {
        fprintf(stderr,
                "Unable to start sensor manager\n");

        sensor_manager_deinit();

        return 1;
    }

    while (1)
    {
        if (sensor_manager_read(&data) != 0)
        {
            fprintf(stderr,
                    "Sensor read failed\n");

            break;
        }

        print_sensor_data(&data);

        sleep(5);
    }

    sensor_manager_stop();
    sensor_manager_deinit();

    return 0;
}
