/*
 * app_rpmsg.c
 *
 * Cortex-M4 <-> Cortex-A7 RPMsg application layer.
 */

#include "app_rpmsg.h"
#include "app_power.h"
#include "app_sensor.h"

#include <string.h>

static bool g_rpmsg_initialized = false;
static bool g_rpmsg_ready = false;

/*
 * --------------------------------------------------------------------------
 * Platform-specific OpenAMP/RPMsg hooks
 * --------------------------------------------------------------------------
 *
 * Connect these functions to the STM32CubeMP1/OpenAMP implementation.
 */

static int Platform_RPMsg_Init(void)
{
    /*
     * Typical implementation will initialize:
     *
     * OpenAMP_Init(...)
     * VirtIO
     * Shared memory
     * RPMsg endpoint
     *
     * Do not place hardware-specific implementation
     * directly into the application layer.
     */

    return RPMSG_STATUS_OK;
}

static int Platform_RPMsg_Start(void)
{
    /*
     * Create RPMsg endpoint here.
     */

    return RPMSG_STATUS_OK;
}

static int Platform_RPMsg_Stop(void)
{
    return RPMSG_STATUS_OK;
}

static int Platform_RPMsg_Send(
    const void *data,
    uint32_t size)
{
    if (data == NULL || size == 0U)
    {
        return RPMSG_STATUS_ERROR;
    }

    /*
     * Connect to rpmsg_send() /
     * OpenAMP endpoint send operation.
     */

    (void)data;
    (void)size;

    return RPMSG_STATUS_OK;
}

static int Platform_RPMsg_Receive(
    void *data,
    uint32_t size)
{
    /*
     * Connect to OpenAMP/RPMsg receive
     * callback or queue.
     */

    (void)data;
    (void)size;

    return RPMSG_STATUS_NOT_READY;
}

/*
 * Initialize RPMsg.
 */
int AppRPMsg_Init(void)
{
    if (Platform_RPMsg_Init()
        != RPMSG_STATUS_OK)
    {
        return RPMSG_STATUS_ERROR;
    }

    g_rpmsg_initialized = true;
    g_rpmsg_ready = false;

    return RPMSG_STATUS_OK;
}

/*
 * Start RPMsg endpoint.
 */
int AppRPMsg_Start(void)
{
    if (!g_rpmsg_initialized)
    {
        return RPMSG_STATUS_NOT_READY;
    }

    if (Platform_RPMsg_Start()
        != RPMSG_STATUS_OK)
    {
        return RPMSG_STATUS_ERROR;
    }

    g_rpmsg_ready = true;

    return RPMSG_STATUS_OK;
}

/*
 * Stop RPMsg.
 */
int AppRPMsg_Stop(void)
{
    if (!g_rpmsg_initialized)
    {
        return RPMSG_STATUS_NOT_READY;
    }

    Platform_RPMsg_Stop();

    g_rpmsg_ready = false;

    return RPMSG_STATUS_OK;
}

/*
 * Process received messages.
 */
int AppRPMsg_Process(void)
{
    rpmsg_message_t message;
    int result;

    if (!g_rpmsg_ready)
    {
        return RPMSG_STATUS_NOT_READY;
    }

    memset(&message, 0, sizeof(message));

    result = Platform_RPMsg_Receive(
        &message,
        sizeof(message));

    if (result == RPMSG_STATUS_NOT_READY)
    {
        /*
         * No message currently available.
         */
        return RPMSG_STATUS_OK;
    }

    if (result != RPMSG_STATUS_OK)
    {
        return RPMSG_STATUS_ERROR;
    }

    if (message.type == RPMSG_MSG_COMMAND)
    {
        return AppRPMsg_HandleCommand(
            &message.payload.command);
    }

    return RPMSG_STATUS_OK;
}

/*
 * Send sensor data.
 */
int AppRPMsg_SendSensorData(
    const sensor_data_t *data)
{
    rpmsg_message_t message;

    if (data == NULL)
    {
        return RPMSG_STATUS_ERROR;
    }

    if (!g_rpmsg_ready)
    {
        return RPMSG_STATUS_NOT_READY;
    }

    memset(&message, 0, sizeof(message));

    message.type =
        RPMSG_MSG_SENSOR_DATA;

    message.length =
        sizeof(rpmsg_sensor_message_t);

    message.payload.sensor.timestamp =
        data->timestamp;

    message.payload.sensor.temperature =
        data->temperature;

    message.payload.sensor.pressure =
        data->pressure;

    message.payload.sensor.vibration =
        data->vibration;

    message.payload.sensor.energy_level = 0U;

    message.payload.sensor.event_status =
        (uint32_t)AppSensor_IsEventDetected();

    return Platform_RPMsg_Send(
        &message,
        sizeof(message));
}

