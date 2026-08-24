/*
 * power_manager.c
 *
 * STM32MP157 Cortex-M4 power-management layer.
 */

#include "power_manager.h"
#include "main.h"

#include <string.h>

static power_manager_t g_power_manager;

/*
 * --------------------------------------------------------------------------
 * Platform-specific power hooks
 * --------------------------------------------------------------------------
 */

static int Platform_Power_Init(void)
{
    /*
     * Initialize:
     *
     * - GPIO power controls
     * - RTC
     * - timers
     * - wake-up GPIO
     * - sensor power regulators
     */

    return POWER_STATUS_OK;
}

static int Platform_Power_EnterSleep(
    power_mode_t mode)
{
    /*
     * IMPORTANT:
     *
     * Replace this function with the appropriate
     * STM32MP1 low-power implementation.
     *
     * The complete STM32MP1 low-power transition
     * involves the A7/Linux/TF-A/PMIC architecture.
     */

    switch (mode)
    {
        case POWER_MODE_IDLE:
            /*
             * CPU idle implementation.
             */
            break;

        case POWER_MODE_SLEEP:
            /*
             * M4 sleep implementation.
             */
            break;

        case POWER_MODE_LOW_POWER:
            /*
             * Platform-specific low-power mode.
             */
            break;

        case POWER_MODE_STOP:
            /*
             * Platform-specific Stop handling.
             */
            break;

        case POWER_MODE_STANDBY:
            /*
             * Standby should normally be coordinated
             * with the complete STM32MP1 power architecture.
             */
            break;

        case POWER_MODE_ACTIVE:
        default:
            return POWER_STATUS_INVALID_MODE;
    }

    return POWER_STATUS_OK;
}

static int Platform_Power_Wakeup(void)
{
    /*
     * Clear wake-up flags and restore required
     * clocks/peripherals here.
     */

    return POWER_STATUS_OK;
}

static int Platform_SensorPower_Enable(void)
{
    /*
     * Drive sensor load-switch/regulator GPIO.
     */

    return POWER_STATUS_OK;
}

static int Platform_SensorPower_Disable(void)
{
    /*
     * Disable sensor power.
     */

    return POWER_STATUS_OK;
}

static int Platform_PeripheralPower_Enable(void)
{
    return POWER_STATUS_OK;
}

static int Platform_PeripheralPower_Disable(void)
{
    return POWER_STATUS_OK;
}

/*
 * Initialize power manager.
 */
int PowerManager_Init(void)
{
    memset(
        &g_power_manager,
        0,
        sizeof(g_power_manager));

    if (Platform_Power_Init()
        != POWER_STATUS_OK)
    {
        return POWER_STATUS_ERROR;
    }

    g_power_manager.current_mode =
        POWER_MODE_ACTIVE;

    g_power_manager.requested_mode =
        POWER_MODE_ACTIVE;

    g_power_manager.wakeup_source =
        POWER_WAKEUP_NONE;

    g_power_manager.initialized = true;

    return POWER_STATUS_OK;
}

/*
 * Deinitialize.
 */
int PowerManager_DeInit(void)
{
    if (!g_power_manager.initialized)
    {
        return POWER_STATUS_NOT_READY;
    }

    memset(
        &g_power_manager,
        0,
        sizeof(g_power_manager));

    return POWER_STATUS_OK;
}

/*
 * Request power mode.
 */
int PowerManager_RequestMode(
    power_mode_t mode)
{
    if (!g_power_manager.initialized)
    {
        return POWER_STATUS_NOT_READY;
    }

    if (mode < POWER_MODE_ACTIVE ||
        mode > POWER_MODE_STANDBY)
    {
        return POWER_STATUS_INVALID_MODE;
    }

    g_power_manager.requested_mode = mode;

    return POWER_STATUS_OK;
}

/*
 * Get current mode.
 */
power_mode_t PowerManager_GetMode(void)
{
    return g_power_manager.current_mode;
}

/*
 * Prepare for sleep.
 */
int PowerManager_PrepareSleep(
    power_mode_t mode)
{
    if (!g_power_manager.initialized)
    {
        return POWER_STATUS_NOT_READY;
    }

    if (mode == POWER_MODE_ACTIVE)
    {
        return POWER_STATUS_INVALID_MODE;
    }

    /*
     * Disable unnecessary peripheral power.
     */
    PowerManager_DisablePeripheralPower();

    /*
     * Disable sensor power.
     */
    PowerManager_DisableSensorPower();

    g_power_manager.requested_mode = mode;
    g_power_manager.sleep_prepared = true;

    return POWER_STATUS_OK;
}

/*
 * Enter low-power mode.
 */
