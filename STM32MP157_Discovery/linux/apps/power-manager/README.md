# Power Manager

## 1. Overview

The Power Manager is a Linux user-space application running on the
Cortex-A7 of the STM32MP157.

Its purpose is to monitor system power conditions and coordinate
power-management decisions for the energy-harvesting sensor platform.

The application works together with the Cortex-M4 firmware, Linux
kernel power-management framework and the energy-harvesting hardware.

## 2. Architecture

```text
                 Energy Source
              Solar / Thermal / Kinetic
                         │
                         ▼
                Energy Harvesting PMIC
                         │
                         ▼
                   Energy Storage
                         │
                         ▼
                    STM32MP157
                         │
             ┌───────────┴───────────┐
             │                       │
         Cortex-A7               Cortex-M4
          Linux                       │
             │                        │
      power-manager                  │
             │                        │
             ├──────── RPMsg ─────────┤
             │                        │
             ▼                        ▼
       Power Policy              Sensor Control
3. Responsibilities

The Power Manager is responsible for:

Monitoring system power state
Monitoring energy-storage voltage
Monitoring harvested-energy status
Selecting an operating mode
Requesting low-power operation
Coordinating sensor activity
Communicating with the Cortex-M4
Monitoring wake-up conditions
Reporting power status
Handling power-related errors
4. Operating States

The application uses logical system states:

                    ┌─────────────┐
                    │    BOOT     │
                    └──────┬──────┘
                           │
                           ▼
                    ┌─────────────┐
                    │    ACTIVE   │
                    └──────┬──────┘
                           │
              ┌────────────┼────────────┐
              │            │            │
              ▼            ▼            ▼
          LOW POWER     WARNING       FAULT
              │
              ▼
          SUSPEND
              │
              ▼
           WAKE-UP
              │
              ▼
           ACTIVE
5. Power Policy

The power manager can use energy conditions to select a system state.

Energy Available
       │
       ▼
Check Storage
       │
       ▼
Check Sensor Requirement
       │
       ▼
Select Operating Mode
       │
 ┌─────┼─────────┐
 ▼     ▼         ▼
HIGH  NORMAL    LOW
 │      │         │
 ▼      ▼         ▼
ACTIVE ACTIVE   LOW POWER
6. Sensor Power Policy

When energy is limited, unnecessary sensors should be disabled.

                    Power Manager
                         │
             ┌───────────┼───────────┐
             │           │           │
             ▼           ▼           ▼
        Temperature    Pressure    Vibration
             │           │           │
          Enable/      Enable/     Enable/
          Disable      Disable     Disable
7. Cortex-M4 Communication

The Linux application can communicate with the Cortex-M4 through
OpenAMP/RPMsg.

Example command:

A7 → M4

POWER_STATE LOW

Response:

M4 → A7

POWER_STATE ACK

Another example:

A7 → M4

SENSOR_DISABLE VIBRATION

Response:

M4 → A7

SENSOR_DISABLE ACK
8. Low-Power Flow
Power Manager
      │
      ▼
Check Energy
      │
      ▼
Energy Low?
   /       \
 NO         YES
 │           │
 ▼           ▼
Normal     Reduce
Operation  Activity
             │
             ▼
       Disable Sensors
             │
             ▼
       Request Low Power
             │
             ▼
          Suspend
9. Linux Power Management

The application can interact with Linux power-management interfaces.

Examples include:

/sys/power/state
/sys/class/power_supply/
/sys/devices/

The exact interfaces available depend on the Linux kernel configuration
and the hardware implementation.

10. Energy Monitoring

The application should monitor:

Energy Source
     │
     ├── Solar
     ├── Thermal
     └── Kinetic
            │
            ▼
       Storage Voltage
            │
            ▼
       Available Energy

Example conceptual output:

Power Manager

Source       : SOLAR
Storage      : SUPERCAP
Voltage      : 4.82 V
Energy State : NORMAL
System State : ACTIVE
11. Fault Handling

Possible conditions:

Low Storage Voltage
Energy Harvesting Failure
Sensor Power Failure
RPMsg Failure
Invalid Power State
Wake-up Failure

The manager should move to a safe low-power state when necessary.

12. Application Flow
Start
 │
 ▼
Initialize
 │
 ▼
Read Power Status
 │
 ▼
Initialize RPMsg
 │
 ▼
Monitor Energy
 │
 ▼
Evaluate Power Policy
 │
 ▼
Control Sensors
 │
 ▼
Update System State
 │
 ▼
Wait
 │
 └──────────────► Repeat
13. Build

Compile the application using the target Linux toolchain.

Example:

gcc -Wall -Wextra \
    main.c \
    power_manager.c \
    -o power-manager

For cross-compilation, use the Yocto-generated SDK/toolchain.

14. Run

Example:

./power-manager
15. Example Output
================================
 STM32MP157 Power Manager
================================

Energy Source : SOLAR
Storage       : SUPERCAP
Voltage       : 4.82 V

System State  : ACTIVE
Sensor State  : ENABLED
RPMsg         : CONNECTED

Power Policy  : NORMAL
================================
16. Project Role

The Power Manager is the Linux-side power-policy component.

Cortex-M4
    │
    │ Real-time sensor control
    ▼
Sensor System
    │
    │ RPMsg
    ▼
Cortex-A7/Linux
    │
    ▼
Power Manager
    │
    ├── Energy monitoring
    ├── Power policy
    ├── Sensor coordination
    └── Low-power requests
