#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/*
 * STM32MP157 Cortex-M4 application
 *
 * Main responsibilities:
 * - System initialization
 * - Sensor application startup
 * - RPMsg/OpenAMP startup
 * - Power-management initialization
 * - Main application loop
 */

/* Application return/status codes */
#define APP_OK              (0)
#define APP_ERROR           (-1)

/* Generic application status */
typedef enum
{
    APP_STATUS_OK = 0,
    APP_STATUS_ERROR,
    APP_STATUS_BUSY,
    APP_STATUS_TIMEOUT,
    APP_STATUS_NOT_READY
} app_status_t;

/* Main application states */
typedef enum
{
    APP_STATE_INIT = 0,
    APP_STATE_SENSOR_INIT,
    APP_STATE_RPMSG_INIT,
    APP_STATE_ACTIVE,
    APP_STATE_LOW_POWER,
    APP_STATE_WAKEUP,
    APP_STATE_ERROR
} app_state_t;

/* Global application state */
extern volatile app_state_t g_app_state;

/* System initialization */
void System_Init(void);

/* Application initialization */
void Application_Init(void);

/* Main application processing */
void Application_Run(void);

/* Error handler */
void Application_ErrorHandler(void);

/* System tick / delay interface */
uint32_t App_GetTick(void);
void App_Delay(uint32_t delay_ms);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
