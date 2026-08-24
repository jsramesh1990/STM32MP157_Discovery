#ifndef RPMSG_TEST_H
#define RPMSG_TEST_H

#include <stddef.h>

#define RPMSG_TEST_MAX_MESSAGE_SIZE 256

typedef enum
{
    RPMSG_TEST_OK = 0,
    RPMSG_TEST_ERROR = -1,
    RPMSG_TEST_TIMEOUT = -2,
    RPMSG_TEST_NOT_CONNECTED = -3
} rpmsg_test_result_t;

typedef struct
{
    int connected;
    int endpoint_ready;
    unsigned int tx_count;
    unsigned int rx_count;
    unsigned int error_count;
} rpmsg_test_status_t;

int rpmsg_test_init(void);

int rpmsg_test_connect(void);

int rpmsg_test_send(const char *message);

int rpmsg_test_receive(char *buffer,
                       size_t buffer_size,
                       int timeout_ms);

int rpmsg_test_ping(void);

int rpmsg_test_get_status(rpmsg_test_status_t *status);

void rpmsg_test_close(void);

#endif /* RPMSG_TEST_H */
