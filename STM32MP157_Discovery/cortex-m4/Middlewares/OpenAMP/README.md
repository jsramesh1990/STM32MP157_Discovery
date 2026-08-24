# OpenAMP / RPMsg Middleware

This directory contains the documentation for the OpenAMP/RPMsg
communication layer used between the STM32MP157 Cortex-M4 and Cortex-A7.

The Cortex-M4 performs low-power sensor acquisition and power-management
tasks, while the Cortex-A7 runs Linux and performs higher-level processing,
storage and communication.

---

## 1. OpenAMP Architecture

The communication architecture is:

```text
                  STM32MP157
        ┌───────────────────────────────┐
        │                               │
        │       Cortex-A7               │
        │                               │
        │          Linux                │
        │             │                 │
        │        RPMsg Driver           │
        │             │                 │
        └─────────────┼─────────────────┘
                      │
                 Shared Memory
                      │
                 RPMsg Channel
                      │
        ┌─────────────┼─────────────────┐
        │             │                 │
        │        OpenAMP/RPMsg          │
        │             │                 │
        │       Cortex-M4              │
        │             │                 │
        │       Sensor Application     │
        │                               │
        └───────────────────────────────┘
````

---

# 2. Why OpenAMP Is Used

The project uses the Cortex-M4 for low-power real-time operations and the
Cortex-A7 for Linux-based high-level processing.

This avoids waking the Cortex-A7 for every sensor operation.

```text
Sensor
   │
   ▼
Cortex-M4
   │
   ├── Read sensor
   ├── Filter data
   ├── Detect event
   └── Monitor power
          │
          │ RPMsg
          ▼
      Cortex-A7
          │
          ├── Linux processing
          ├── Database
          ├── Network
          ├── Cloud
          └── AI / analytics
```

---

# 3. RPMsg Communication

RPMsg provides message-based communication between the two processors.

Example:

```text
Cortex-M4                         Cortex-A7
    │                                 │
    │     SENSOR_DATA                 │
    ├────────────────────────────────►│
    │                                 │
    │     POWER_STATUS                │
    ├────────────────────────────────►│
    │                                 │
    │     EVENT                       │
    ├────────────────────────────────►│
    │                                 │
    │     START_SENSOR                │
    │◄────────────────────────────────┤
    │                                 │
    │     STOP_SENSOR                 │
    │◄────────────────────────────────┤
    │                                 │
    │     ENTER_LOW_POWER             │
    │◄────────────────────────────────┤
```

---

# 4. Message Types

The application can define messages such as:

```text
MESSAGE_SENSOR_DATA
MESSAGE_SENSOR_EVENT
MESSAGE_POWER_STATUS
MESSAGE_SYSTEM_STATUS
MESSAGE_ERROR
MESSAGE_START_SENSOR
MESSAGE_STOP_SENSOR
MESSAGE_READ_SENSOR
MESSAGE_ENTER_LOW_POWER
MESSAGE_WAKEUP
```

Example message:

```c
typedef struct
{
    uint32_t type;
    uint32_t timestamp;
    int32_t temperature;
    int32_t vibration;
    uint32_t energy_level;
} sensor_message_t;
```

---

# 5. Cortex-M4 Responsibilities

The Cortex-M4 should handle:

```text
Sensor acquisition
        │
        ▼
Sensor filtering
        │
        ▼
Threshold detection
        │
        ▼
Power monitoring
        │
        ▼
Wake-up management
        │
        ▼
RPMsg notification
```

The M4 should avoid unnecessary Linux interaction.

For example:

```text
Every 1 second:

Wake M4
   ↓
Read sensor
   ↓
Check threshold
   ↓
Store result
   ↓
Return to low power
```

Only when an important event occurs:

```text
Sensor Event
     ↓
M4
     ↓
Wake A7
     ↓
RPMsg
     ↓
Linux
```

---

# 6. Cortex-A7 Responsibilities

The Cortex-A7/Linux side handles:

```text
RPMsg reception
      │
      ├── Data logging
      ├── Network communication
      ├── Cloud upload
      ├── User interface
      ├── Database
      └── AI/ML processing
```

Linux should not be unnecessarily active for simple sensor measurements.

---

# 7. OpenAMP Data Flow

The complete data flow is:

```text
                  SENSOR
                     │
                     ▼
              Cortex-M4
                     │
              Sensor Manager
                     │
                     ▼
              Data Processing
                     │
                     ▼
              RPMsg Endpoint
                     │
                     ▼
               Shared Memory
                     │
                     ▼
             Linux RPMsg Driver
                     │
                     ▼
               User Application
                     │
                     ▼
              Storage / Network
```

---

# 8. Control Flow

Linux can also control the Cortex-M4:

```text
Linux Application
       │
       ▼
RPMsg
       │
       ▼
Cortex-M4
       │
       ▼
Command Parser
       │
 ┌─────┼─────────┐
 │     │         │
 ▼     ▼         ▼
START STOP    LOW POWER
 │     │         │
 ▼     ▼         ▼
