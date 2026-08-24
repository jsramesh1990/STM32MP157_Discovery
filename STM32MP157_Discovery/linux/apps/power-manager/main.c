#include "power_manager.h"

#include <stdio.h>
#include <unistd.h>

static void print_status(const power_status_t *status)
{
    printf("\n");
    printf("========================================\n");
    printf("       STM32MP157 POWER MANAGER\n");
    printf("========================================\n");

    printf("Energy Source : %s\n",
           power_manager_source_string(status->source));

    printf("Storage       : %.2f V\n",
           status->storage_voltage);

    printf("Current       : %.2f A\n",
           status->storage_current);

    printf("Energy        : %s\n",
           status->energy_available ? "AVAILABLE" : "LOW");

    printf("RPMsg         : %s\n",
           status->rpmsg_connected ? "CONNECTED" : "DISCONNECTED");

    printf("System State  : %s\n",
           power_manager_state_string(status->state));

    printf("========================================\n");
}

int main(void)
{
    power_status_t status;

    printf("Starting STM32MP157 Power Manager\n");

    if (power_manager_init() != 0)
    {
        fprintf(stderr, "Power Manager initialization failed\n");
        return 1;
    }

    while (1)
    {
        if (power_manager_update() != 0)
        {
            fprintf(stderr, "Power status update failed\n");
        }

        if (power_manager_get_status(&status) != 0)
        {
            fprintf(stderr, "Unable to read power status\n");
            break;
        }

        print_status(&status);

        /*
         * Example monitoring period.
         *
         * In the production system this should be replaced with an
         * event-driven design where possible.
         */
        sleep(5);
    }

    power_manager_deinit();

    return 0;
}
