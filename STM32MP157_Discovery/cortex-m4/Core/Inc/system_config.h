#ifndef __SYSTEM_CONFIG_H
#define __SYSTEM_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/*
 * System configuration
 *
 * Central configuration for the STM32MP157 energy-aware
 * sensor application.
 */

/* Firmware version */
#define FW_VERSION_MAJOR       1U
#define FW_VERSION_MINOR       0U
#define FW_VERSION_PATCH       0U

#define FW_VERSION_STRING      "1.0.0"

/* Default sensor configuration */
#define DEFAULT_SAMPLE_PERIOD_MS       1000U

/* Sensor thresholds */
#define DEFAULT_TEMPERATURE_THRESHOLD  70.0f
#define DEFAULT_PRESSURE_THRESHOLD      1200.0f
#define DEFAULT_VIBRATION_THRESHOLD    10.0f

/* Energy thresholds */
#define ENERGY_LOW_THRESHOLD_PERCENT    20U
#define ENERGY_CRITICAL_THRESHOLD       10U

/* Power-management timing */
#define DEFAULT_SLEEP_PERIOD_MS        10000U
#define DEFAULT_WAKEUP_TIMEOUT_MS       5000U

/* RPMsg configuration */
#define RPMSG_ENDPOINT_NAME             "energy_sensor"
#define RPMSG_MAX_MESSAGE_SIZE          256U

/* Sensor enable flags */
#define SENSOR_ENABLE_TEMPERATURE       (1U << 0)
#define SENSOR_ENABLE_PRESSURE          (1U << 1)
#define SENSOR_ENABLE_VIBRATION         (1U << 2)
#define SENSOR_ENABLE_ACCELEROMETER     (1U << 3)
#define SENSOR_ENABLE_ADC               (1U << 4)

/* Default enabled sensors */
#define DEFAULT_ENABLED_SENSORS \
    (SENSOR_ENABLE_TEMPERATURE | \
     SENSOR_ENABLE_VIBRATION)

/* Application configuration */
typedef struct
{
    uint32_t sample_period_ms;

    uint32_t sleep_period_ms;

    uint32_t enabled_sensors;

    float temperature_threshold;
    float pressure_threshold;
    float vibration_threshold;

    uint32_t low_energy_threshold;
    uint32_t critical_energy_threshold;

    bool rpmsg_enabled;
    bool low_power_enabled;
    bool wakeup_enabled;

} system_config_t;

/* Initialize default configuration */
void SystemConfig_Init(void);

/* Get system configuration */
const system_config_t *SystemConfig_Get(void);

/* Update system configuration */
int SystemConfig_Set(const system_config_t *config);

/* Restore default configuration */
void SystemConfig_Reset(void);

/* Validate configuration */
bool SystemConfig_IsValid(const system_config_t *config);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_CONFIG_H */
