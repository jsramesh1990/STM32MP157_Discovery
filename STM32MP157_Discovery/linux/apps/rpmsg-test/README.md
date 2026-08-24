# RPMsg Test Application

## 1. Overview

The RPMsg Test application validates communication between the
Cortex-A7 running Linux and the Cortex-M4 firmware on the STM32MP157.

The application is intended for development, debugging and validation
of the OpenAMP/RPMsg communication channel.

## 2. Architecture

```text
                  STM32MP157
                      │
          ┌───────────┴───────────┐
          │                       │
      Cortex-A7               Cortex-M4
          │                       │
        Linux                  Firmware
          │                       │
          ▼                       │
     rpmsg-test                   │
          │                       │
          ▼                       │
        RPMsg ◄───────────────────┘
          │
          ▼
       Response
3. Purpose

The application verifies:

RPMsg endpoint availability
Cortex-A7 to Cortex-M4 communication
Cortex-M4 to Cortex-A7 communication
Message transmission
Message reception
Response handling
Basic communication errors
4. Test Flow
Start
  │
  ▼
Initialize RPMsg
  │
  ▼
Create Endpoint
  │
  ▼
Send Test Message
  │
  ▼
Wait for M4 Response
  │
  ▼
Validate Response
  │
  ▼
Print Result
  │
  ▼
Repeat
5. Example Messages

Linux to Cortex-M4:

PING

Cortex-M4 response:

PONG

Another test:

SENSOR_READ

Expected response:

SENSOR_DATA
6. Test Commands

Example conceptual commands:

PING
STATUS
SENSOR_READ
POWER_STATUS
LOW_POWER
WAKE

These commands should match the RPMsg protocol implemented by the
Cortex-M4 firmware.

7. Example Output
========================================
       STM32MP157 RPMsg TEST
========================================

RPMsg device : CONNECTED
Endpoint     : READY

TX : PING
RX : PONG

Communication : PASS
========================================
8. Linux RPMsg Interface

The exact RPMsg device and endpoint names depend on the OpenAMP,
remoteproc and Device Tree configuration.

Typical Linux interfaces may include:

/dev/rpmsg*
/sys/class/rpmsg/

Do not assume a fixed device name. Verify the actual target system.

Useful commands:

ls /dev/rpmsg*
ls /sys/class/rpmsg/
dmesg | grep -i rpmsg
dmesg | grep -i remoteproc
9. Cortex-M4 Requirement

The Cortex-M4 firmware must:

Start successfully.
Initialize OpenAMP.
Create the RPMsg endpoint.
Wait for messages.
Process incoming commands.
Send responses.

The Linux application cannot communicate through RPMsg if the
Cortex-M4 firmware and remoteproc/OpenAMP configuration are not ready.

10. Testing Strategy
Test 1: PING
A7 → PING → M4
A7 ← PONG ← M4
Test 2: STATUS
A7 → STATUS → M4
A7 ← STATUS_RESPONSE ← M4
Test 3: SENSOR_READ
A7 → SENSOR_READ → M4
A7 ← SENSOR_DATA ← M4
Test 4: POWER_STATUS
A7 → POWER_STATUS → M4
A7 ← POWER_DATA ← M4
Test 5: Invalid Command
A7 → UNKNOWN → M4
A7 ← ERROR ← M4
11. Build

Example:

gcc -Wall -Wextra \
    main.c \
    rpmsg_test.c \
    -o rpmsg-test

For the target system, use the Yocto SDK/cross-compiler.

12. Debugging

Check remoteproc:

ls /sys/class/remoteproc/

Check RPMsg:

dmesg | grep -i rpmsg

Check Cortex-M4 firmware loading:

dmesg | grep -i remoteproc

Check available devices:

ls -l /dev/rpmsg*
13. Relationship With Other Applications
                 RPMsg Communication
                         │
                         ▼
                    rpmsg-test
                         │
                    Validation
                         │
                         ▼
              ┌──────────┴──────────┐
              ▼                     ▼
       sensor-manager          power-manager
              │                     │
              └──────────┬──────────┘
                         ▼
                      RPMsg
                         │
                         ▼
                    Cortex-M4

rpmsg-test should be used first to validate the communication path
before relying on RPMsg in the production applications.
