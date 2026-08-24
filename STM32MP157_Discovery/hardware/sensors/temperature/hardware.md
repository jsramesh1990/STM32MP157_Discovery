# Temperature Sensor Hardware

## 1. Hardware Overview

The temperature sensor is connected to the STM32MP157 Cortex-M4 through
a digital communication interface.

The sensor power can be controlled to reduce energy consumption.

```text
                       STM32MP157
                           │
                    ┌──────┴──────┐
                    │  Cortex-M4  │
                    └──────┬──────┘
                           │
             ┌─────────────┼─────────────┐
             │             │             │
            SDA           SCL           INT
             │             │             │
             └─────────────┼─────────────┘
                           │
                           ▼
                  Temperature Sensor
                           ▲
                           │
                         VDD
                           │
                    ┌──────┴──────┐
                    │ Load Switch │
                    └──────┬──────┘
                           ▲
                           │
                    Power Enable
                           │
                       Cortex-M4
````

---

## 2. Hardware Blocks

```text
┌────────────────────────┐
│ Energy Source          │
│ Solar/Thermal/Kinetic  │
└───────────┬────────────┘
            │
            ▼
┌────────────────────────┐
│ Energy Harvesting PMIC │
└───────────┬────────────┘
            │
            ▼
┌────────────────────────┐
│ Energy Storage         │
└───────────┬────────────┘
            │
            ▼
┌────────────────────────┐
│ Power Management       │
└───────────┬────────────┘
            │
            ▼
┌────────────────────────┐
│ STM32MP157             │
│ Cortex-M4              │
└───────────┬────────────┘
            │
            │ I2C / SPI
            ▼
┌────────────────────────┐
│ Temperature Sensor     │
└────────────────────────┘
```

---

## 3. Electrical Connections

The exact pins depend on the selected sensor and STM32MP157 hardware.

Typical I2C connection:

| STM32MP157    | Temperature Sensor |
| ------------- | ------------------ |
| I2C SDA       | SDA                |
| I2C SCL       | SCL                |
| GPIO          | INT                |
| GPIO          | Power Enable       |
| GND           | GND                |
| Sensor Supply | VDD                |

---

## 4. I2C Pull-Up

I2C requires pull-up resistors.

```text
             VDD
              │
             R1
              │
SDA ──────────┼──────── Sensor SDA


             VDD
              │
             R2
              │
SCL ──────────┼──────── Sensor SCL
```

The resistor values must be selected according to:

* I2C bus speed
* Bus capacitance
* Sensor requirements
* Supply voltage
* Electrical characteristics

---

## 5. Sensor Power Control

A load switch can disconnect the temperature sensor from the power rail.

```text
                    VDD
                     │
                     ▼
               ┌───────────┐
M4 GPIO ──────►│Load Switch│
               └─────┬─────┘
                     │
                     ▼
             Temperature Sensor
```

This allows the sensor to consume almost no operating current when
measurement is not required, apart from leakage through the surrounding
circuitry.

---

## 6. Power States

### Active

```text
Power Enable = ON
Sensor VDD   = ON
I2C          = Active
Measurement  = Active
```

### Low Power

```text
Power Enable = OFF
Sensor VDD   = OFF
I2C          = Idle
Measurement  = Disabled
```

---

## 7. Temperature Sensor Placement

Sensor placement is important.

Avoid placing the sensor immediately next to:

* High-power regulators
* CPU heat sources
* PMIC
* Power transistors
* High-current traces

because these can introduce measurement errors.

For an environmental temperature sensor:

```text
Heat Sources
     │
     │ Keep away
     ▼
Temperature Sensor
     │
     ▼
Environmental Temperature
```

For equipment monitoring, the sensor should have appropriate thermal
coupling to the equipment being measured.

---

## 8. GPIO Interrupt

If supported:

```text
Temperature Sensor
        │
        │ INT
        ▼
STM32MP157 GPIO
        │
        ▼
Cortex-M4 Interrupt
```

The interrupt can indicate:

* Over-temperature
* Under-temperature
* Data ready
* Threshold crossing
* Sensor fault

---

## 9. Voltage Compatibility

Before connecting the sensor, verify:

```text
Sensor VDD
Sensor I/O voltage
STM32MP157 I/O voltage
I2C pull-up voltage
```

Voltage compatibility must be verified against the actual sensor and
STM32MP157 hardware documentation.

---

## 10. Low-Power Hardware Considerations

The design should minimize leakage from:

* Sensor
* Pull-up resistors
* Load switch
* Regulators
* GPIOs
* Level shifters
* Protection components

For a production sub-µA target, every leakage path must be considered.

---

## 11. Discovery Kit

The STM32MP157 Discovery Kit can be used to develop and test:

```text
Temperature Sensor
       │
       ▼
Cortex-M4
       │
       ▼
Low-Power Control
       │
       ▼
Cortex-A7
       │
       ▼
Linux
```

The complete Discovery Kit should not be considered a sub-1 µA
production sensor platform.

A custom low-leakage PCB is required for the final energy-harvesting
sensor node.

