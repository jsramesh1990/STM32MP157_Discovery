# STM32MP157 Discovery Kit Hardware

## 1. Overview

The STM32MP157 Discovery Kit is the development platform used for
developing and testing the energy-aware industrial sensor project.

The platform is based on the STM32MP157 microprocessor and provides
Cortex-A7 and Cortex-M4 processing capabilities.

## 2. Project Architecture

```text
                    STM32MP157 Discovery Kit
                              │
                 ┌────────────┴────────────┐
                 │                         │
             Cortex-A7                 Cortex-M4
                 │                         │
               Linux                 Sensor Control
                 │                         │
          High-level Apps          Low-power Processing
                 │                         │
                 └────────────┬────────────┘
                              │
                       Sensor Interfaces
                              │
              ┌───────────────┼───────────────┐
              │               │               │
          Temperature       Pressure       Vibration
              │               │               │
              └───────────────┴───────────────┘
                              │
                         Energy System
                              │
                    Solar / Thermal / Kinetic
````

## 3. Main Components

The Discovery Kit provides access to:

* STM32MP157 MPU
* Cortex-A7 processing
* Cortex-M4 processing
* DDR memory
* Storage interfaces
* Ethernet
* USB
* Display interfaces
* Camera interfaces
* Audio interfaces
* GPIO
* I2C
* SPI
* UART
* ADC-related interfaces
* PWM
* Timers
* Debug interfaces

## 4. Cortex-A7

The Cortex-A7 subsystem runs Linux.

Main responsibilities:

* Linux operating system
* Application software
* Data logging
* Network communication
* User interface
* Cloud communication
* High-level analytics
* Configuration

## 5. Cortex-M4

The Cortex-M4 is used for real-time and low-power tasks.

Main responsibilities:

* Sensor acquisition
* Sensor control
* Low-level processing
* Interrupt handling
* Threshold detection
* Power management
* Low-power operation
* Communication with Cortex-A7

## 6. Sensor Architecture

```text
Temperature ──┐
              │
Pressure ─────┼──► Cortex-M4 ──► RPMsg ──► Cortex-A7/Linux
              │
Vibration ────┘
```

## 7. Energy-Harvesting Architecture

```text
Solar
  │
Thermal ─────► Energy Harvesting PMIC
  │                    │
Kinetic                ▼
                  Energy Storage
                       │
                       ▼
                  Power Management
                       │
                       ▼
                 STM32MP157
```

## 8. Low-Power Concept

The Discovery Kit is used to demonstrate low-power techniques.

```text
             RUN
              │
              ▼
        Sensor Acquisition
              │
              ▼
         Data Processing
              │
              ▼
       Event / Threshold
              │
              ▼
         Communication
              │
              ▼
         Low-Power Mode
              │
              ▼
           Wake-up
              │
              └──────────► RUN
```

## 9. Important Note

The Discovery Kit is a development platform and is not itself a
sub-1 µA production sensor node.

The final energy-harvesting product should use a custom PCB designed for:

* Low leakage
* Low quiescent current
* Power gating
* Energy harvesting
* Sensor power control
* Optimized regulators
* Minimal unused circuitry

