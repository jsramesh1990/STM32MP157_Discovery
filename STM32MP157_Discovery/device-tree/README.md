# STM32MP157 Energy Sensor Device Tree

This directory contains the Device Tree configuration for the
STM32MP157 Energy-Aware Industrial Sensor Node.

## Files

```text
device-tree/
├── README.md
├── stm32mp157-energy-sensor.dts
├── stm32mp157-energy-sensor-overlay.dts
└── stm32mp157-energy-sensor-pinctrl.dtsi
````

## Architecture

```text
                    STM32MP157
                         │
             ┌───────────┴───────────┐
             │                       │
        Cortex-A7                Cortex-M4
             │                       │
           Linux                 Firmware
             │                       │
       Device Tree              Sensor
             │                       │
             └──────────┬────────────┘
                        │
                   OpenAMP/RPMsg
```

## Device Tree Responsibilities

The Device Tree describes:

* Cortex-M4 remote processor
* Reserved M4 memory
* RPMsg/OpenAMP memory
* Sensor buses
* GPIOs
* GPIO wake-up
* I2C
* SPI
* UART
* RTC
* LEDs
* Power control
* Sensor interrupt
* Pin multiplexing

## Boot Flow

```text
BootROM
   ↓
TF-A
   ↓
U-Boot
   ↓
Linux Kernel
   ↓
Device Tree
   ↓
Remoteproc
   ↓
Cortex-M4 Firmware
   ↓
OpenAMP/RPMsg
```

## Remoteproc Flow

```text
Linux
 │
 ▼
stm32 remoteproc driver
 │
 ▼
Reserved M4 memory
 │
 ▼
Load Cortex-M4 firmware
 │
 ▼
Start Cortex-M4
 │
 ▼
RPMsg channel
```

## Low-Power Flow

```text
Sensor
   │
   ▼
GPIO Interrupt
   │
   ▼
Cortex-M4
   │
   ▼
Process Event
   │
   ▼
Wake Cortex-A7
   │
   ▼
Linux
```

## Pin Control

`stm32mp157-energy-sensor-pinctrl.dtsi` contains pin multiplexing and
electrical configuration used by the sensor peripherals.

Typical interfaces:

```text
I2C
SPI
UART
GPIO
RTC
Sensor interrupt
```

## Overlay

`stm32mp157-energy-sensor-overlay.dts` is intended for optional
hardware-specific configuration without modifying the base board Device
Tree.

Use the overlay for features such as:

```text
Optional sensor
Optional energy monitor
Optional wake GPIO
Optional communication interface
```

## Important

The exact GPIO numbers, peripheral instances, clocks, regulators,
reserved-memory addresses and remoteproc configuration must match the
actual STM32MP157 Discovery Kit hardware and the corresponding STM32MP1 BSP.

Do not use placeholder addresses or GPIOs in a production configuration.

````

