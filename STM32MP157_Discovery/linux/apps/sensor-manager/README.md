# Sensor Manager

## 1. Overview

The Sensor Manager is a Linux user-space application running on the
Cortex-A7 of the STM32MP157.

It coordinates temperature, pressure and vibration sensor data
received from the Cortex-M4 firmware through OpenAMP/RPMsg.

The Cortex-M4 performs real-time sensor acquisition while the Linux
Cortex-A7 performs high-level processing, monitoring and logging.

## 2. Architecture

```text
                         STM32MP157
                              │
             ┌────────────────┴────────────────┐
             │                                 │
         Cortex-A7                         Cortex-M4
           Linux                         Real-Time Firmware
             │                                 │
             ▼                                 ▼
       sensor-manager                    Sensor Manager
             │                                 │
             │                              Sensors
             │                       ┌─────────┼─────────┐
             │                       ▼         ▼         ▼
             │                    Temperature Pressure Vibration
             │                       │         │         │
             └────────── RPMsg ◄─────┴─────────┴─────────┘
3. Responsibilities

The Sensor Manager is responsible for:

Initializing sensor communication
Communicating with Cortex-M4
Requesting sensor measurements
Receiving sensor data
Validating sensor data
Maintaining the latest sensor values
Monitoring sensor status
Detecting sensor errors
Providing sensor data to Linux applications
Managing sensor sampling requests
4. Supported Sensors

The project contains three sensor categories:

Temperature
Pressure
Vibration

The actual sensor part numbers can be selected according to the
hardware implementation.

5. Sensor Data

The Sensor Manager maintains:

Temperature
Pressure
Vibration
Timestamp
Sensor status
Communication status

Example:

Temperature : 31.5 °C
Pressure    : 101.2 kPa
Vibration   : 0.42 g RMS
Status      : VALID
6. Communication Flow
                  Cortex-M4
                     │
              Read Sensor
                     │
                     ▼
              Process Data
                     │
                     ▼
                   RPMsg
                     │
                     ▼
              Cortex-A7/Linux
                     │
                     ▼
              sensor-manager
                     │
          ┌──────────┼──────────┐
          ▼          ▼          ▼
      Temperature Pressure   Vibration
7. Commands

The Linux application can request operations such as:

SENSOR_INIT
SENSOR_START
SENSOR_STOP
SENSOR_READ
SENSOR_STATUS
SENSOR_CONFIG

Example:

A7 → M4

SENSOR_READ

Response:

M4 → A7

TEMP=31.5
PRESSURE=101.2
VIBRATION=0.42
8. Sensor Manager State
                  INIT
                   │
                   ▼
                READY
                   │
                   ▼
                 RUNNING
                   │
              ┌────┴────┐
              │         │
              ▼         ▼
            ERROR     STOPPED
              │         │
              └────┬────┘
                   ▼
                 READY
9. Low-Power Operation

The Sensor Manager must cooperate with the Power Manager.

                Power Manager
                      │
                      ▼
                Energy Low
                      │
                      ▼
              Sensor Manager
                      │
          ┌───────────┼───────────┐
          ▼           ▼           ▼
      Disable       Reduce      Stop
      Sensor        Rate        Sensor
          │           │           │
          └───────────┼───────────┘
                      ▼
                  Low Power

When energy becomes available again:

Low Power
    │
    ▼
Wake-up
    │
    ▼
Enable Sensors
    │
    ▼
Restore Sampling
    │
    ▼
Running
10. Build

Example:

gcc -Wall -Wextra \
    main.c \
    sensor_manager.c \
    -o sensor-manager

For the target system, use the Yocto-generated cross-compilation SDK.

11. Run
./sensor-manager

Example output:

========================================
       STM32MP157 SENSOR MANAGER
========================================

RPMsg          : CONNECTED
Sensor State   : RUNNING

Temperature    : 31.5 C
Pressure       : 101.2 kPa
Vibration      : 0.42 g RMS

Sensor Status  : VALID
========================================
12. Relationship With Other Applications
                 Linux / Cortex-A7
                        │
       ┌────────────────┼────────────────┐
       │                │                │
       ▼                ▼                ▼
sensor-manager   sensor-monitor   power-manager
       │                │                │
       └────────────────┼────────────────┘
                        │
                       RPMsg
                        │
                        ▼
                  Cortex-M4
                        │
              ┌─────────┼─────────┐
              ▼         ▼         ▼
          Temperature Pressure Vibration
13. Error Handling

The Sensor Manager should detect:

RPMsg disconnect
Sensor timeout
Invalid sensor data
Sensor initialization failure
Sensor communication failure
Out-of-range values
Cortex-M4 failure

When a communication failure occurs, the manager should attempt
recovery and report the error to the monitoring application.

14. Project Role

The Sensor Manager is the main Linux-side interface to the sensor
subsystem.

It separates:

Low-level sensor hardware
        │
        ▼
Cortex-M4 firmware
        │
        ▼
RPMsg
        │
        ▼
Sensor Manager
        │
        ├── Sensor Monitor
        └── Power Manager
