
### `power_manager.h`

```c
#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    POWER_STATE_BOOT = 0,
    POWER_STATE_ACTIVE,
    POWER_STATE_LOW_POWER,
    POWER_STATE_WARNING,
    POWER_STATE_FAULT
} power_state_t;

typedef enum
{
    ENERGY_SOURCE_UNKNOWN = 0,
    ENERGY_SOURCE_SOLAR,
    ENERGY_SOURCE_THERMAL,
    ENERGY_SOURCE_KINETIC
} energy_source_t;

typedef struct
{
    energy_source_t source;
    float storage_voltage;
    float storage_current;
    bool energy_available;
    bool rpmsg_connected;
    power_state_t state;
} power_status_t;

int power_manager_init(void);

int power_manager_get_status(power_status_t *status);

int power_manager_update(void);

int power_manager_set_state(power_state_t state);

int power_manager_request_low_power(void);

int power_manager_wakeup(void);

int power_manager_control_sensor(const char *sensor,
                                bool enable);

const char *power_manager_state_string(power_state_t state);

const char *power_manager_source_string(energy_source_t source);

void power_manager_deinit(void);

#endif /* POWER_MANAGER_H */