/*
 * Send sensor event.
 */
int AppRPMsg_SendSensorEvent(
    uint32_t event)
{
    rpmsg_message_t message;

    if (!g_rpmsg_ready)
    {
        return RPMSG_STATUS_NOT_READY;
    }

    memset(&message, 0, sizeof(message));

    message.type =
        RPMSG_MSG_SENSOR_EVENT;

    message.length =
        sizeof(uint32_t);

    message.payload.sensor.event_status =
        event;

    return Platform_RPMsg_Send(
        &message,
        sizeof(message));
}

/*
 * Send power status.
 */
int AppRPMsg_SendPowerStatus(
    const rpmsg_power_message_t *status)
{
    rpmsg_message_t message;

    if (status == NULL)
    {
        return RPMSG_STATUS_ERROR;
    }

    if (!g_rpmsg_ready)
    {
        return RPMSG_STATUS_NOT_READY;
    }

    memset(&message, 0, sizeof(message));

    message.type =
        RPMSG_MSG_POWER_STATUS;

    message.length =
        sizeof(rpmsg_power_message_t);

    memcpy(
        &message.payload.power,
        status,
        sizeof(rpmsg_power_message_t));

    return Platform_RPMsg_Send(
        &message,
        sizeof(message));
}

/*
 * Send M4 ready message.
 */
int AppRPMsg_SendReady(void)
{
    rpmsg_message_t message;

    if (!g_rpmsg_ready)
    {
        return RPMSG_STATUS_NOT_READY;
    }

    memset(&message, 0, sizeof(message));

    message.type =
        RPMSG_MSG_SYSTEM_READY;

    message.length = 0U;

    return Platform_RPMsg_Send(
        &message,
        sizeof(message));
}

/*
 * Send command acknowledgement.
 */
int AppRPMsg_SendAck(uint32_t command)
{
    rpmsg_message_t message;

    if (!g_rpmsg_ready)
    {
        return RPMSG_STATUS_NOT_READY;
    }

    memset(&message, 0, sizeof(message));

    message.type =
        RPMSG_MSG_ACK;

    message.length =
        sizeof(uint32_t);

    message.payload.command.command =
        (rpmsg_command_t)command;

    return Platform_RPMsg_Send(
        &message,
        sizeof(message));
}

/*
 * Check RPMsg status.
 */
bool AppRPMsg_IsReady(void)
{
    return g_rpmsg_ready;
}

/*
 * Handle A7 command.
 */
int AppRPMsg_HandleCommand(
    const rpmsg_command_message_t *command)
{
    if (command == NULL)
    {
        return RPMSG_STATUS_ERROR;
    }

    switch (command->command)
    {
        case RPMSG_CMD_START_SENSOR:

            SensorManager_PowerOn();

            AppRPMsg_SendAck(
                command->command);

            break;

        case RPMSG_CMD_STOP_SENSOR:

            SensorManager_PowerOff();

            AppRPMsg_SendAck(
                command->command);

            break;

        case RPMSG_CMD_READ_SENSOR:
        {
            const sensor_data_t *data;

            data = AppSensor_GetData();

            if (data != NULL)
            {
                AppRPMsg_SendSensorData(data);
            }

            AppRPMsg_SendAck(
                command->command);

            break;
        }

        case RPMSG_CMD_ENTER_LOW_POWER:

            AppPower_RequestMode(
                (power_mode_t)command->parameter);

            AppPower_PrepareSleep(
                (power_mode_t)command->parameter);

            AppRPMsg_SendAck(
                command->command);

            break;

        case RPMSG_CMD_WAKEUP:

            AppPower_RequestWakeup();

            AppRPMsg_SendAck(
                command->command);

            break;

        case RPMSG_CMD_GET_STATUS:
        {
            rpmsg_power_message_t status;

            const power_statistics_t *stats;

            stats =
                PowerManager_GetStatistics();

            memset(&status, 0, sizeof(status));

            status.power_mode =
                (uint32_t)PowerManager_GetMode();

            status.wakeup_source =
                (uint32_t)
                PowerManager_GetLastWakeupSource();

            if (stats != NULL)
            {
                status.voltage_mv =
                    stats->voltage_mv;

                status.current_ua =
                    stats->current_ua;
            }

            AppRPMsg_SendPowerStatus(&status);

            break;
        }

        case RPMSG_CMD_RESET:

            /*
             * Platform-specific reset may be
             * implemented here.
             */

            AppRPMsg_SendAck(
                command->command);

            break;

        case RPMSG_CMD_NONE:
        default:

            return RPMSG_STATUS_ERROR;
    }

    return RPMSG_STATUS_OK;
}
