# Pressure Sensor Register Map

## 1. Purpose

This document defines the register-level interface of the selected
pressure sensor.

The exact register map must be populated after selecting the actual
pressure sensor IC.

---

## 2. Sensor Information

| Parameter | Value |
|---|---|
| Manufacturer | TBD |
| Part Number | TBD |
| Interface | I2C / SPI |
| Device Address | TBD |
| Supply Voltage | TBD |
| Measurement Range | TBD |
| Resolution | TBD |
| Operating Current | TBD |
| Sleep Current | TBD |
| Data Rate | TBD |

---

## 3. Register Map

The following table is a project template.

| Address | Register | Access | Reset | Description |
|---|---|---|---|---|
| TBD | DEVICE_ID | R | TBD | Device identification |
| TBD | STATUS | R | TBD | Sensor status |
| TBD | CTRL | R/W | TBD | Sensor control |
| TBD | CONFIG | R/W | TBD | Sensor configuration |
| TBD | PRESSURE_L | R | TBD | Pressure low byte |
| TBD | PRESSURE_H | R | TBD | Pressure high byte |
| TBD | INT_CONFIG | R/W | TBD | Interrupt configuration |

**Do not use these addresses until the actual sensor datasheet has been
added.**

---

## 4. Device Identification

The driver should normally verify the sensor during initialization.

```text
Cortex-M4
    │
    ▼
Read DEVICE_ID
    │
    ▼
Compare Expected ID
    │
 ┌──┴───────┐
 │          │
Match     Mismatch
 │          │
 ▼          ▼
Continue   Error
````

---

## 5. Sensor Initialization

Typical sequence:

```text
Reset Sensor
     │
     ▼
Read Device ID
     │
     ▼
Configure Measurement Mode
     │
     ▼
Configure Output Data Rate
     │
     ▼
Configure Resolution
     │
     ▼
Configure Interrupt
     │
     ▼
Sensor Ready
```

The exact sequence depends on the selected pressure sensor.

---

## 6. Pressure Data

A typical sensor provides raw pressure data.

```text
Raw Register Data
       │
       ▼
Combine Bytes
       │
       ▼
Raw Pressure
       │
       ▼
Apply Scale Factor
       │
       ▼
Apply Offset
       │
       ▼
Pressure Value
```

The actual conversion formula must come from the sensor datasheet.

Example conceptual formula:

```text
Pressure = RawValue × Scale + Offset
```

Do not use this formula directly without confirming the selected sensor's
datasheet.

---

## 7. Status Register

The status register may contain flags such as:

```text
DATA_READY
OVERFLOW
ERROR
INTERRUPT
```

The exact bit positions depend on the sensor.

---

## 8. Interrupt Configuration

Possible configuration:

```text
Pressure Threshold
       │
       ▼
Sensor Comparator
       │
       ▼
Interrupt
       │
       ▼
STM32MP157 GPIO
       │
       ▼
Cortex-M4
```

This can be used to wake the M4 only when an important pressure event
occurs.

---

## 9. Low-Power Registers

If supported by the selected sensor, configure:

* Shutdown mode
* Standby mode
* One-shot measurement
* Measurement rate
* Interrupt wake-up

The exact register fields must be copied from the selected sensor
datasheet.

---

## 10. Finalization

After selecting the physical pressure sensor, update this document with:

1. Exact part number
2. Exact I2C/SPI address
3. Complete register map
4. Register bit fields
5. Reset values
6. Measurement conversion formula
7. Calibration procedure
8. Timing requirements
9. Power consumption
10. Interrupt configuration

