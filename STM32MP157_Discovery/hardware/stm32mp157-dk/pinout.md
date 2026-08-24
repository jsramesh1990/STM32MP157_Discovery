# STM32MP157 Discovery Kit Pinout

## 1. Overview

This document defines the GPIO and peripheral pin usage for the
STM32MP157 Discovery Kit project.

The exact pin assignments must be verified against the official
Discovery Kit schematic and STM32MP157 datasheet/reference manual.

## 2. Project Pin Categories

```text
STM32MP157
    │
    ├── I2C
    │    ├── Temperature
    │    └── Pressure
    │
    ├── SPI
    │    └── Vibration
    │
    ├── GPIO
    │    ├── Sensor Interrupts
    │    └── Power Enable
    │
    ├── UART
    │    └── Debug / Console
    │
    ├── PWM
    │    └── Application dependent
    │
    └── Other Peripherals
````

## 3. Sensor Pin Assignment

| Function          | Interface | STM32MP157 Pin | Sensor      |
| ----------------- | --------- | -------------- | ----------- |
| Temperature SDA   | I2C       | TBD            | Temperature |
| Temperature SCL   | I2C       | TBD            | Temperature |
| Temperature INT   | GPIO      | TBD            | Temperature |
| Temperature Power | GPIO      | TBD            | Temperature |
| Pressure SDA      | I2C       | TBD            | Pressure    |
| Pressure SCL      | I2C       | TBD            | Pressure    |
| Pressure INT      | GPIO      | TBD            | Pressure    |
| Pressure Power    | GPIO      | TBD            | Pressure    |
| Vibration SCLK    | SPI       | TBD            | Vibration   |
| Vibration MOSI    | SPI       | TBD            | Vibration   |
| Vibration MISO    | SPI       | TBD            | Vibration   |
| Vibration CS      | GPIO/SPI  | TBD            | Vibration   |
| Vibration INT     | GPIO      | TBD            | Vibration   |
| Vibration Power   | GPIO      | TBD            | Vibration   |

**TBD pins must be replaced with the actual board pin assignments
before hardware implementation.**

## 4. Debug UART

The debug UART can be used for:

```text
Boot messages
Kernel messages
Cortex-M4 logs
Sensor debugging
Power-management debugging
```

Conceptual connection:

```text
STM32MP157 UART
      │
      ▼
Debug Connector
      │
      ▼
Host PC
```

## 5. I2C

The I2C bus can connect low-speed sensors.

```text
                 I2C Bus
                    │
          ┌─────────┼─────────┐
          │         │         │
    Temperature  Pressure   Other
       Sensor     Sensor    Devices
```

## 6. SPI

SPI is intended for high-speed sensor communication.

```text
STM32MP157 SPI
      │
 ┌────┼────┬────┐
 │    │    │    │
SCLK MOSI MISO  CS
 │    │    │    │
 └────┴────┴────┘
          │
          ▼
   Vibration Sensor
```

## 7. Interrupt GPIOs

Sensor interrupts should be connected to GPIOs capable of generating
the required interrupt events.

```text
Temperature INT ──► GPIO
Pressure INT ─────► GPIO
Vibration INT ────► GPIO
```

## 8. Power Enable GPIOs

If external load switches are used:

```text
M4 GPIO
   │
   ├── Temperature Power
   ├── Pressure Power
   └── Vibration Power
```

## 9. Device Tree

Pin configuration must also be represented in the Device Tree.

Example structure:

```text
device-tree/
├── stm32mp157-energy-sensor.dts
├── stm32mp157-energy-sensor-overlay.dts
└── stm32mp157-energy-sensor-pinctrl.dtsi
```

The Device Tree should define:

* Pin multiplexing
* GPIOs
* I2C controllers
* SPI controllers
* Interrupts
* Sensor nodes
* Power supplies
* Regulators

## 10. Pin Configuration Verification

Before using a pin, verify:

1. STM32MP157 alternate function
2. Discovery Kit schematic
3. Pin multiplexing
4. GPIO availability
5. Electrical voltage
6. Pull-up/pull-down requirements
7. Device Tree configuration
8. Conflicts with existing peripherals

