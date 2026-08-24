/*
 * app_power.c
 *
 * Application-level power management.
 */

#include "app_power.h"
#include "app_rpmsg.h"
#include "sensor_manager.h"
#include "system_config.h"

#include <string.h>

static app_power_context_t g_power_context;

/*
 * Initialize power application.
 */
int AppPower_Init(void)
{
    memset(&g_power_context,
           0,
           sizeof(g_power_context));

    if (PowerManager_Init() != POWER_STATUS_OK)
    {
        g_power_context.state =
            APP_POWER_ERROR;

        return APP_ERROR;
    }

    g_power_context.state =
        APP_POWER_ACTIVE;

    g_power_context.requested_mode =
        POWER_MODE_ACTIVE;

    g_power_context.wakeup_source =
        POWER_WAKEUP_NONE;

    g_power_context.initialized = true;

    return APP_OK;
}

/*
 * Run power-management state machine.
 */
int AppPower_Run(void)
{
    const system_config_t *config;

    if (!g_power_context.initialized)
    {
        return APP_ERROR;
    }

    config = SystemConfig_Get();

    if (config == NULL)
    {
        return APP_ERROR;
    }

    switch (g_power_context.state)
    {
        case APP_POWER_ACTIVE:

            /*
             * Once sensor processing is complete,
             * prepare for low power.
             */
            if (config->low_power_enabled)
            {
                g_power_context.state =
                    APP_POWER_PREPARE_SLEEP;
            }

            break;

        case APP_POWER_PREPARE_SLEEP:

            if (AppPower_PrepareSleep(
                    POWER_MODE_SLEEP) != APP_OK)
            {
                g_power_context.state =
                    APP_POWER_ERROR;

                return APP_ERROR;
            }

            g_power_context.state =
                APP_POWER_SLEEP;

            break;

        case APP_POWER_SLEEP:

            if (AppPower_EnterSleep(
                    g_power_context.requested_mode)
                    != APP_OK)
            {
                g_power_context.state =
                    APP_POWER_ERROR;

                return APP_ERROR;
            }

            /*
             * After return from the low-power
             * function, the system has resumed.
             */
            g_power_context.state =
                APP_POWER_WAKEUP;

            break;

        case APP_POWER_WAKEUP:

            if (AppPower_HandleWakeup() != APP_OK)
            {
                g_power_context.state =
                    APP_POWER_ERROR;

                return APP_ERROR;
            }

            g_power_context.state =
                APP_POWER_ACTIVE;

            break;

        case APP_POWER_ERROR:
        default:
            return APP_ERROR;
    }

    return APP_OK;
}

/*
 * Prepare system for sleep.
 */
int AppPower_PrepareSleep(power_mode_t mode)
{
    /*
     * Stop sensor acquisition before entering
     * low-power operation.
     */
    if (SensorManager_PowerOff()
        != SENSOR_STATUS_OK)
    {
        return APP_ERROR;
    }

    /*
     * Configure wake-up source.
     */
    if (PowerManager_SetWakeupSource(
            POWER_WAKEUP_RTC)
        != POWER_STATUS_OK)
    {
        return APP_ERROR;
    }

    /*
     * Configure power manager.
     */
    if (PowerManager_PrepareSleep(mode)
        != POWER_STATUS_OK)
    {
        return APP_ERROR;
    }

    g_power_context.requested_mode = mode;
    g_power_context.state =
        APP_POWER_SLEEP;

    return APP_OK;
}

/*
 * Enter requested low-power mode.
 */
int AppPower_EnterSleep(power_mode_t mode)
{
    /*
     * Enter platform-specific low-power mode.
     *
     * The actual STM32MP157 low-power transition
     * should be implemented through the appropriate
     * STM32MP1 power-management architecture.
     */
    if (PowerManager_EnterSleep(mode)
        != POWER_STATUS_OK)
    {
        return APP_ERROR;
    }

    g_power_context.sleep_count++;

    return APP_OK;
}

/*
 * Handle wake-up.
 */
int AppPower_HandleWakeup(void)
{
    power_wakeup_source_t source;

    if (PowerManager_HandleWakeup()
        != POWER_STATUS_OK)
    {
        return APP_ERROR;
    }

    source =
        PowerManager_GetLastWakeupSource();

    g_power_context.wakeup_source = source;
    g_power_context.wakeup_count++;

    /*
     * Restore sensor power.
     */
    if (SensorManager_PowerOn()
        != SENSOR_STATUS_OK)
    {
        return APP_ERROR;
    }

    /*
     * Inform Linux about the wake-up event.
     */
    AppRPMsg_SendSensorEvent(
        (uint32_t)source);

    return APP_OK;
}

/*
 * Get current application power state.
 */
app_power_state_t AppPower_GetState(void)
{
    return g_power_context.state;
}

/*
 * Get power context.
 */
const app_power_context_t *AppPower_GetContext(void)
{
    return &g_power_context;
}

/*
 * Request power mode.
 */
int AppPower_RequestMode(power_mode_t mode)
{
    if (mode < POWER_MODE_ACTIVE ||
        mode > POWER_MODE_STANDBY)
    {
        return APP_ERROR;
    }

    g_power_context.requested_mode = mode;

    return APP_OK;
}

/*
 * Request wake-up.
 */
int AppPower_RequestWakeup(void)
{
    g_power_context.state =
        APP_POWER_WAKEUP;

    return APP_OK;
}
