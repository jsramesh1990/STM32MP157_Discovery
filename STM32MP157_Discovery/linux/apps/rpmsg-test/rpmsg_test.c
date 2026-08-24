#include "rpmsg_test.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

static rpmsg_test_status_t g_status;

static void reset_status(void)
{
    memset(&g_status, 0, sizeof(g_status));
}

int rpmsg_test_init(void)
{
    reset_status();

    /*
     * Production implementation:
     *
     * 1. Detect the RPMsg device.
     * 2. Open the RPMsg endpoint.
     * 3. Configure communication.
     *
     * The actual implementation depends on the Linux RPMsg/OpenAMP
     * configuration and Device Tree.
     */

    return RPMSG_TEST_OK;
}

int rpmsg_test_connect(void)
{
    /*
     * Replace this development stub with the actual RPMsg endpoint
     * discovery/open operation.
     */

    g_status.connected = 1;
    g_status.endpoint_ready = 1;

    printf("RPMsg: endpoint connected\n");

    return RPMSG_TEST_OK;
}

int rpmsg_test_send(const char *message)
{
    if (message == NULL)
    {
        return RPMSG_TEST_ERROR;
    }

    if (!g_status.connected || !g_status.endpoint_ready)
    {
        return RPMSG_TEST_NOT_CONNECTED;
    }

    printf("RPMsg TX: %s\n", message);

    /*
     * Production implementation:
     *
     * Write the message to the RPMsg endpoint.
     */

    g_status.tx_count++;

    return RPMSG_TEST_OK;
}

int rpmsg_test_receive(char *buffer,
                        size_t buffer_size,
                        int timeout_ms)
{
    if (buffer == NULL || buffer_size == 0)
    {
        return RPMSG_TEST_ERROR;
    }

    if (!g_status.connected || !g_status.endpoint_ready)
    {
        return RPMSG_TEST_NOT_CONNECTED;
    }

    /*
     * Production implementation:
     *
     * Read from the RPMsg endpoint using the appropriate Linux
     * RPMsg interface.
     *
     * This placeholder simulates a response for initial application
     * development.
     */

    if (timeout_ms > 0)
    {
        usleep((useconds_t)timeout_ms * 1000U);
    }

    snprintf(buffer, buffer_size, "PONG");

    printf("RPMsg RX: %s\n", buffer);

    g_status.rx_count++;

    return RPMSG_TEST_OK;
}

int rpmsg_test_ping(void)
{
    char response[RPMSG_TEST_MAX_MESSAGE_SIZE];

    int result;

    result = rpmsg_test_send("PING");

    if (result != RPMSG_TEST_OK)
    {
        g_status.error_count++;
        return result;
    }

    result = rpmsg_test_receive(response,
                                sizeof(response),
                                100);

    if (result != RPMSG_TEST_OK)
    {
        g_status.error_count++;
        return result;
    }

    if (strcmp(response, "PONG") != 0)
    {
        g_status.error_count++;
        return RPMSG_TEST_ERROR;
    }

    return RPMSG_TEST_OK;
}

int rpmsg_test_get_status(rpmsg_test_status_t *status)
{
    if (status == NULL)
    {
        return RPMSG_TEST_ERROR;
    }

    *status = g_status;

    return RPMSG_TEST_OK;
}

void rpmsg_test_close(void)
{
    /*
     * Production implementation:
     *
     * Close the RPMsg endpoint and release associated resources.
     */

    g_status.connected = 0;
    g_status.endpoint_ready = 0;
}