Sensor Sensor   Sleep
 ON     OFF
```

---

# 9. Low-Power Integration

OpenAMP must be designed carefully for the low-power architecture.

Normal operation:

```text
A7 RUN
 │
 M4 RUN
 │
 Sensor ON
 │
 RPMsg active
```

Low-power operation:

```text
A7
 │
 └──── Suspend
        │
        ▼
      M4
        │
        ├── Wake periodically
        ├── Read sensor
        ├── Process data
        └── Sleep
```

Event operation:

```text
M4
 │
 ├── Sensor event
 │
 ▼
Wake A7
 │
 ▼
RPMsg
 │
 ▼
Linux
```

---

# 10. RPMsg Endpoint

The Cortex-M4 creates an RPMsg endpoint.

Conceptually:

```text
rpmsg_sensor
```

Example messages:

```text
sensor/read
sensor/start
sensor/stop
sensor/status
power/status
system/status
```

A simple logical channel can be:

```text
sensor_service
```

---

# 11. Message Format

Use a fixed message structure.

Example:

```c
typedef enum
{
    RPMSG_CMD_START_SENSOR = 0,
    RPMSG_CMD_STOP_SENSOR,
    RPMSG_CMD_READ_SENSOR,
    RPMSG_CMD_POWER_STATUS,
    RPMSG_CMD_LOW_POWER,
    RPMSG_CMD_WAKEUP
} rpmsg_command_t;
```

Sensor response:

```c
typedef struct
{
    uint32_t command;
    uint32_t status;

    int32_t temperature;
    int32_t pressure;
    int32_t vibration;

    uint32_t energy_percent;

    uint32_t timestamp;
} rpmsg_sensor_response_t;
```

---

# 12. Resource Table

OpenAMP/remoteproc uses a resource table to describe resources required by
the remote processor.

Conceptually:

```text
Resource Table
      │
      ├── Firmware version
      ├── RPMsg device
      ├── VirtIO information
      ├── VRING0
      ├── VRING1
      └── Shared memory
```

The resource table must match the memory regions reserved for the Cortex-M4
firmware.

---

# 13. Memory Architecture

The memory relationship is:

```text
STM32MP157
│
├── Cortex-A7
│
├── DDR
│
├── Cortex-M4 SRAM
│     │
│     ├── Firmware
│     ├── Stack
│     ├── Data
│     └── RPMsg resources
│
└── Shared memory
      │
      ├── VRING0
      ├── VRING1
      └── RPMsg buffers
```

The exact memory addresses must match the STM32MP157 BSP/device-tree
configuration.

---

# 14. Linux Side

On the Cortex-A7, Linux provides the remoteproc and RPMsg framework.

Typical flow:

```text
Linux
  │
  ▼
remoteproc
  │
  ▼
Load Cortex-M4 firmware
  │
  ▼
Start Cortex-M4
  │
  ▼
Create RPMsg device
  │
  ▼
Create RPMsg endpoint
  │
  ▼
Application communication
```

Firmware can normally be deployed through the Linux remoteproc firmware
mechanism.

---

# 15. Firmware Startup

The expected startup flow is:

```text
Linux Boot
    │
    ▼
Kernel
    │
    ▼
remoteproc
    │
    ▼
Load M4 firmware
    │
    ▼
Start M4
    │
    ▼
Cortex-M4 Reset_Handler
    │
    ▼
HAL Initialization
    │
    ▼
System Configuration
    │
    ▼
Sensor Initialization
    │
    ▼
Power Manager
    │
    ▼
OpenAMP Initialization
    │
    ▼
RPMsg Endpoint
    │
    ▼
Main Application
```

---

# 16. Project Integration

The middleware is consumed by:

```text
cortex-m4/
│
├── Core/
│   ├── Inc/
│   │
│   └── Src/
│       ├── app_rpmsg.c
│       └── main.c
│
└── Middlewares/
    └── OpenAMP/
        └── README.md
```

The application layer should communicate with OpenAMP through
`app_rpmsg.c`.

Architecture:

```text
app_rpmsg.c
     │
     ▼
OpenAMP
     │
     ▼
RPMsg
     │
     ▼
Linux remoteproc/RPMsg
```

---

# 17. Error Handling

The RPMsg layer should detect:

```text
Endpoint unavailable
Channel unavailable
Message timeout
Invalid message
Buffer unavailable
Remote processor unavailable
Communication failure
```

Example:

```text
RPMsg Error
    │
    ▼
Log Error
    │
    ▼
Retry
    │
    ├── Success → Continue
    │
    └── Failure → Enter safe state
