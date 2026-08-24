# Vibration Sensor Hardware

## 1. Hardware Overview

The vibration sensor is mounted on or near the equipment being monitored.

The sensor communicates with the STM32MP157 Cortex-M4 using SPI or I2C.

```text
                       Industrial Machine
                              │
                              ▼
                         Vibration
                              │
                              ▼
                    ┌──────────────────┐
                    │ Vibration Sensor │
                    └────────┬─────────┘
                             │
                 ┌───────────┼───────────┐
                 │           │           │
                SPI         INT        VDD
                 │           │           │
                 ▼           ▼           ▼
              STM32MP157  GPIO       Power
              Cortex-M4              Supply
````

---

## 2. Complete Hardware Architecture

```text
┌──────────────────────────┐
│ Energy Source            │
│ Solar / Thermal / Kinetic│
└────────────┬─────────────┘
             │
             ▼
┌──────────────────────────┐
│ Energy Harvesting PMIC   │
└────────────┬─────────────┘
             │
             ▼
┌──────────────────────────┐
│ Energy Storage           │
│ Supercapacitor / Battery │
└────────────┬─────────────┘
             │
             ▼
┌──────────────────────────┐
│ Power Management         │
└────────────┬─────────────┘
             │
             ▼
┌──────────────────────────┐
│ STM32MP157               │
│ Cortex-M4                │
└────────────┬─────────────┘
             │
             │ SPI / I2C
             ▼
┌──────────────────────────┐
│ Vibration Sensor         │
│ Accelerometer / IMU      │
└──────────────────────────┘
             ▲
             │
         Mechanical
         Vibration
             │
             ▼
        Industrial Machine
```

---

## 3. Typical SPI Connections

| STM32MP157    | Vibration Sensor |
| ------------- | ---------------- |
| SPI SCLK      | SCLK             |
| SPI MOSI      | MOSI             |
| SPI MISO      | MISO             |
| SPI CS        | CS               |
| GPIO          | INT              |
| GPIO          | Power Enable     |
| GND           | GND              |
| Sensor Supply | VDD              |

The actual STM32MP157 pins must be taken from the selected board
schematic and Device Tree configuration.

---

## 4. I2C Alternative

If the selected vibration sensor uses I2C:

| STM32MP157    | Vibration Sensor |
| ------------- | ---------------- |
| I2C SDA       | SDA              |
| I2C SCL       | SCL              |
| GPIO          | INT              |
| GPIO          | Power Enable     |
| GND           | GND              |
| Sensor Supply | VDD              |

---

## 5. Vibration Sensor Placement

Sensor placement is critical.

For machine monitoring:

```text
              Motor
        ┌──────────────┐
        │              │
        │   Machine    │
        │              │
        └──────┬───────┘
               │
               │ Mechanical
               │ vibration
               ▼
        ┌──────────────┐
        │ Vibration    │
        │ Sensor       │
        └──────────────┘
```

The sensor should be mounted securely to the equipment.

Poor mechanical mounting can introduce:

* Measurement errors
* Resonance
* Noise
* Reduced bandwidth
* Incorrect vibration levels

---

## 6. Sensor Orientation

For a 3-axis accelerometer:

```text
             Z
             ↑
             │
             │
             └──────► X
            /
           /
          Y
```

The software must document the physical sensor orientation.

This is important when interpreting X/Y/Z measurements.

---

## 7. Power Control

The sensor power can be controlled using a load switch.

```text
                    Main Supply
                         │
                         ▼
                  ┌────────────┐
M4 GPIO ─────────►│ Load Switch│
                  └─────┬──────┘
                        │
                        ▼
                Vibration Sensor
```

This enables sensor power gating during low-power operation.

---

## 8. Interrupt Connection

```text
Vibration Sensor
       │
       │ INT
       ▼
STM32MP157 GPIO
       │
       ▼
Cortex-M4
       │
       ▼
Interrupt Handler
```

The interrupt can indicate:

* Data ready
* FIFO watermark
* FIFO overflow
* Motion detected
* Vibration threshold
* Sensor fault

---

## 9. FIFO Hardware Concept

```text
        Sensor
           │
           ▼
     ADC / Processing
           │
           ▼
         FIFO
           │
      Watermark
           │
           ▼
      Interrupt
           │
           ▼
        Cortex-M4
```

FIFO reduces the number of processor interrupts and allows burst
transfers.

---

## 10. Power States

### Active

```text
Sensor VDD   = ON
Interface    = Active
Sampling     = Active
FIFO         = Active
Interrupt    = Enabled
```

### Low Power

```text
Sensor VDD   = OFF
Interface    = Idle
Sampling     = Disabled
FIFO         = Disabled
Interrupt    = Disabled
```

The exact power states depend on the selected sensor.

---

## 11. Energy-Harvesting Integration

A vibration sensor can coexist with a kinetic energy harvester.

```text
              Machine Vibration
                     │
             ┌───────┴────────┐
             │                │
             ▼                ▼
      Kinetic Harvester   Vibration Sensor
             │                │
             ▼                ▼
      Energy Storage       Cortex-M4
             │                │
             └───────┬────────┘
                     │
                     ▼
                STM32MP157
```

The mechanical design must prevent the energy harvester from
significantly disturbing the vibration measurement.

---

## 12. Low-Power Hardware Considerations

Minimize leakage from:

* Sensor
* Load switch
* Pull-up resistors
* GPIOs
* Level shifters
* Regulators
* Protection components

High-speed vibration acquisition should only be enabled when required.

---

## 13. Discovery Kit Consideration

The STM32MP157 Discovery Kit can be used to demonstrate:

```text
Vibration Sensor
       │
       ▼
SPI/I2C
       │
       ▼
Cortex-M4
       │
       ▼
Signal Processing
       │
       ▼
Event Detection
       │
       ▼
RPMsg
       │
       ▼
Cortex-A7/Linux

