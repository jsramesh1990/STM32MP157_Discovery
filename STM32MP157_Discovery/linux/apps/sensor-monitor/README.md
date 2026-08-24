# Sensor Monitor

## 1. Overview

Sensor Monitor is a Linux user-space application running on the
Cortex-A7 of the STM32MP157.

It provides a human-readable view of the sensor subsystem and
displays temperature, pressure, vibration and system status.

The application is intended for development, testing, debugging and
field monitoring.

## 2. Architecture

```text
                  STM32MP157
                       │
             ┌─────────┴─────────┐
             │                   │
         Cortex-A7           Cortex-M4
           Linux             Firmware
             │                   │
             ▼                   ▼
      sensor-monitor       Sensor acquisition
             │                   │
             │                Sensors
             │          ┌────────┼────────┐
             │          ▼        ▼        ▼
             │       Temp     Pressure  Vibration
             │          │        │        │
             └──────────┼────────┼────────┘
                        │
                       RPMsg
                        │
                        ▼
                 sensor-manager
                        │
                        ▼
                 sensor-monitor
3. Responsibilities

Sensor Monitor is responsible for:

Displaying temperature
Displaying pressure
Displaying vibration
Displaying sensor validity
Displaying RPMsg status
Displaying sensor-manager status
Displaying timestamps
Logging sensor measurements
Detecting abnormal values
Providing a simple monitoring interface
4. Sensor Data

The application monitors:

Temperature
Pressure
Vibration
Timestamp
Sensor status
RPMsg status
System state

Example:

Temperature : 31.5 C
Pressure    : 101.2 kPa
Vibration   : 0.42 g RMS
Status      : NORMAL
5. Monitoring Flow
Start
  │
  ▼
Initialize
  │
  ▼
Connect to Sensor Manager
  │
  ▼
Read Sensor Data
  │
  ▼
Validate Data
  │
  ▼
Display Data
  │
  ▼
Log Data
  │
  ▼
Check Thresholds
  │
  ▼
Wait
  │
  └──────────────► Repeat
6. Example Output
========================================
       STM32MP157 SENSOR MONITOR
========================================

Temperature : 31.50 C
Pressure    : 101.20 kPa
Vibration   : 0.42 g RMS

Sensor State : RUNNING
RPMsg        : CONNECTED
Status       : NORMAL

========================================
7. Abnormal Condition

The monitor can detect values outside configured limits.

Example:

Temperature : 82.4 C
Pressure    : 101.3 kPa
Vibration   : 3.82 g RMS

WARNING:
High temperature detected
High vibration detected
8. Low-Power System

The monitor should not prevent the system from entering low-power
operation.

When the system enters low power:

Sensor Monitor
      │
      ▼
Detect inactive state
      │
      ▼
Stop continuous polling
      │
      ▼
Wait for sensor/system wake-up
      │
      ▼
Resume monitoring

This is important for the energy-harvesting design.

9. Build

Example:

gcc -Wall -Wextra \
    main.c \
    sensor_monitor.c \
    -o sensor-monitor

For the STM32MP157 target, use the Yocto-generated cross-compilation
SDK.

10. Run
./sensor-monitor
11. Logging

Sensor measurements can be logged for later analysis.

Example:

timestamp,temperature,pressure,vibration
1000,31.5,101.2,0.42
2000,31.6,101.3,0.41
3000,31.5,101.2,0.43

The production implementation can use a dedicated log file or
another data-storage mechanism.

12. Threshold Monitoring

Example thresholds:

Temperature:
    Normal  < 70 C
    Warning >= 70 C

Vibration:
    Normal  < 2.0 g
    Warning >= 2.0 g

The actual thresholds must be selected according to the sensor and
application requirements.

13. Relationship With Other Applications
                    Linux
                      │
        ┌─────────────┼─────────────┐
        │             │             │
        ▼             ▼             ▼
sensor-manager   sensor-monitor  power-manager
        │             ▲
        │             │
        └─────────────┘
              Sensor Data

rpmsg-test is used separately to validate the underlying RPMsg
communication before using the sensor applications.

14. Project Role

Sensor Monitor is the presentation and monitoring layer.

Sensor Hardware
      │
      ▼
Cortex-M4
      │
      ▼
RPMsg
      │
      ▼
sensor-manager
      │
      ▼
sensor-monitor
      │
      ├── Display
      ├── Logging
      ├── Threshold detection
      └── Status monitoring