```

---

# 18. Low-Power Rules

OpenAMP/RPMsg communication should not continuously prevent low-power
operation.

Before entering a deep low-power state:

```text
1. Complete pending RPMsg messages
2. Stop unnecessary communication
3. Disable unused peripherals
4. Save required state
5. Configure wake-up source
6. Enter low-power mode
```

On wake-up:

```text
1. Restore clocks
2. Restore peripherals
3. Restore sensor state
4. Re-establish communication if required
5. Continue sensor operation
```

---

# 19. Debugging

Useful Linux commands depend on the BSP and kernel configuration.

Check remote processors:

```bash
ls /sys/class/remoteproc/
```

Check remoteproc state:

```bash
cat /sys/class/remoteproc/remoteproc0/state
```

Firmware name:

```bash
cat /sys/class/remoteproc/remoteproc0/firmware
```

Start remote processor:

```bash
echo start | sudo tee /sys/class/remoteproc/remoteproc0/state
```

Stop remote processor:

```bash
echo stop | sudo tee /sys/class/remoteproc/remoteproc0/state
```

Check kernel messages:

```bash
dmesg | grep -i remoteproc
```

Check RPMsg:

```bash
dmesg | grep -i rpmsg
```

**Note:** `remoteproc0` may be a different instance on a particular BSP.

---

# 20. Testing

Test communication in stages.

### Test 1 — M4 boot

```text
Linux
  ↓
remoteproc
  ↓
M4 starts
  ↓
M4 UART/debug message
```

### Test 2 — RPMsg channel

```text
A7
 ↓
RPMsg
 ↓
M4
 ↓
ACK
```

### Test 3 — Sensor data

```text
Sensor
 ↓
M4
 ↓
RPMsg
 ↓
A7
```

### Test 4 — Power status

```text
M4
 ↓
Energy monitor
 ↓
RPMsg
 ↓
Linux
```

### Test 5 — Low-power wake-up

```text
M4
 ↓
Sleep
 ↓
RTC/GPIO/Sensor interrupt
 ↓
Wake
 ↓
Sensor measurement
```

### Test 6 — Complete system

```text
Energy Harvesting
       ↓
Power Manager
       ↓
M4
       ↓
Sensor
       ↓
Event Detection
       ↓
RPMsg
       ↓
A7/Linux
       ↓
Data Processing
       ↓
Network
       ↓
M4 Low Power
```

---

# 21. Important Design Principle

OpenAMP/RPMsg is **not the mechanism that creates the low-power state**.

It is the communication mechanism between:

```text
Cortex-A7
     ↕
 OpenAMP/RPMsg
     ↕
Cortex-M4
```

Power management is handled separately by:

```text
Power Manager
      +
STM32MP1 power-control framework
      +
PMIC
      +
Clock management
      +
Sensor power switching
      +
Wake-up sources
```

---

# 22. Production Architecture

The final energy-harvesting sensor should follow:

```text
              ENERGY HARVESTING
                      │
                      ▼
               ENERGY STORAGE
                      │
                      ▼
                POWER MANAGER
                      │
                      ▼
              ┌───────────────┐
              │  STM32MP157   │
              │               │
              │ Cortex-M4     │
              │      │        │
              │      ▼        │
              │   Sensors     │
              │               │
              │      ▲        │
              │      │        │
              │   RPMsg       │
              │      │        │
              │ Cortex-A7     │
              │      │        │
              │    Linux      │
              └──────┬────────┘
                     │
                     ▼
              Network / Cloud
```

The Cortex-M4 is therefore the **low-power sensor and event engine**, while
the Cortex-A7 is the **high-performance Linux processing engine**.

---

# 23. Directory Rule

This directory intentionally contains only:

```text
Middlewares/
└── OpenAMP/
    └── README.md
```

The actual OpenAMP/remoteproc/RPMsg implementation should be supplied by the
STM32MP1 BSP/SDK dependency or build system rather than duplicating the
third-party middleware source into this project directory.

---

# 24. Related Project Files

OpenAMP/RPMsg is integrated with:

```text
Core/Inc/app_rpmsg.h
Core/Src/app_rpmsg.c
Core/Src/main.c
```

and with the Linux side through:

```text
Linux
  │
  ├── remoteproc
  ├── RPMsg
  ├── device tree
  └── firmware loading
```

---

# 25. Final Flow

```text
             POWER ON
                 │
                 ▼
          Cortex-A7 Linux
                 │
                 ▼
            remoteproc
                 │
                 ▼
         Load Cortex-M4 FW
                 │
                 ▼
            Cortex-M4
                 │
                 ▼
          OpenAMP Init
                 │
                 ▼
          RPMsg Endpoint
                 │
                 ▼
          Sensor Manager
                 │
                 ▼
           Read Sensor
                 │
                 ▼
          Process Locally
                 │
            Event?
           /       \
         NO         YES
         │           │
         ▼           ▼
      Sleep        RPMsg
         │           │
         │           ▼
         │       Cortex-A7
         │           │
         │           ▼
         │      Linux Processing
         │
         ▼
       Wake
         │
         └───────────────► Repeat
```

````

So the final directory remains exactly:

```text
STM32MP157_Discovery/
└── cortex-m4/
    └── Middlewares/
        └── OpenAMP/
            └── README.md
````

No `.c`, `.h`, resource-table, or third-party OpenAMP source files are added here at this stage.

