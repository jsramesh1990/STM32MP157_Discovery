#ifndef __APP_POWER_H
#define __APP_POWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "power_manager.h"

/*
 * Application-level power management.
 *
 * Example flow:
 *
 * ACTIVE
 *   |
 *   v
 * Sensor measurement
 *   |
 *   v
 * Data processing
 *   |
 *   v
 * Report data
 *   |
 *   v
 * Prepare sleep
 *   |
 *   v
 * Low-power mode
 *   |
 *   v
 * Wake-up
 */

/* Application power state */
typedef enum
{
    APP_POWER_ACTIVE = 0,
    APP_POWER_PREPARE_SLEEP,
    APP_POWER_SLEEP,
    APP_POWER_WAKEUP,
    APP_POWER_ERROR
} app_power_state_t;

/* Power application context */
typedef struct
{
    app_power_state_t state;

    power_mode_t requested_mode;
    power_wakeup_source_t wakeup_source;

    uint32_t sleep_count;
    uint32_t wakeup_count;

    bool initialized;

} app_power_context_t;

/* Initialize power application */
int AppPower_Init(void);

/* Execute power-management processing */
int AppPower_Run(void);

/* Prepare system for low-power operation */
int AppPower_PrepareSleep(power_mode_t mode);

/* Enter requested low-power state */
int AppPower_EnterSleep(power_mode_t mode);

/* Handle wake-up */
int AppPower_HandleWakeup(void);

/* Get current application power state */
app_power_state_t AppPower_GetState(void);

/* Get power context */
const app_power_context_t *AppPower_GetContext(void);

/* Request a specific power mode */
int AppPower_RequestMode(power_mode_t mode);

/* Request wake-up */
int AppPower_RequestWakeup(void);

#ifdef __cplusplus
}
#endif

#endif /* __APP_POWER_H */
