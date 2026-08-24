#ifndef __POWER_MANAGER_H
#define __POWER_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/*
 * STM32MP157 Cortex-M4 Power Manager
 *
 * Responsibilities:
 *
 * - Power-state management
 * - Sensor power gating
 * - Wake-up source management
 * - Sleep preparation
 * - Energy monitoring
 *
 * Note:
 * The exact system-level STM32MP1 low-power state is controlled
 * by the complete A7/Linux + TF-A + PMIC + M4 architecture.
 */

/* Power modes */
typedef enum
{
    POWER_MODE_ACTIVE = 0,

    POWER_MODE_IDLE,

    POWER_MODE_SLEEP,

    POWER_MODE_LOW_POWER,

    POWER_MODE_STOP,

    POWER_MODE_STANDBY

} power_mode_t;

/* Wake-up sources */
typedef enum
{
    POWER_WAKEUP_NONE = 0,

    POWER_WAKEUP_RTC,
    POWER_WAKEUP_GPIO,
    POWER_WAKEUP_SENSOR,
    POWER_WAKEUP_RPMSG,
    POWER_WAKEUP_TIMER,
    POWER_WAKEUP_EXTERNAL

} power_wakeup_source_t;

/* Power manager status */
typedef enum
{
    POWER_STATUS_OK = 0,
    POWER_STATUS_ERROR,
    POWER_STATUS_NOT_READY,
    POWER_STATUS_BUSY,
    POWER_STATUS_INVALID_MODE

} power_status_t;

/* Power statistics */
typedef struct
{
    uint32_t sleep_count;
    uint32_t wakeup_count;

    uint32_t total_sleep_ms;
    uint32_t last_sleep_ms;

    uint32_t last_wakeup_source;

    uint32_t voltage_mv;
    uint32_t current_ua;

} power_statistics_t;

/* Power manager context */
typedef struct
{
    power_mode_t current_mode;
    power_mode_t requested_mode;

    power_wakeup_source_t wakeup_source;

    power_statistics_t statistics;

    bool initialized;
    bool sleep_prepared;

} power_manager_t;

/* Initialize power manager */
int PowerManager_Init(void);

/* Deinitialize power manager */
int PowerManager_DeInit(void);

/* Request power mode */
int PowerManager_RequestMode(power_mode_t mode);

/* Get current power mode */
power_mode_t PowerManager_GetMode(void);

/* Prepare for low-power operation */
int PowerManager_PrepareSleep(power_mode_t mode);

/* Enter low-power state */
int PowerManager_EnterSleep(power_mode_t mode);

/* Configure wake-up source */
int PowerManager_SetWakeupSource(power_wakeup_source_t source);

/* Get configured wake-up source */
power_wakeup_source_t PowerManager_GetWakeupSource(void);

/* Process wake-up event */
int PowerManager_HandleWakeup(void);

/* Get wake-up source after resume */
power_wakeup_source_t PowerManager_GetLastWakeupSource(void);

/* Enable sensor power */
int PowerManager_EnableSensorPower(void);

/* Disable sensor power */
int PowerManager_DisableSensorPower(void);

/* Enable external peripheral power */
int PowerManager_EnablePeripheralPower(void);

/* Disable external peripheral power */
int PowerManager_DisablePeripheralPower(void);

/* Get power statistics */
const power_statistics_t *PowerManager_GetStatistics(void);

/* Get power manager context */
const power_manager_t *PowerManager_GetContext(void);

/* Update measured voltage/current */
void PowerManager_UpdateMeasurement(uint32_t voltage_mv,
                                    uint32_t current_ua);

/* Check whether low-power operation is possible */
bool PowerManager_CanEnterLowPower(void);

/* Check whether system is currently in low power */
bool PowerManager_IsLowPower(void);

#ifdef __cplusplus
}
#endif

#endif /* __POWER_MANAGER_H */
