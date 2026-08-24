#include "rpmsg_test.h"

#include <stdio.h>

static void print_status(void)
{
    rpmsg_test_status_t status;

    if (rpmsg_test_get_status(&status) != RPMSG_TEST_OK)
    {
        printf("Unable to read RPMsg status\n");
        return;
    }

    printf("\n");
    printf("========================================\n");
    printf("          STM32MP157 RPMsg TEST\n");
    printf("========================================\n");

    printf("Connected     : %s\n",
           status.connected ? "YES" : "NO");

    printf("Endpoint      : %s\n",
           status.endpoint_ready ? "READY" : "NOT READY");

    printf("TX Messages   : %u\n",
           status.tx_count);

    printf("RX Messages   : %u\n",
           status.rx_count);

    printf("Errors        : %u\n",
           status.error_count);

    printf("========================================\n");
}

int main(void)
{
    int result;

    printf("Starting STM32MP157 RPMsg Test\n");

    result = rpmsg_test_init();

    if (result != RPMSG_TEST_OK)
    {
        fprintf(stderr, "RPMsg initialization failed\n");
        return 1;
    }

    result = rpmsg_test_connect();

    if (result != RPMSG_TEST_OK)
    {
        fprintf(stderr, "RPMsg connection failed\n");
        rpmsg_test_close();
        return 1;
    }

    printf("\nRunning PING test...\n");

    result = rpmsg_test_ping();

    if (result == RPMSG_TEST_OK)
    {
        printf("RPMsg PING test: PASS\n");
    }
    else
    {
        printf("RPMsg PING test: FAIL\n");
    }

    print_status();

    rpmsg_test_close();

    return (result == RPMSG_TEST_OK) ? 0 : 1;
}
