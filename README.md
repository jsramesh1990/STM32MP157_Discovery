
# STM32MP157_Discovery

[![Platform](https://img.shields.io/badge/Platform-STM32MP157-blue)](https://www.st.com/en/microcontrollers-microprocessors/stm32mp1-series.html)
[![Board](https://img.shields.io/badge/Board-STM32MP157%20Discovery-green)](https://www.st.com/en/evaluation-tools/stm32mp157c-dk2.html)
[![CPU](https://img.shields.io/badge/CPU-Cortex--A7%20%2B%20Cortex--M4-orange)](https://www.st.com/en/microcontrollers-microprocessors/stm32mp1-series.html)
[![OS](https://img.shields.io/badge/OS-Linux-yellow)](https://www.kernel.org/)
[![Yocto](https://img.shields.io/badge/Build-Yocto-purple)](https://www.yoctoproject.org/)
[![Language](https://img.shields.io/badge/Language-C%20%2F%20Shell%20%2F%20Python-lightgrey)](https://www.c-language.org/)
[![License](https://img.shields.io/badge/License-CLOSED-red)](#license)

A low-power industrial sensor platform based on the **STM32MP157** MPU, combining Cortex-A7 Linux processing, Cortex-M4 real-time control, sensor management, RPMsg communication, low-power operation, and solar/thermal/kinetic energy-harvesting concepts.

---

## Project Overview

This project demonstrates how an STM32MP157-based embedded platform can be designed for energy-constrained industrial sensing applications.

The main objective is to combine:

- Energy harvesting
- Low-power system operation
- Cortex-A7 Linux processing
- Cortex-M4 real-time sensor control
- Temperature sensing
- Pressure sensing
- Vibration sensing
- RPMsg communication
- Linux power management
- RTC/GPIO wake-up
- Device Tree configuration
- Yocto/OpenEmbedded integration
- Automated testing
- Power measurement
- Serial monitoring
- Log collection and analysis

The STM32MP157 Discovery Kit is used as the development and demonstration platform.

> **Important:** The STM32MP157 Discovery Kit itself is not a sub-1 µA complete system. The STM32MP157 silicon supports very-low-power modes under specified conditions, while achieving an ultra-low-power system-level product requires a dedicated hardware design with optimized power rails, leakage, peripherals, sensors, and energy-harvesting circuitry.

---

# System Concept

```text
                    ENERGY SOURCE
                         │
              ┌──────────┼──────────┐
              │          │          │
             Solar     Thermal    Kinetic
              │          │          │
              └──────────┼──────────┘
                         │
                         ▼
              Energy Harvesting PMIC
                         │
                         ▼
                 Storage Element
              Supercapacitor / Battery
                         │
                         ▼
                 Power Management
                         │
                         ▼
                 ┌───────────────┐
                 │  STM32MP157   │
                 │               │
                 │ Cortex-A7     │
                 │ Cortex-M4     │
                 └───────┬───────┘
                         │
             ┌───────────┼───────────┐
             │           │           │
             ▼           ▼           ▼
          Sensors      RPMsg       Linux
             │           │           │
             │           │           ▼
             │           │       Applications
             │           │           │
             │           ▼           │
             │      Cortex-M4       │
             │                      │
             └──────────┬───────────┘
                        │
                        ▼
                  Data Processing
                        │
                        ▼
                  Communication
                        │
                        ▼
                    Gateway
                        │
                        ▼
                       Cloud
````

---

# Main Design Principle

The system should not keep the complete Linux subsystem running continuously when the application does not require it.

Instead, the architecture uses **duty cycling**.

```text
                  ┌───────────────┐
                  │ LOW POWER     │
                  └───────┬───────┘
                          │
                          │ RTC / GPIO /
                          │ sensor event
                          ▼
                  ┌───────────────┐
                  │ WAKE SYSTEM   │
                  └───────┬───────┘
                          │
                          ▼
                  ┌───────────────┐
                  │ Cortex-M4     │
                  │ Sensor Read   │
                  └───────┬───────┘
                          │
                          ▼
                  ┌───────────────┐
                  │ Filter /      │
                  │ Process       │
                  └───────┬───────┘
                          │
                       Event?
                      /       \
                    No         Yes
                    │           │
                    │           ▼
                    │      Wake Cortex-A7
                    │           │
                    │           ▼
                    │        Linux
                    │           │
                    │           ▼
                    │      Advanced
                    │      Processing
                    │           │
                    │           ▼
                    │       Transmit
                    │
                    ▼
                  Sleep
```

---

# Architecture

```text
┌──────────────────────────────────────────────────────────────┐
│                    STM32MP157 PLATFORM                       │
│                                                              │
│  ┌──────────────────────┐      ┌──────────────────────────┐ │
│  │      Cortex-A7       │      │       Cortex-M4          │ │
│  │                      │      │                          │ │
│  │ Linux / Applications │      │ Sensor Control           │ │
│  │ Services             │      │ Real-Time Processing     │ │
│  │ RPMsg Endpoint       │◄────►│ RPMsg Endpoint            │ │
│  │ Power Management     │      │ Low-Power Tasks           │ │
│  └───────────┬──────────┘      └────────────┬─────────────┘ │
│              │                              │               │
│              ▼                              ▼               │
│       Linux Drivers                    HAL / Drivers        │
│              │                              │               │
└──────────────┼──────────────────────────────┼───────────────┘
               │                              │
               ▼                              ▼
          Device Tree                    Sensor Interfaces
                                              │
                                ┌─────────────┼─────────────┐
                                ▼             ▼             ▼
                           Temperature    Pressure      Vibration
```

---

# Cortex-A7 Role

The Cortex-A7 subsystem runs Linux and performs high-level operations.

Responsibilities:

* Linux kernel
* Device Tree
* Sensor management
* Power management
* RPMsg endpoint
* Data processing
* Logging
* Communication
* System services
* Application execution
* Cloud/gateway communication

---

# Cortex-M4 Role

The Cortex-M4 is used for low-latency and low-power tasks.

Responsibilities:

* Sensor acquisition
* Sensor timing
* GPIO control
* Low-level processing
* Sensor event detection
* Power-aware operation
* RPMsg communication
* Wake-up/event handling

The basic philosophy is:

```text
Cortex-M4
   ↓
Low-power continuous monitoring

Cortex-A7
   ↓
High-level processing when required
```

---

# Sensor Architecture

The project supports three sensor categories:

```text
hardware/sensors/
│
├── pressure/
│
├── temperature/
│
└── vibration/
```

Sensor flow:

```text
Sensor
  │
  ▼
Physical Measurement
  │
  ▼
Sensor Interface
  │
  ├── I2C
  ├── SPI
  └── GPIO / Interrupt
  │
  ▼
Cortex-M4
  │
  ▼
Filtering / Validation
  │
  ▼
RPMsg
  │
  ▼
Linux
  │
  ▼
Sensor Manager
  │
  ▼
Sensor Monitor
```

---

# Temperature Sensor Flow

```text
Temperature
     │
     ▼
Temperature Sensor
     │
     ▼
I2C / SPI
     │
     ▼
Cortex-M4
     │
     ▼
Read Register
     │
     ▼
Convert Raw Data
     │
     ▼
Temperature Value
     │
     ▼
RPMsg
     │
     ▼
Linux
```

---

# Pressure Sensor Flow

```text
Pressure
   │
   ▼
Pressure Sensor
   │
   ▼
I2C / SPI
   │
   ▼
Cortex-M4
   │
   ▼
Raw Pressure Data
   │
   ▼
Calibration
   │
   ▼
Pressure Value
   │
   ▼
RPMsg
   │
   ▼
Linux
```

---

# Vibration Sensor Flow

```text
Mechanical Vibration
        │
        ▼
Vibration Sensor
        │
        ▼
Accelerometer / Vibration IC
        │
        ▼
SPI / I2C
        │
        ▼
Cortex-M4
        │
        ▼
Sampling
        │
        ▼
Filtering
        │
        ▼
RMS / Threshold
        │
        ▼
Event Detection
        │
        ▼
Wake Cortex-A7
```

---

# RPMsg Architecture

RPMsg is used for communication between the Cortex-A7 Linux subsystem and Cortex-M4 firmware.

```text
                 Cortex-A7
                    │
                    │
                 Linux
                    │
                    ▼
              RPMsg Driver
                    │
                    ▼
             VirtIO / RPMsg
                    │
              Shared Memory
                    │
                    ▼
              RPMsg Endpoint
                    │
                    ▼
                 Cortex-M4
                    │
                    ▼
              Sensor Manager
```

Example message:

```text
A7 → M4

{
    command: READ_SENSOR,
    sensor: TEMPERATURE
}
```

Response:

```text
M4 → A7

{
    sensor: TEMPERATURE,
    value: 31.5,
    unit: C,
    status: OK
}
```

---

# RPMsg Communication Flow

```text
Linux Application
       │
       ▼
sensor-manager
       │
       ▼
rpmsg-test / RPMsg API
       │
       ▼
Linux RPMsg Driver
       │
       ▼
Remote Processor Framework
       │
       ▼
Shared Memory / VirtIO
       │
       ▼
Cortex-M4 RPMsg
       │
       ▼
M4 Application
       │
       ▼
Sensor
```

---

# Power Architecture

```text
Energy Source
     │
     ▼
Energy Harvester
     │
     ▼
Energy Harvesting PMIC
     │
     ▼
Storage
     │
     ▼
Regulator
     │
     ▼
STM32MP157 Power Rails
     │
     ├── Cortex-A7
     ├── Cortex-M4
     ├── DDR
     ├── Sensors
     └── Communication
```

---

# Solar Energy Flow

```text
Sunlight
   │
   ▼
Solar Panel
   │
   ▼
PV Energy Harvester
   │
   ▼
Energy Storage
   │
   ▼
Power Management
   │
   ▼
STM32MP157
```

See:

```text
hardware/energy-harvesting/solar.md
```

---

# Thermal Energy Flow

```text
Temperature Difference
        │
        ▼
Thermoelectric Generator
        │
        ▼
Energy Harvester
        │
        ▼
Storage
        │
        ▼
Power Management
        │
        ▼
STM32MP157
```

See:

```text
hardware/energy-harvesting/thermal.md
```

---

# Kinetic Energy Flow

```text
Mechanical Motion
       │
       ▼
Piezoelectric /
Electromagnetic Generator
       │
       ▼
Rectifier
       │
       ▼
Energy Harvester
       │
       ▼
Storage
       │
       ▼
STM32MP157
```

See:

```text
hardware/energy-harvesting/kinetic.md
```

---

# Power-State Flow

The system uses multiple power states depending on the required response time and power budget.

```text
                   RUN
                    │
                    ▼
                  SLEEP
                    │
                    ▼
                  STOP
                    │
                    ▼
                LP-STOP
                    │
                    ▼
               LPLV-STOP
                    │
                    ▼
                STANDBY
```

Wake-up:

```text
STANDBY
   │
   ├── RTC
   │
   ├── GPIO
   │
   └── External event
   │
   ▼
WAKE
   │
   ▼
INITIALIZATION
   │
   ▼
SENSOR PROCESSING
```

---

# Low-Power Strategy

The project uses:

```text
1. Duty cycling
2. Sensor power gating
3. Cortex-A7 sleep
4. Cortex-M4 low-power processing
5. Peripheral shutdown
6. Dynamic wake-up
7. Event-driven processing
8. Data batching
9. Communication batching
10. Energy-aware operation
```

The goal is to minimize:

```text
Average Power
```

rather than simply minimizing instantaneous peak power.

---

# Energy Budget

The system should satisfy:

```text
Energy harvested
        >
Energy consumed
```

A simplified model:

```text
E_total =
    E_sleep
  + E_sensor
  + E_processing
  + E_communication
  + E_wakeup
```

Average power:

```text
P_average = E_total / Time
```

For an energy-harvesting system:

```text
P_harvested >= P_average
```

A practical design must also account for:

* Storage capacity
* Conversion losses
* Leakage
* Sensor startup energy
* Radio startup energy
* Peak current
* Environmental availability
* Temperature
* Harvester efficiency

---

# Wake-Up Architecture

```text
                    LOW POWER
                        │
           ┌────────────┼────────────┐
           │            │            │
           ▼            ▼            ▼
          RTC          GPIO       Sensor IRQ
           │            │            │
           └────────────┼────────────┘
                        ▼
                     WAKE-UP
                        │
                        ▼
                  Cortex-M4/A7
                        │
                        ▼
                  Process Event
```

---

# Sensor Event Wake-Up

```text
Vibration detected
       │
       ▼
Sensor interrupt
       │
       ▼
GPIO wake-up
       │
       ▼
Cortex-M4
       │
       ▼
Validate event
       │
       ▼
Significant?
     /     \
   No       Yes
   │         │
   ▼         ▼
 Sleep     Wake A7
             │
             ▼
          Linux
             │
             ▼
         Log / Send
```

---

# Linux Architecture

```text
┌────────────────────────────────────────────┐
│              User Applications             │
│                                            │
│ power-manager                              │
│ sensor-manager                             │
│ sensor-monitor                             │
│ rpmsg-test                                 │
└──────────────────┬─────────────────────────┘
                   │
┌──────────────────▼─────────────────────────┐
│                 Services                   │
│                                            │
│ power-service                              │
│ sensor-service                             │
└──────────────────┬─────────────────────────┘
                   │
┌──────────────────▼─────────────────────────┐
│              Linux Kernel                  │
│                                            │
│ Device Tree                                │
│ I2C / SPI / GPIO                           │
│ RemoteProc                                 │
│ RPMsg                                      │
│ Power Management                           │
│ RTC / Wake-up                              │
└──────────────────┬─────────────────────────┘
                   │
                   ▼
              STM32MP157 HW
```

---

# Linux Applications

```text
linux/apps/
│
├── power-manager/
│
├── rpmsg-test/
│
├── sensor-manager/
│
└── sensor-monitor/
```

### power-manager

Controls and monitors system power behavior.

### rpmsg-test

Validates Cortex-A7 ↔ Cortex-M4 communication.

### sensor-manager

Coordinates sensor acquisition.

### sensor-monitor

Displays and monitors sensor data.

---

# Linux Services

```text
linux/services/
│
├── power-service/
│
└── sensor-service/
```

Services are long-running background processes managed by Linux/systemd.

```text
systemd
  │
  ├── power-service
  │
  └── sensor-service
```

---

# Device Tree Flow

```text
Device Tree Source
        │
        ▼
stm32mp157-energy-sensor.dts
        │
        ├── GPIO
        ├── I2C
        ├── SPI
        ├── Sensors
        ├── RPMsg
        └── Power
        │
        ▼
Device Tree Compiler
        │
        ▼
DTB
        │
        ▼
Linux Kernel
        │
        ▼
Drivers
        │
        ▼
Hardware
```

Device Tree files:

```text
device-tree/
├── README.md
├── stm32mp157-energy-sensor.dts
├── stm32mp157-energy-sensor-overlay.dts
└── stm32mp157-energy-sensor-pinctrl.dtsi
```

---

# Cortex-M4 Firmware Flow

```text
Power ON
   │
   ▼
M4 Startup
   │
   ▼
HAL Initialization
   │
   ▼
Clock Initialization
   │
   ▼
GPIO Initialization
   │
   ▼
Sensor Initialization
   │
   ▼
RPMsg Initialization
   │
   ▼
Application Initialization
   │
   ▼
Main Loop
   │
   ├── Sensor Read
   ├── Event Detection
   ├── RPMsg
   ├── Power Control
   └── Low-Power Wait
```

---

# Cortex-M4 Directory

```text
cortex-m4/
├── README.md
├── Core/
│   ├── Inc/
│   │   ├── main.h
│   │   ├── app_sensor.h
│   │   ├── app_power.h
│   │   ├── app_rpmsg.h
│   │   ├── sensor_manager.h
│   │   ├── power_manager.h
│   │   └── system_config.h
│   │
│   └── Src/
│       ├── main.c
│       ├── app_power.c
│       ├── app_rpmsg.c
│       ├── app_sensor.c
│       ├── power_manager.c
│       ├── sensor_manager.c
│       └── system_config.c
│
├── Config/
│   ├── stm32mp157xx_hal_conf.h
│   └── stm32mp157xx_it.h
│
├── Drivers/
│   ├── BSP/
│   ├── CMSIS/
│   └── README.md
│
├── Middlewares/
│   └── OpenAMP/
│       └── README.md
│
├── linker/
│   └── STM32MP157_M4.ld
│
├── Makefile
├── CMakeLists.txt
└── README.md
```

---

# Yocto Architecture

```text
                        Yocto
                          │
                          ▼
                 meta-energy-sensor
                          │
          ┌───────────────┼────────────────┐
          │               │                │
          ▼               ▼                ▼
     recipes-apps    recipes-services   recipes-firmware
          │               │                │
          ▼               ▼                ▼
       Apps            Services           M4
          │               │                │
          └───────────────┼────────────────┘
                          │
                          ▼
                    recipes-bsp
                          │
                          ▼
                     Device Tree
                          │
                          ▼
                   recipes-kernel
                          │
                          ▼
                    Linux Kernel
                          │
                          ▼
                       BitBake
                          │
                          ▼
                   Bootable Image
```

---

# Yocto Layer

```text
yocto/
├── build.sh
├── clean.sh
├── deploy.sh
├── flash_sd.sh
├── setup.sh
├── README.md
│
└── meta-energy-sensor/
    │
    ├── conf/
    │   └── layer.conf
    │
    ├── recipes-apps/
    │   ├── energy-sensor.bb
    │   ├── files/
    │   │   ├── energy-sensor.c
    │   │   └── energy-sensor.service
    │   │
    │   ├── power-manager/
    │   │   ├── power-manager.bb
    │   │   └── files/
    │   │
    │   ├── rpmsg-test/
    │   │   ├── rpmsg-test.bb
    │   │   └── files/
    │   │
    │   ├── sensor-manager/
    │   │   ├── sensor-manager.bb
    │   │   └── files/
    │   │
    │   └── sensor-monitor/
    │       ├── sensor-monitor.bb
    │       └── files/
    │
    ├── recipes-bsp/
    │   └── device-tree/
    │
    ├── recipes-firmware/
    │   └── cortex-m4/
    │
    ├── recipes-kernel/
    │   └── linux/
    │       └── linux-stm32mp/
    │
    └── recipes-services/
        ├── power-service/
        └── sensor-service/
```

---

# Yocto Build Flow

```text
Ubuntu Host
     │
     ▼
Yocto Setup
     │
     ▼
Initialize Build Environment
     │
     ▼
Add meta-energy-sensor
     │
     ▼
Configure MACHINE
     │
     ▼
Configure DISTRO
     │
     ▼
BitBake
     │
     ├───────────────┐
     ▼               ▼
Linux Kernel       Cortex-M4
     │               │
     ▼               ▼
Device Tree        Firmware
     │               │
     └───────┬───────┘
             ▼
        Root Filesystem
             │
             ▼
        Boot Components
             │
             ▼
        WIC / SD Image
             │
             ▼
       STM32MP157-DK
```

---

# Complete Boot Flow

```text
Power ON
   │
   ▼
Boot ROM
   │
   ▼
TF-A / First Stage Boot
   │
   ▼
DDR Initialization
   │
   ▼
Trusted Firmware
   │
   ▼
U-Boot
   │
   ▼
Read Boot Configuration
   │
   ▼
Load Kernel
   │
   ▼
Load Device Tree
   │
   ▼
Load Firmware / Boot Components
   │
   ▼
Start Linux Kernel
   │
   ▼
Kernel Initialization
   │
   ▼
Device Tree Parsing
   │
   ▼
Driver Initialization
   │
   ├── GPIO
   ├── I2C
   ├── SPI
   ├── RTC
   ├── RemoteProc
   └── RPMsg
   │
   ▼
Root Filesystem
   │
   ▼
systemd
   │
   ├── power-service
   └── sensor-service
   │
   ▼
User Applications
```

---

# Complete Sensor Data Flow

```text
Physical World
      │
      ▼
Sensor
      │
      ▼
I2C / SPI / GPIO
      │
      ▼
Cortex-M4 Driver
      │
      ▼
Sensor Manager
      │
      ▼
Filtering / Calibration
      │
      ▼
Event Detection
      │
      ▼
RPMsg
      │
      ▼
Linux RPMsg Driver
      │
      ▼
Sensor Service
      │
      ▼
Sensor Manager
      │
      ▼
Sensor Monitor
      │
      ▼
Log / Database / Network
```

---

# Complete Power Management Flow

```text
Energy Available
       │
       ▼
Power Management
       │
       ▼
Check Energy Budget
       │
       ├───────────────┐
       │               │
       ▼               ▼
Enough Energy      Low Energy
       │               │
       ▼               ▼
Normal Operation   Low-Power Mode
       │               │
       ▼               ▼
Sensor Read        M4 Monitoring
       │               │
       ▼               ▼
Processing         Event Detection
       │               │
       └───────┬───────┘
               ▼
          Communication
               │
               ▼
            Sleep
```

---

# Complete Low-Power Flow

```text
Application Running
        │
        ▼
Finish Current Work
        │
        ▼
Stop Sensors
        │
        ▼
Stop Unused Peripherals
        │
        ▼
Flush Important Data
        │
        ▼
Configure Wake Source
        │
        ▼
Suspend Cortex-A7
        │
        ▼
Low-Power State
        │
        ▼
RTC / GPIO / Sensor IRQ
        │
        ▼
Wake-up
        │
        ▼
Restore State
        │
        ▼
Restart Required Peripherals
        │
        ▼
Read Sensor
        │
        ▼
Process Event
        │
        ▼
Return to Low Power
```

---

# Test Architecture

```text
tests/
│
├── boot/
│
├── energy/
│
├── low-power/
│
├── rpmsg/
│
├── sensor/
│
└── wakeup/
```

Test flow:

```text
Build
  │
  ▼
Deploy
  │
  ▼
Boot Test
  │
  ▼
Sensor Test
  │
  ▼
RPMsg Test
  │
  ▼
Energy Test
  │
  ▼
Low-Power Test
  │
  ▼
Wake-up Test
  │
  ▼
Collect Logs
  │
  ▼
Test Report
```

---

# Test Categories

## Boot

Validates:

* Boot sequence
* Linux startup
* Device Tree
* Kernel
* Remote processor support

## Energy

Validates:

* Power supply
* Voltage
* Current
* Energy availability
* Energy budget

## Low Power

Validates:

* Suspend
* Stop
* Low-power modes
* Power-state transitions

## RPMsg

Validates:

* RemoteProc
* RPMsg
* Cortex-A7 ↔ Cortex-M4 communication

## Sensor

Validates:

* Temperature
* Pressure
* Vibration
* Sensor interfaces
* Sensor data path

## Wakeup

Validates:

* RTC wake-up
* GPIO wake-up
* Sensor interrupt
* Resume

---

# Developer Tools

```text
tools/
│
├── log-parser/
│
├── power-measurement/
│
└── serial-monitor/
```

The tools run primarily on the development host.

```text
STM32MP157
    │
    ├── UART ───────────────► serial-monitor
    │
    ├── Logs ───────────────► log-parser
    │
    └── Current Measurement ► power-measurement
```

---

# Project Automation

```text
scripts/
│
├── build_all.sh
├── clean_all.sh
├── collect_logs.sh
├── deploy_all.sh
└── run_tests.sh
```

Complete developer workflow:

```text
./scripts/build_all.sh
        │
        ▼
./scripts/deploy_all.sh
        │
        ▼
STM32MP157-DK
        │
        ▼
./scripts/run_tests.sh
        │
        ▼
./scripts/collect_logs.sh
```

---

# Hardware Documentation

```text
hardware/
│
├── energy-harvesting/
│   ├── kinetic.md
│   ├── solar.md
│   └── thermal.md
│
├── sensors/
│   ├── pressure/
│   ├── temperature/
│   └── vibration/
│
└── stm32mp157-dk/
    ├── peripherals.md
    ├── pinout.md
    └── README.md
```

---

# Pressure Sensor Documentation

```text
pressure/
├── README.md
├── interface.md
├── hardware.md
└── register_map.md
```

Documents:

* Sensor selection
* Electrical interface
* I2C/SPI communication
* Power requirements
* Register configuration
* Calibration
* Data conversion

---

# Temperature Sensor Documentation

```text
temperature/
├── README.md
├── interface.md
├── hardware.md
└── register_map.md
```

---

# Vibration Sensor Documentation

```text
vibration/
├── README.md
├── interface.md
├── hardware.md
└── register_map.md
```

---

# Hardware Pin and Peripheral Flow

```text
STM32MP157
     │
     ├── GPIO
     │
     ├── I2C
     │
     ├── SPI
     │
     ├── UART
     │
     ├── RTC
     │
     ├── PWM
     │
     └── Interrupt
            │
            ▼
         Sensors
```

---

# GPIO Flow

```text
Device Tree
    │
    ▼
GPIO Controller
    │
    ▼
Linux / Cortex-M4
    │
    ▼
GPIO Configuration
    │
    ▼
Input / Output
    │
    ▼
Sensor / Wake-up Signal
```

---

# I2C Flow

```text
Application
    │
    ▼
Sensor Manager
    │
    ▼
I2C Driver
    │
    ▼
I2C Controller
    │
    ▼
SDA / SCL
    │
    ▼
Sensor
```

---

# SPI Flow

```text
Application
    │
    ▼
Sensor Manager
    │
    ▼
SPI Driver
    │
    ▼
SPI Controller
    │
    ▼
SCLK / MOSI / MISO / CS
    │
    ▼
Sensor
```

---

# Interrupt Flow

```text
Sensor Event
     │
     ▼
GPIO / IRQ
     │
     ▼
Interrupt Controller
     │
     ▼
ISR
     │
     ▼
Event Handler
     │
     ▼
Sensor Manager
     │
     ▼
RPMsg / Wake-up
```

---

# Project Directory

```text
STM32MP157_Discovery/
│
├── CONTRIBUTING.md
├── CHANGELOG.md
├── .gitignore
├── README.md
│
├── cortex-m4/
│
├── device-tree/
│
├── hardware/
│
├── linux/
│
├── scripts/
│
├── tests/
│
├── tools/
│
└── yocto/
```

---

# Complete Repository Architecture

```text
                         STM32MP157 DISCOVERY
                                  │
          ┌───────────────────────┼────────────────────────┐
          │                       │                        │
          ▼                       ▼                        ▼
      Hardware                 Firmware                  Linux
          │                       │                        │
          │                   Cortex-M4              Cortex-A7
          │                       │                        │
          │                       │                        │
          └───────────────────────┼────────────────────────┘
                                  │
                                  ▼
                               RPMsg
                                  │
                                  ▼
                           Sensor / Power
                              Management
                                  │
                                  ▼
                            Low-Power Logic
                                  │
                                  ▼
                          Energy Management
                                  │
                                  ▼
                         Energy Harvesting
```

---

# Development Workflow

```text
1. Design hardware
       ↓
2. Define Device Tree
       ↓
3. Develop Cortex-M4 firmware
       ↓
4. Develop Linux applications
       ↓
5. Develop Linux services
       ↓
6. Integrate RPMsg
       ↓
7. Integrate Yocto
       ↓
8. Build image
       ↓
9. Flash SD card
       ↓
10. Boot board
       ↓
11. Run sensor tests
       ↓
12. Run RPMsg tests
       ↓
13. Run low-power tests
       ↓
14. Measure power
       ↓
15. Analyze logs
       ↓
16. Optimize
       ↓
17. Repeat
```

---

# Debugging Flow

```text
Problem
   │
   ▼
Serial Monitor
   │
   ▼
Kernel Logs
   │
   ▼
dmesg
   │
   ├── Device Tree?
   │
   ├── Driver?
   │
   ├── RemoteProc?
   │
   ├── RPMsg?
   │
   ├── Sensor?
   │
   └── Power?
   │
   ▼
Log Parser
   │
   ▼
Root Cause
   │
   ▼
Fix
   │
   ▼
Rebuild
```

---

# Power Optimization Workflow

```text
Measure
   │
   ▼
Find High-Consumption Block
   │
   ▼
Classify
   │
   ├── CPU
   ├── DDR
   ├── Sensor
   ├── Peripheral
   ├── Radio
   └── Leakage
   │
   ▼
Optimize
   │
   ├── Duty Cycle
   ├── Power Gate
   ├── Clock Gate
   ├── Suspend
   └── Reduce Active Time
   │
   ▼
Measure Again
   │
   ▼
Compare
   │
   ▼
Repeat
```

---

# Energy-Harvesting Optimization

```text
Measure Harvested Energy
          │
          ▼
Calculate Available Energy
          │
          ▼
Calculate System Consumption
          │
          ▼
       Compare
        /     \
       /       \
Enough         Not Enough
Energy         Energy
  │               │
  ▼               ▼
Normal         Increase
Operation      Sleep Time
                  │
                  ▼
             Reduce Sensor
             Activity
                  │
                  ▼
             Reduce Radio
             Activity
                  │
                  ▼
             Optimize CPU
```

---

# Real Product Architecture

The Discovery Kit is used for development.

A production design would look more like:

```text
             Solar / Thermal / Kinetic
                       │
                       ▼
                Energy Harvester
                       │
                       ▼
                 Storage Element
                       │
                       ▼
              Ultra-Low-Power PMIC
                       │
             ┌─────────┴─────────┐
             │                   │
             ▼                   ▼
        STM32MP157           Sensors
             │
       ┌─────┴─────┐
       │           │
    Cortex-A7   Cortex-M4
       │           │
       └─────┬─────┘
             ▼
           RPMsg
             │
             ▼
        Communication
             │
             ▼
          Gateway
```

The production PCB should minimize:

* PMIC leakage
* Regulator quiescent current
* LED consumption
* Debug interface consumption
* DDR consumption
* Sensor standby current
* Pull-up leakage
* GPIO leakage
* Peripheral leakage

---

# Current Measurement Strategy

Measure different system states independently:

```text
1. Boot
2. Linux idle
3. Sensor active
4. Cortex-M4 active
5. RPMsg active
6. Communication active
7. Suspend
8. Stop
9. Standby
10. Wake-up
```

Example table:

| State         | Voltage | Current | Power |
| ------------- | ------: | ------: | ----: |
| Boot          |     TBD |     TBD |   TBD |
| Linux Idle    |     TBD |     TBD |   TBD |
| Sensor Active |     TBD |     TBD |   TBD |
| RPMsg         |     TBD |     TBD |   TBD |
| Suspend       |     TBD |     TBD |   TBD |
| Standby       |     TBD |     TBD |   TBD |

Replace `TBD` with actual measurements from your hardware.

---

# Important Power Target

The project should distinguish between:

```text
SoC-level low-power specification
```

and:

```text
Complete-board/system power consumption
```

The Discovery Kit contains many components that are not required in a final ultra-low-power product.

Therefore:

```text
Discovery Kit
     │
     └── Development / Demonstration

Custom PCB
     │
     └── Production Ultra-Low-Power Design
```

---

# Getting Started

Clone the repository:

```bash
git clone <YOUR_GITHUB_REPOSITORY>
cd STM32MP157_Discovery
```

Initialize the Cortex-M4 build:

```bash
cd cortex-m4
```

Build the Yocto environment:

```bash
cd ../yocto
./setup.sh
```

Build the image:

```bash
./build.sh
```

Deploy:

```bash
./deploy.sh
```

Flash the SD card:

```bash
sudo ./flash_sd.sh <image.wic>
```

Boot the Discovery Kit.

---

# Testing

Run the complete test suite:

```bash
./scripts/run_tests.sh
```

Or run individual tests:

```bash
./tests/boot/test_boot.sh

./tests/energy/test_energy.sh

./tests/low-power/test_low_power.sh

./tests/rpmsg/test_rpmsg.sh

./tests/sensor/test_sensor.sh

./tests/wakeup/test_wakeup.sh
```

---

# Serial Debugging

Find the serial device:

```bash
ls /dev/ttyUSB*
```

Run:

```bash
python3 tools/serial-monitor/serial_monitor.py \
    /dev/ttyUSB0 \
    115200
```

---

# Log Collection

On the target:

```bash
./scripts/collect_logs.sh
```

Analyze logs:

```bash
python3 tools/log-parser/log_parser.py sensor.log
```

---

# Power Calculation

Example:

```bash
python3 tools/power-measurement/power_measurement.py \
    3.3 \
    0.002
```

Power is calculated using:

```text
P = V × I
```

Energy:

```text
E = P × t
```

---

# Software Stack

```text
┌─────────────────────────────┐
│ Applications                │
├─────────────────────────────┤
│ Linux Services              │
├─────────────────────────────┤
│ Linux Kernel                │
├─────────────────────────────┤
│ Device Tree                 │
├─────────────────────────────┤
│ STM32MP1 Drivers            │
├─────────────────────────────┤
│ Cortex-A7 / Cortex-M4       │
├─────────────────────────────┤
│ STM32MP157 Hardware         │
└─────────────────────────────┘
```

---

# Technologies Used

* STM32MP157
* Cortex-A7
* Cortex-M4
* STM32 HAL
* OpenAMP
* RPMsg
* Linux
* Device Tree
* Yocto/OpenEmbedded
* systemd
* I2C
* SPI
* GPIO
* UART
* RTC
* RemoteProc
* Power Management
* Solar Energy Harvesting
* Thermal Energy Harvesting
* Kinetic Energy Harvesting
* C
* Bash
* Python

---

# Project Goals

The project demonstrates:

* Embedded Linux development
* Cortex-M4 firmware development
* Linux/M4 communication
* Sensor integration
* Device Tree development
* Yocto BSP development
* Power management
* Low-power architecture
* Energy harvesting
* Automated testing
* Hardware/software integration
* Embedded debugging
* Power measurement

---

# Future Improvements

```text
Phase 1
├── Basic sensors
├── M4 firmware
├── Linux application
└── RPMsg

Phase 2
├── Low-power states
├── Wake-up
├── Power measurement
└── Energy budgeting

Phase 3
├── Solar harvesting
├── Thermal harvesting
├── Kinetic harvesting
└── Supercapacitor storage

Phase 4
├── Industrial communication
├── Remote monitoring
├── Data logging
└── Cloud integration

Phase 5
├── Custom PCB
├── Power optimization
├── Leakage optimization
└── Production design
```

---

# Repository Status

| Component                       | Status    |
| ------------------------------- | --------- |
| STM32MP157 platform             | 🟢        |
| Cortex-M4 firmware              | 🟢        |
| Linux applications              | 🟢        |
| Linux services                  | 🟢        |
| RPMsg architecture              | 🟢        |
| Device Tree                     | 🟢        |
| Yocto layer                     | 🟢        |
| Sensor architecture             | 🟢        |
| Energy harvesting documentation | 🟢        |
| Low-power architecture          | 🟢        |
| Automated tests                 | 🟢        |
| Power measurement               | 🟢        |
| Production hardware             | 🔵 Future |

---

# Contributing

Please read:

```text
CONTRIBUTING.md
```

before submitting changes.

---

# Changelog

Project changes are documented in:

```text
CHANGELOG.md
```

---

# License

This project currently uses:

```text
CLOSED
```

for the project-specific source components.

Review the licenses of all STMicroelectronics, Linux, Yocto, OpenAMP, CMSIS, and other third-party components separately before redistribution.

---

# Disclaimer

This project is intended for engineering development, experimentation, education, and demonstration.

The STM32MP157 Discovery Kit is a development platform and should not be interpreted as a production ultra-low-power energy-harvesting sensor node.

Actual system-level power consumption depends on:

* Hardware configuration
* PMIC
* DDR
* Sensors
* Peripheral configuration
* Clock configuration
* Software
* Leakage
* Board components
* Measurement conditions
* Energy-harvesting source

A production sub-microamp design requires dedicated hardware and detailed power-budget validation.

---

# Project Flow — One Page

```text
                    ENERGY SOURCE
                         │
            ┌────────────┼────────────┐
            │            │            │
          SOLAR       THERMAL       KINETIC
            │            │            │
            └────────────┼────────────┘
                         ▼
                 ENERGY HARVESTER
                         │
                         ▼
                    POWER STORAGE
                         │
                         ▼
                    POWER MANAGER
                         │
                         ▼
                  ┌──────────────┐
                  │ STM32MP157   │
                  └──────┬───────┘
                         │
              ┌──────────┴──────────┐
              ▼                     ▼
          Cortex-A7             Cortex-M4
              │                     │
            Linux                Sensors
              │                     │
        ┌─────┼─────┐               │
        │     │     │               │
        ▼     ▼     ▼               ▼
     Power  Sensor RPMsg        Processing
     App    App                  │
        │     │     │             │
        └─────┴─────┼─────────────┘
                    ▼
                  RPMsg
                    │
                    ▼
              Data Processing
                    │
                    ▼
               Event Detect
                    │
             ┌──────┴──────┐
             ▼             ▼
           Event         No Event
             │             │
             ▼             ▼
         Wake A7          Sleep
             │             │
             ▼             │
         Communicate       │
             │             │
             └──────┬──────┘
                    ▼
                LOW POWER
                    │
              RTC / GPIO /
              SENSOR IRQ
                    │
                    ▼
                   WAKE
                    │
                    └──────────────► Repeat
```

---

# Final Architecture

```text
                         ┌─────────────────────┐
                         │  Solar / Thermal /  │
                         │      Kinetic        │
                         └──────────┬──────────┘
                                    │
                                    ▼
                         ┌─────────────────────┐
                         │ Energy Harvesting   │
                         │       PMIC          │
                         └──────────┬──────────┘
                                    │
                                    ▼
                         ┌─────────────────────┐
                         │ Storage / Regulation│
                         └──────────┬──────────┘
                                    │
                                    ▼
              ┌─────────────────────────────────────────┐
              │              STM32MP157                 │
              │                                         │
              │  ┌────────────────┐ ┌────────────────┐ │
              │  │   Cortex-A7    │ │   Cortex-M4    │ │
              │  │                │ │                │ │
              │  │ Linux          │ │ Sensors        │ │
              │  │ Applications   │ │ Control        │ │
              │  │ Services       │ │ Processing     │ │
              │  │ Power Mgmt     │ │ Low Power      │ │
              │  └───────┬────────┘ └───────┬────────┘ │
              │          │                  │          │
              │          └────── RPMsg ─────┘          │
              └────────────────┬────────────────────────┘
                               │
                               ▼
                      ┌─────────────────┐
                      │     Sensors     │
                      │                 │
                      │ Temperature     │
                      │ Pressure        │
                      │ Vibration       │
                      └────────┬────────┘
                               │
                               ▼
                         Data / Events
                               │
                               ▼
                       Communication
                               │
                               ▼
                         Gateway / Cloud
```

---

## Project Objective

The final objective is to develop an **energy-aware STM32MP157 embedded platform** capable of:

```text
Harvest Energy
      ↓
Measure Environment
      ↓
Process Data
      ↓
Detect Events
      ↓
Communicate Only When Required
      ↓
Enter Low Power
      ↓
Wake on Event
      ↓
Repeat
```

This architecture provides the foundation for developing a production-oriented **solar, thermal, or kinetic energy-harvesting industrial sensor node** using the STM32MP157.

```
```
