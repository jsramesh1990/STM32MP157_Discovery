#ifndef __APP_RPMSG_H
#define __APP_RPMSG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "sensor_manager.h"

/*
 * Cortex-M4 <-> Cortex-A7 communication.
 *
 * Communication path:
 *
 * Cortex-M4
 *     |
 *     v
 * OpenAMP
 *     |
 *     v
 * RPMsg
 *     |
 *     v
 * Shared Memory / VirtIO
 *     |
 *     v
 * Linux RPMsg
 *     |
 *     v
 * Cortex-A7
 */

/* RPMsg application status */
typedef enum
{
    RPMSG_STATUS_OK = 0,
    RPMSG_STATUS_ERROR,
    RPMSG_STATUS_NOT_READY,
    RPMSG_STATUS_TIMEOUT,
    RPMSG_STATUS_BUSY
} rpmsg_status_t;

/* Message types */
typedef enum
{
    RPMSG_MSG_NONE = 0,

    /* Sensor messages */
    RPMSG_MSG_SENSOR_DATA,
    RPMSG_MSG_SENSOR_EVENT,

    /* Power messages */
    RPMSG_MSG_POWER_STATUS,
    RPMSG_MSG_WAKEUP_EVENT,

    /* System messages */
    RPMSG_MSG_SYSTEM_READY,
    RPMSG_MSG_SYSTEM_STATUS,
    RPMSG_MSG_COMMAND,
    RPMSG_MSG_ACK,
    RPMSG_MSG_ERROR

} rpmsg_message_type_t;

/* Commands received from Cortex-A7 */
typedef enum
{
    RPMSG_CMD_NONE = 0,

    RPMSG_CMD_START_SENSOR,
    RPMSG_CMD_STOP_SENSOR,
    RPMSG_CMD_READ_SENSOR,
    RPMSG_CMD_ENTER_LOW_POWER,
    RPMSG_CMD_WAKEUP,
    RPMSG_CMD_GET_STATUS,
    RPMSG_CMD_RESET

} rpmsg_command_t;

/* Sensor data message */
typedef struct
{
    uint32_t timestamp;

    float temperature;
    float pressure;
    float vibration;

    uint32_t energy_level;

    uint32_t event_status;

} rpmsg_sensor_message_t;

/* Power status message */
typedef struct
{
    uint32_t power_mode;

    uint32_t wakeup_source;

    uint32_t energy_level;

    uint32_t voltage_mv;

    uint32_t current_ua;

} rpmsg_power_message_t;

/* Command message */
typedef struct
{
    rpmsg_command_t command;

    uint32_t parameter;

} rpmsg_command_message_t;

/* Generic RPMsg packet */
typedef struct
{
    rpmsg_message_type_t type;

    uint32_t length;

    union
    {
        rpmsg_sensor_message_t sensor;
        rpmsg_power_message_t power;
        rpmsg_command_message_t command;

    } payload;

} rpmsg_message_t;

/* Initialize RPMsg/OpenAMP */
int AppRPMsg_Init(void);

/* Start RPMsg endpoint */
int AppRPMsg_Start(void);

/* Stop RPMsg endpoint */
int AppRPMsg_Stop(void);

/* Process incoming RPMsg messages */
int AppRPMsg_Process(void);

/* Send sensor data to Linux */
int AppRPMsg_SendSensorData(const sensor_data_t *data);

/* Send sensor event to Linux */
int AppRPMsg_SendSensorEvent(uint32_t event);

/* Send power status to Linux */
int AppRPMsg_SendPowerStatus(const rpmsg_power_message_t *status);

/* Send system ready message */
int AppRPMsg_SendReady(void);

/* Send acknowledgement */
int AppRPMsg_SendAck(uint32_t command);

/* Check whether RPMsg is ready */
bool AppRPMsg_IsReady(void);

/* Handle received command */
int AppRPMsg_HandleCommand(const rpmsg_command_message_t *command);

#ifdef __cplusplus
}
#endif

#endif /* __APP_RPMSG_H */
