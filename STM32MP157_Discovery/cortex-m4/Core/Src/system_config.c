/*
 * system_config.c
 *
 * Global configuration for the STM32MP157
 * energy-aware sensor firmware.
 */

#include "system_config.h"

#include <string.h>

static system_config_t g_system_config;

/*
 * Initialize default configuration.
 */
void SystemConfig_Init(void)
{
    memset(
        &g_system_config,
        0,
        sizeof(g_system_config));

    g_system_config.sample_period_ms =
        DEFAULT_SAMPLE_PERIOD_MS;

    g_system_config.sleep_period_ms =
        DEFAULT_SLEEP_PERIOD_MS;

    g_system_config.enabled_sensors =
        DEFAULT_ENABLED_SENSORS;

    g_system_config.temperature_threshold =
        DEFAULT_TEMPERATURE_THRESHOLD;

    g_system_config.pressure_threshold =
        DEFAULT_PRESSURE_THRESHOLD;

    g_system_config.vibration_threshold =
        DEFAULT_VIBRATION_THRESHOLD;

    g_system_config.low_energy_threshold =
        ENERGY_LOW_THRESHOLD_PERCENT;

    g_system_config.critical_energy_threshold =
        ENERGY_CRITICAL_THRESHOLD;

    g_system_config.rpmsg_enabled = true;

    g_system_config.low_power_enabled = true;

    g_system_config.wakeup_enabled = true;
}

/*
 * Return configuration.
 */
const system_config_t *
SystemConfig_Get(void)
{
    return &g_system_config;
}

/*
 * Update configuration.
 */
int SystemConfig_Set(
    const system_config_t *config)
{
    if (config == NULL)
    {
        return -1;
    }

    if (!SystemConfig_IsValid(config))
    {
        return -1;
    }

    memcpy(
        &g_system_config,
        config,
        sizeof(system_config_t));

    return 0;
}

/*
 * Restore defaults.
 */
void SystemConfig_Reset(void)
{
    SystemConfig_Init();
}

/*
 * Validate configuration.
 */
bool SystemConfig_IsValid(
    const system_config_t *config)
{
    if (config == NULL)
    {
        return false;
    }

    /*
     * Sampling period must not be zero.
     */
    if (config->sample_period_ms == 0U)
    {
        return false;
    }

    /*
     * Sleep period must not be zero.
     */
    if (config->sleep_period_ms == 0U)
    {
        return false;
    }

    /*
     * At least one sensor should be enabled.
     */
    if (config->enabled_sensors == 0U)
    {
        return false;
    }

    /*
     * Energy thresholds must be valid percentages.
     */
    if (config->low_energy_threshold > 100U)
    {
        return false;
    }

    if (config->critical_energy_threshold > 100U)
    {
        return false;
    }

    if (config->critical_energy_threshold >
        config->low_energy_threshold)
    {
        return false;
    }

    /*
     * Temperature threshold sanity check.
     */
    if (config->temperature_threshold <
        -100.0f)
    {
        return false;
    }

    if (config->temperature_threshold >
        200.0f)
    {
        return false;
    }

    /*
     * Pressure threshold sanity check.
     */
    if (config->pressure_threshold <= 0.0f)
    {
        return false;
    }

    /*
     * Vibration threshold must be non-negative.
     */
    if (config->vibration_threshold < 0.0f)
    {
        return false;
    }

    return true;
}
