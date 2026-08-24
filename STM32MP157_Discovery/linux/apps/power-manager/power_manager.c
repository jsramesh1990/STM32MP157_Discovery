#include "power_manager.h"

#include <stdio.h>
#include <string.h>

static power_status_t g_power_status;

static void initialize_default_status(void)
{
    memset(&g_power_status, 0, sizeof(g_power_status));

    g_power_status.source = ENERGY_SOURCE_UNKNOWN;
    g_power_status.storage_voltage = 0.0f;
    g_power_status.storage_current = 0.0f;
    g_power_status.energy_available = false;
    g_power_status.rpmsg_connected = false;
    g_power_status.state = POWER_STATE_BOOT;
}

int power_manager_init(void)
{
    initialize_default_status();

    /*
     * Hardware-specific initialization should be added here.
     *
     * Examples:
     * - Open power-supply interfaces
     * - Initialize RPMsg
     * - Read initial storage voltage
     * - Detect energy source
     */

    g_power_status.state = POWER_STATE_ACTIVE;

    return 0;
}

int power_manager_get_status(power_status_t *status)
{
    if (status == NULL)
    {
        return -1;
    }

    *status = g_power_status;

    return 0;
}

int power_manager_update(void)
{
    /*
     * Real implementation should read the actual power state from
     * Linux power-supply interfaces, ADC interfaces or an external
     * energy-harvesting PMIC interface.
     */

    if (g_power_status.storage_voltage > 0.0f)
    {
        g_power_status.energy_available = true;
    }

    return 0;
}

int power_manager_set_state(power_state_t state)
{
    switch (state)
    {
        case POWER_STATE_BOOT:
        case POWER_STATE_ACTIVE:
        case POWER_STATE_LOW_POWER:
        case POWER_STATE_WARNING:
        case POWER_STATE_FAULT:
            g_power_status.state = state;
            return 0;

        default:
            return -1;
    }
}

int power_manager_request_low_power(void)
{
    printf("Power Manager: requesting low-power mode\n");

    /*
     * The production implementation should:
     *
     * 1. Notify the Cortex-M4.
     * 2. Disable unnecessary sensors.
     * 3. Stop unnecessary Linux services.
     * 4. Configure wake-up sources.
     * 5. Request Linux suspend.
     */

    g_power_status.state = POWER_STATE_LOW_POWER;

    return 0;
}

int power_manager_wakeup(void)
{
    printf("Power Manager: wake-up requested\n");

    g_power_status.state = POWER_STATE_ACTIVE;

    return 0;
}

int power_manager_control_sensor(const char *sensor,
                                 bool enable)
{
    if (sensor == NULL)
    {
        return -1;
    }

    printf("Power Manager: sensor=%s state=%s\n",
           sensor,
           enable ? "ON" : "OFF");

    /*
     * Production implementation:
     *
     * Send sensor power-control command to Cortex-M4
     * through RPMsg or use an appropriate Linux interface.
     */

    return 0;
}

const char *power_manager_state_string(power_state_t state)
{
    switch (state)
    {
        case POWER_STATE_BOOT:
            return "BOOT";

        case POWER_STATE_ACTIVE:
            return "ACTIVE";

        case POWER_STATE_LOW_POWER:
            return "LOW_POWER";

        case POWER_STATE_WARNING:
            return "WARNING";

        case POWER_STATE_FAULT:
            return "FAULT";

        default:
            return "UNKNOWN";
    }
}

const char *power_manager_source_string(energy_source_t source)
{
    switch (source)
    {
        case ENERGY_SOURCE_SOLAR:
            return "SOLAR";

        case ENERGY_SOURCE_THERMAL:
            return "THERMAL";

        case ENERGY_SOURCE_KINETIC:
            return "KINETIC";

        default:
            return "UNKNOWN";
    }
}

void power_manager_deinit(void)
{
    /*
     * Close hardware interfaces and RPMsg resources here.
     */

    g_power_status.rpmsg_connected = false;
}
