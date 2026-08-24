# STM32MP157 Discovery Kit Peripherals

## 1. Overview

The STM32MP157 Discovery Kit provides multiple peripherals that can
be used by the energy-aware sensor project.

The peripherals are divided between:

- Processing
- Communication
- Storage
- Sensors
- Debug
- Display
- Audio
- Networking
- Power management

## 2. Peripheral Architecture

```text
                         STM32MP157
                              │
        ┌─────────────────────┼─────────────────────┐
        │                     │                     │
     Cortex-A7            Cortex-M4             System
        │                     │                     │
     Linux              Real-time Control          │
        │                     │                     │
   ┌────┼─────┐         ┌─────┼─────┐              │
   │    │     │         │     │     │              │
 USB  Ethernet I2C     SPI   GPIO  UART           DDR
             │         │
             ▼         ▼
          Sensors   Vibration
````

## 3. GPIO

GPIO is used for:

* Sensor interrupts
* Sensor power control
* Reset signals
* Status LEDs
* External events
* Wake-up signals

Example:

```text
Sensor INT
    │
    ▼
GPIO
    │
    ▼
Cortex-M4
```

## 4. I2C

I2C is suitable for:

* Temperature sensors
* Pressure sensors
* PMICs
* EEPROMs
* Low-speed peripherals

Typical architecture:

```text
I2C Controller
      │
      ├── Temperature Sensor
      ├── Pressure Sensor
      └── Other Devices
```

## 5. SPI

SPI is suitable for:

* Vibration sensors
* High-speed ADCs
* Flash devices
* High-rate data acquisition

```text
SPI Controller
      │
      └──── Vibration Sensor
```

## 6. UART

UART can be used for:

* Debug console
* Boot messages
* Firmware debugging
* External serial communication

```text
STM32MP157
    │
   UART
    │
    ▼
 Debug Console
    │
    ▼
 Host PC
```

## 7. PWM

PWM can be used for:

* Motor control
* Fan control
* LED control
* Power control
* Application-specific actuators

```text
STM32MP157
     │
    PWM
     │
     ▼
   Driver
     │
     ▼
  Actuator
```

## 8. ADC

ADC can be used for monitoring analog signals such as:

* Supply voltage
* Energy-harvesting voltage
* Current-sense signals
* Analog sensors

Example:

```text
Energy Source
     │
     ▼
Voltage Divider
     │
     ▼
ADC
     │
     ▼
Cortex-M4
     │
     ▼
Energy Monitoring
```

## 9. Timers

Timers can be used for:

* Sensor sampling
* Periodic wake-up
* Time measurement
* PWM
* Scheduling
* Timeout handling

Example:

```text
Timer
  │
  ▼
Periodic Event
  │
  ▼
Wake Cortex-M4
  │
  ▼
Read Sensor
```

## 10. RTC

The RTC is important for low-power operation.

```text
RTC
 │
 ▼
Wake-up Event
 │
 ▼
Cortex-M4 / System
 │
 ▼
Sensor Measurement
```

It can provide scheduled wake-up without keeping the main processor
fully active.

## 11. Ethernet

Ethernet can be used by Linux for:

* Remote monitoring
* Data logging
* Network communication
* Sensor gateway operation
* Development/debugging

```text
Sensors
   │
   ▼
Cortex-M4
   │
  RPMsg
   │
   ▼
Cortex-A7
   │
 Linux
   │
Ethernet
   │
   ▼
Network
```

## 12. USB

USB can be used for:

* Development
* Debugging
* Data transfer
* External peripherals

USB should normally be disabled or placed into an appropriate
low-power state when not required by the application.

## 13. Storage

Storage can be used for:

* Sensor logs
* Configuration
* Firmware
* Calibration data
* Event history

The storage interface and device depend on the Discovery Kit hardware
configuration.

## 14. Audio

Audio peripherals are available on the Discovery Kit platform and can
be used for other applications.

For the energy-aware sensor project, unused audio blocks should not be
enabled unnecessarily because unnecessary peripherals increase power
consumption.

## 15. Display

Display interfaces can be used for:

* Local sensor visualization
* Debugging
* System status
* Graphs
* Alarms

For a low-power deployment, display hardware would normally be disabled
when not required.

## 16. Debug

Debug interfaces are required during development.

Typical functions include:

```text
Firmware Download
       │
       ▼
Debug
       │
       ▼
Breakpoints
       │
       ▼
Register Inspection
       │
       ▼
Performance Analysis
```

## 17. OpenAMP / RPMsg

The Cortex-M4 and Cortex-A7 communicate through OpenAMP/RPMsg.

```text
                 Cortex-A7
                    │
                  Linux
                    │
                  RPMsg
                    │
                    ▼
                 Cortex-M4
                    │
             Sensor Manager
                    │
                    ▼
                 Sensors
```

Example message:

```text
M4 → A7

TEMPERATURE = 32.5 C
VIBRATION_RMS = 0.42 g
PRESSURE = 101.2 kPa
STATUS = NORMAL
```

## 18. Power Management

Power-related peripherals and controls are important for the
energy-harvesting design.

```text
Energy Source
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

## 19. Peripheral Usage Summary

| Peripheral | Project Usage            |
| ---------- | ------------------------ |
| GPIO       | Interrupt / Power Enable |
| I2C        | Temperature / Pressure   |
| SPI        | Vibration                |
| UART       | Debug                    |
| PWM        | Optional                 |
| ADC        | Energy Monitoring        |
| Timer      | Sampling / Scheduling    |
| RTC        | Wake-up                  |
| Ethernet   | Network                  |
| USB        | Development              |
| Storage    | Sensor Logs              |
| RPMsg      | A7 ↔ M4 Communication    |
| Debug      | Development              |

## 20. Low-Power Rule

Every peripheral should have an explicit power-management policy.

```text
Peripheral Required?
       │
   ┌───┴────┐
   │        │
  YES       NO
   │        │
   ▼        ▼
Enable    Disable
   │        │
   ▼        ▼
Use      Save Power
```

The goal is to keep only the minimum required hardware active during
each operating state.

