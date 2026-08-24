# Temperature Sensor Interface

## 1. Overview

The temperature sensor communicates with the STM32MP157 Cortex-M4 using
a digital interface.

Common interfaces are:

- I2C
- SPI
- GPIO interrupt

For a typical low-speed temperature sensor, I2C is suitable.

---

## 2. I2C Architecture

```text
                 STM32MP157
                 Cortex-M4
                     │
             ┌───────┴───────┐
             │               │
            SDA             SCL
             │               │
             └───────┬───────┘
                     │
                     ▼
             Temperature Sensor
````

I2C signals:

```text
SDA → Serial Data
SCL → Serial Clock
```

I2C normally requires pull-up resistors.

---

## 3. Optional Interrupt

A temperature sensor may provide an interrupt for:

* Temperature threshold
* Over-temperature
* Under-temperature
* Data ready
* Sensor fault

```text
Temperature Sensor
        │
        │ INT
        ▼
STM32MP157 GPIO
        │
        ▼
Cortex-M4
```

---

## 4. Sensor Power Enable

For low-power operation, the sensor power can be controlled.

```text
Cortex-M4 GPIO
      │
      ▼
 Load Switch
      │
      ▼
Temperature Sensor
```

Typical operation:

```text
GPIO = HIGH
     ↓
Sensor ON

GPIO = LOW
     ↓
Sensor OFF
```

The actual polarity depends on the selected power switch.

---

## 5. I2C Measurement Sequence

```text
START
  │
  ▼
Sensor Address
  │
  ▼
Register Address
  │
  ▼
Configure / Start Measurement
  │
  ▼
Wait for Conversion
  │
  ▼
Read Temperature Registers
  │
  ▼
STOP
```

---

## 6. Register Read Sequence

Typical I2C read:

```text
START
  │
  ▼
Sensor Address + WRITE
  │
  ▼
Register Address
  │
  ▼
REPEATED START
  │
  ▼
Sensor Address + READ
  │
  ▼
Read Data
  │
  ▼
STOP
```

The exact transaction depends on the selected sensor.

---

## 7. Temperature Data Flow

```text
Temperature Registers
          │
          ▼
       Raw Data
          │
          ▼
      Cortex-M4
          │
          ▼
    Sensor Manager
          │
          ▼
      Calibration
          │
          ▼
 Temperature Conversion
          │
          ▼
 Temperature in °C
```

---

## 8. Communication Parameters

The final configuration must define:

| Parameter        | Value            |
| ---------------- | ---------------- |
| Interface        | I2C / SPI        |
| I2C Address      | Sensor dependent |
| Bus Speed        | Sensor dependent |
| Supply Voltage   | Sensor dependent |
| Logic Voltage    | Sensor dependent |
| Data Width       | Sensor dependent |
| Interrupt        | Optional         |
| Pull-up          | Required for I2C |
| Measurement Rate | Sensor dependent |

Do not use placeholder values in the final hardware configuration.

---

## 9. Error Handling

The temperature driver should detect:

```text
Communication Error
       │
       ├── Sensor Not Responding
       ├── I2C NACK
       ├── Timeout
       ├── Invalid Data
       └── Sensor Fault
```

Recovery:

```text
Error
 │
 ▼
Retry
 │
 ▼
Successful?
 ├── YES → Continue
 │
 └── NO
      │
      ▼
 Sensor Reset
      │
      ▼
 Reinitialize
      │
      ▼
 Report Error
```

---

## 10. Low-Power Sequence

```text
Low Power
    │
    ▼
Wake M4
    │
    ▼
Enable Sensor Power
    │
    ▼
Wait for Startup
    │
    ▼
Initialize Interface
    │
    ▼
Start Measurement
    │
    ▼
Read Temperature
    │
    ▼
Process Result
    │
    ▼
Disable Sensor
    │
    ▼
Return to Low Power
```

Timing values must be taken from the selected sensor datasheet.


