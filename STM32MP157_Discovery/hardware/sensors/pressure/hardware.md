# Pressure Sensor Hardware

## 1. Hardware Overview

The pressure sensor is connected to the STM32MP157 through a digital
interface and a controllable power supply.

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
                   Pressure Sensor
                           ▲
                           │
                       VDD │
                           │
                      Load Switch
                           ▲
                           │
                    Power Enable
                           │
                       Cortex-M4
````

---

## 2. Main Hardware Blocks

```text
┌──────────────────────┐
│ Energy Source        │
│ Solar/Thermal/Kinetic│
└──────────┬───────────┘
           │
           ▼
┌──────────────────────┐
│ Energy Harvesting    │
│ PMIC                 │
└──────────┬───────────┘
           │
           ▼
┌──────────────────────┐
│ Energy Storage       │
│ Supercapacitor/etc.  │
└──────────┬───────────┘
           │
           ▼
┌──────────────────────┐
│ Power Management     │
└──────────┬───────────┘
           │
           ▼
┌──────────────────────┐
│ STM32MP157           │
│ Cortex-M4            │
└──────────┬───────────┘
           │
           ├─────────────── I2C/SPI
           │
           ▼
┌──────────────────────┐
│ Pressure Sensor      │
└──────────────────────┘
```

---

## 3. Electrical Connections

The exact connections depend on the selected pressure sensor.

Typical I2C configuration:

| STM32MP157    | Pressure Sensor |
| ------------- | --------------- |
| I2C SDA       | SDA             |
| I2C SCL       | SCL             |
| GPIO          | INT             |
| GPIO          | Power Enable    |
| GND           | GND             |
| Sensor Supply | VDD             |

---

## 4. I2C Pull-Up

I2C requires pull-up resistors.

```text
        VDD
         │
       ┌─┴─┐
       │R1 │
       └─┬─┘
         │
SDA ─────┼──────── Sensor SDA

        VDD
         │
       ┌─┴─┐
       │R2 │
       └─┬─┘
         │
SCL ─────┼──────── Sensor SCL
```

The resistor values must be selected according to:

* Bus speed
* Bus capacitance
* Sensor requirements
* Voltage level
* STM32MP157 electrical characteristics

---

## 5. Sensor Power Control

The sensor power should preferably be switchable.

```text
                 Sensor Supply
                     │
                     ▼
              ┌─────────────┐
              │ Load Switch │
              └──────┬──────┘
                     │
                     ▼
              Pressure Sensor
                     ▲
                     │
               Enable GPIO
                     │
                     ▼
                Cortex-M4
```

This allows the sensor to be completely disconnected during long
low-power periods.

---

## 6. Power States

### Sensor ON

```text
Power Enable = ON
Sensor VDD   = ON
I2C          = Active
Measurement  = Active
```

### Sensor OFF

```text
Power Enable = OFF
Sensor VDD   = OFF
I2C          = Idle
Measurement  = Disabled
```

---

## 7. GPIO Interrupt

If the selected sensor supports an interrupt:

```text
Pressure Sensor
      │
      │ INT
      ▼
STM32MP157 GPIO
      │
      ▼
Cortex-M4 Interrupt
```

Possible events:

* Data ready
* Pressure threshold exceeded
* Pressure alarm
* Sensor error

---

## 8. Voltage Compatibility

Before connecting the sensor, verify:

```text
Sensor VDD
Sensor I/O voltage
STM32MP157 I/O voltage
I2C pull-up voltage
```

Never connect a sensor directly until voltage compatibility has been
verified against the actual hardware documentation.

---

## 9. Low-Power Hardware Design

The low-power design should minimize leakage from:

* Sensor
* Pull-up resistors
* Load switch
* Voltage regulators
* GPIOs
* Protection components
* Level shifters

The complete production board must be designed for the target leakage
current.

---

## 10. Discovery Kit Consideration

The STM32MP157 Discovery Kit is primarily a development platform.

It can be used to demonstrate:

```text
Sensor
  ↓
Cortex-M4
  ↓
Low-power control
  ↓
Cortex-A7
  ↓
Linux
```

However, the complete Discovery Kit should not be treated as a
sub-1 µA production sensor node.

A custom PCB is required for aggressive system-level current targets.

