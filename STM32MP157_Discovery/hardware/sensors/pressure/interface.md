# Pressure Sensor Interface

## 1. Overview

The pressure sensor communicates with the STM32MP157 Cortex-M4 through
a digital hardware interface.

The preferred interface depends on the selected sensor.

Common interfaces are:

- I2C
- SPI
- GPIO interrupt

For a low-speed pressure sensor, I2C is generally suitable.

For a high-speed or specialized sensor, SPI may be selected.

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
              Pressure Sensor
````

I2C uses:

```text
SDA → Serial Data
SCL → Serial Clock
```

Both signals normally require pull-up resistors.

---

## 3. Optional Interrupt

Some pressure sensors provide a data-ready or threshold interrupt.

```text
Pressure Sensor
      │
      │ INT
      ▼
STM32MP157 GPIO
      │
      ▼
Cortex-M4
```

The interrupt can be used for:

* Measurement ready
* Pressure threshold
* Alarm condition
* Sensor fault
* Motion/event notification

---

## 4. Sensor Power Enable

For energy-aware operation, sensor power can be controlled.

```text
Cortex-M4 GPIO
      │
      ▼
Load Switch
      │
      ▼
Pressure Sensor
```

Operation:

```text
GPIO = HIGH
     ↓
Sensor ON

GPIO = LOW
     ↓
Sensor OFF
```

The actual GPIO polarity depends on the selected load switch.

---

## 5. I2C Measurement Sequence

```text
START
  │
  ▼
I2C Sensor Address
  │
  ▼
Write Configuration
  │
  ▼
Start Measurement
  │
  ▼
Wait for Conversion
  │
  ▼
Read Pressure Registers
  │
  ▼
STOP
```

---

## 6. Register Read Sequence

Typical register access:

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

## 7. Pressure Data Flow

```text
Sensor Register
      │
      ▼
Raw Pressure Data
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
Pressure Conversion
      │
      ▼
Physical Value
```

Example physical units:

```text
Pa
kPa
bar
mbar
psi
```

---

## 8. Communication Parameters

The following parameters must be defined for the selected sensor:

| Parameter         | Configuration    |
| ----------------- | ---------------- |
| Interface         | I2C / SPI        |
| I2C Address       | Sensor dependent |
| Bus Speed         | Sensor dependent |
| Supply Voltage    | Sensor dependent |
| Logic Voltage     | Sensor dependent |
| Data Width        | Sensor dependent |
| Interrupt         | Optional         |
| Pull-up           | Required for I2C |
| Maximum Frequency | Sensor dependent |

Do not use placeholder values in the production configuration.

---

## 9. Error Handling

The driver should detect:

```text
I2C Bus Error
     │
     ├── Sensor Not Responding
     ├── NACK
     ├── Timeout
     ├── Invalid Register
     └── Invalid Measurement
```

Recommended recovery:

```text
Communication Error
        │
        ▼
Retry
        │
        ▼
Still Failing?
     /       \
   NO         YES
   │           │
   ▼           ▼
Continue    Reset Sensor
               │
               ▼
          Reinitialize
               │
               ▼
          Report Fault
```

---

## 10. Low-Power Interface Sequence

```text
Wake-up
   │
   ▼
Enable Sensor Power
   │
   ▼
Wait for Sensor Startup
   │
   ▼
Initialize I2C
   │
   ▼
Read Pressure
   │
   ▼
Disable Sensor
   │
   ▼
Return to Low Power
```

The timing values must be obtained from the selected sensor datasheet.