int PowerManager_EnterSleep(
    power_mode_t mode)
{
    uint32_t start_tick;
    uint32_t end_tick;

    if (!g_power_manager.initialized)
    {
        return POWER_STATUS_NOT_READY;
    }

    if (!g_power_manager.sleep_prepared)
    {
        return POWER_STATUS_ERROR;
    }

    start_tick = App_GetTick();

    g_power_manager.current_mode = mode;

    if (Platform_Power_EnterSleep(mode)
        != POWER_STATUS_OK)
    {
        g_power_manager.current_mode =
            POWER_MODE_ACTIVE;

        return POWER_STATUS_ERROR;
    }

    end_tick = App_GetTick();

    g_power_manager.statistics.last_sleep_ms =
        end_tick - start_tick;

    g_power_manager.statistics.total_sleep_ms +=
        g_power_manager.statistics.last_sleep_ms;

    g_power_manager.statistics.sleep_count++;

    return POWER_STATUS_OK;
}

/*
 * Configure wake-up source.
 */
int PowerManager_SetWakeupSource(
    power_wakeup_source_t source)
{
    if (!g_power_manager.initialized)
    {
        return POWER_STATUS_NOT_READY;
    }

    g_power_manager.wakeup_source = source;

    return POWER_STATUS_OK;
}

/*
 * Get configured wake-up source.
 */
power_wakeup_source_t
PowerManager_GetWakeupSource(void)
{
    return g_power_manager.wakeup_source;
}

/*
 * Handle wake-up.
 */
int PowerManager_HandleWakeup(void)
{
    if (!g_power_manager.initialized)
    {
        return POWER_STATUS_NOT_READY;
    }

    if (Platform_Power_Wakeup()
        != POWER_STATUS_OK)
    {
        return POWER_STATUS_ERROR;
    }

    g_power_manager.current_mode =
        POWER_MODE_ACTIVE;

    g_power_manager.sleep_prepared = false;

    g_power_manager.statistics.wakeup_count++;

    g_power_manager.statistics.last_wakeup_source =
        (uint32_t)g_power_manager.wakeup_source;

    /*
     * Restore peripheral power.
     */
    PowerManager_EnablePeripheralPower();

    return POWER_STATUS_OK;
}

/*
 * Get last wake-up source.
 */
power_wakeup_source_t
PowerManager_GetLastWakeupSource(void)
{
    return g_power_manager.wakeup_source;
}

/*
 * Enable sensor power.
 */
int PowerManager_EnableSensorPower(void)
{
    if (!g_power_manager.initialized)
    {
        return POWER_STATUS_NOT_READY;
    }

    if (Platform_SensorPower_Enable()
        != POWER_STATUS_OK)
    {
        return POWER_STATUS_ERROR;
    }

    return POWER_STATUS_OK;
}

/*
 * Disable sensor power.
 */
int PowerManager_DisableSensorPower(void)
{
    if (!g_power_manager.initialized)
    {
        return POWER_STATUS_NOT_READY;
    }

    if (Platform_SensorPower_Disable()
        != POWER_STATUS_OK)
    {
        return POWER_STATUS_ERROR;
    }

    return POWER_STATUS_OK;
}

/*
 * Enable external peripherals.
 */
int PowerManager_EnablePeripheralPower(void)
{
    if (!g_power_manager.initialized)
    {
        return POWER_STATUS_NOT_READY;
    }

    if (Platform_PeripheralPower_Enable()
        != POWER_STATUS_OK)
    {
        return POWER_STATUS_ERROR;
    }

    return POWER_STATUS_OK;
}

/*
 * Disable external peripherals.
 */
int PowerManager_DisablePeripheralPower(void)
{
    if (!g_power_manager.initialized)
    {
        return POWER_STATUS_NOT_READY;
    }

    if (Platform_PeripheralPower_Disable()
        != POWER_STATUS_OK)
    {
        return POWER_STATUS_ERROR;
    }

    return POWER_STATUS_OK;
}

/*
 * Get power statistics.
 */
const power_statistics_t *
PowerManager_GetStatistics(void)
{
    return &g_power_manager.statistics;
}

/*
 * Get manager context.
 */
const power_manager_t *
PowerManager_GetContext(void)
{
    return &g_power_manager;
}

/*
 * Update voltage/current measurement.
 */
void PowerManager_UpdateMeasurement(
    uint32_t voltage_mv,
    uint32_t current_ua)
{
    g_power_manager.statistics.voltage_mv =
        voltage_mv;

    g_power_manager.statistics.current_ua =
        current_ua;
}

/*
 * Check whether low-power operation
 * is currently possible.
 */
bool PowerManager_CanEnterLowPower(void)
{
    if (!g_power_manager.initialized)
    {
        return false;
    }

    if (!g_power_manager.sleep_prepared)
    {
        return false;
    }

    return true;
}

/*
 * Check current power state.
 */
bool PowerManager_IsLowPower(void)
{
    return
        (g_power_manager.current_mode !=
         POWER_MODE_ACTIVE);
}
