# Vibration Sensor Register Map

## 1. Purpose

This document defines the register-level interface of the selected
vibration sensor.

The exact register addresses and bit definitions must be obtained from
the datasheet of the selected vibration sensor IC.

---

## 2. Sensor Information

| Parameter | Value |
|---|---|
| Manufacturer | TBD |
| Part Number | TBD |
| Sensor Type | Accelerometer / IMU |
| Interface | SPI / I2C |
| Device Address | TBD |
| Supply Voltage | TBD |
| Accelerometer Range | TBD |
| Resolution | TBD |
| Output Data Rate | TBD |
| Bandwidth | TBD |
| FIFO Size | TBD |
| Operating Current | TBD |
| Standby Current | TBD |

---

## 3. Register Map

The following is a project template only.

| Address | Register | Access | Reset | Description |
|---|---|---|---|---|
| TBD | DEVICE_ID | R | TBD | Device identification |
| TBD | STATUS | R | TBD | Sensor status |
| TBD | CTRL | R/W | TBD | Sensor control |
| TBD | CONFIG | R/W | TBD | Sensor configuration |
| TBD | ODR | R/W | TBD | Output data rate |
| TBD | RANGE | R/W | TBD | Accelerometer range |
| TBD | FILTER | R/W | TBD | Filter configuration |
| TBD | INT_CONFIG | R/W | TBD | Interrupt configuration |
| TBD | FIFO_CONFIG | R/W | TBD | FIFO configuration |
| TBD | FIFO_STATUS | R | TBD | FIFO status |
| TBD | FIFO_DATA | R | TBD | FIFO sample data |
| TBD | X_L | R | TBD | X-axis low byte |
| TBD | X_H | R | TBD | X-axis high byte |
| TBD | Y_L | R | TBD | Y-axis low byte |
| TBD | Y_H | R | TBD | Y-axis high byte |
| TBD | Z_L | R | TBD | Z-axis low byte |
| TBD | Z_H | R | TBD | Z-axis high byte |

**These addresses are placeholders and must not be used directly in
firmware.**

---

## 4. Device Identification

The Cortex-M4 should verify the sensor during initialization.

```text
Cortex-M4
    │
    ▼
Read DEVICE_ID
    │
    ▼
Compare Expected ID
    │
 ┌──┴──────────┐
 │             │
Match       Mismatch
 │             │
 ▼             ▼
Continue      Error
````

---

## 5. Sensor Initialization

Typical initialization:

```text
Reset Sensor
     │
     ▼
Read Device ID
     │
     ▼
Configure Accelerometer
     │
     ▼
Configure Range
     │
     ▼
Configure Output Data Rate
     │
     ▼
Configure Bandwidth
     │
     ▼
Configure FIFO
     │
     ▼
Configure Interrupt
     │
     ▼
Sensor Ready
```

The exact register sequence depends on the selected sensor.

---

## 6. Accelerometer Data

Typical data path:

```text
X/Y/Z Registers
      │
      ▼
Raw ADC Data
      │
      ▼
Combine Bytes
      │
      ▼
Signed Acceleration
      │
      ▼
Apply Sensitivity
      │
      ▼
Acceleration
      │
      ▼
Signal Processing
```

Typical units:

```text
mg
m/s²
g
```

The exact conversion formula is sensor-dependent.

---

## 7. FIFO Configuration

A vibration sensor may use a FIFO to store samples.

```text
Sensor
  │
  ▼
X/Y/Z Samples
  │
  ▼
FIFO
  │
  ▼
FIFO Watermark
  │
  ▼
Interrupt
  │
  ▼
Cortex-M4
```

The register configuration should define:

* FIFO mode
* FIFO watermark
* FIFO sample format
* FIFO threshold
* FIFO overflow behavior

---

## 8. Output Data Rate

The output data rate controls how frequently acceleration samples are
generated.

```text
Low ODR
   │
   ├── Lower data rate
   ├── Lower processing load
   └── Lower energy consumption

High ODR
   │
   ├── More samples
   ├── Better high-frequency analysis
   └── Higher energy consumption
```

The selected ODR must match the vibration frequency range being monitored.

---

## 9. Accelerometer Range

Typical accelerometer ranges may include:

```text
±2 g
±4 g
±8 g
±16 g
```

The actual supported ranges depend on the selected sensor.

The range should be selected according to the expected machine vibration.

---

## 10. Interrupt Configuration

Possible interrupt sources:

```text
DATA_READY
FIFO_WATERMARK
FIFO_OVERFLOW
MOTION
THRESHOLD
SENSOR_ERROR
```

Example:

```text
Vibration
    │
    ▼
Threshold Detector
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

---

## 11. Vibration Feature Processing

The raw acceleration samples can be converted into useful features.

### RMS

```text
RMS = sqrt(sum(x²) / N)
```

### Peak

```text
Peak = maximum(abs(x))
```

### Peak-to-Peak

```text
Peak-to-Peak = Maximum - Minimum
```

### Frequency

Frequency can be determined using:

* Zero crossing
* FFT
* Sensor hardware features

The final algorithm depends on the application.

---

## 12. Fault Detection

```text
Raw Samples
     │
     ▼
Filtering
     │
     ▼
Feature Extraction
     │
     ▼
Threshold Comparison
     │
 ┌───┴────┐
 │        │
Normal   Fault
 │        │
 ▼        ▼
Sleep    Event
           │
           ▼
        Wake A7
```

---

## 13. Low-Power Registers

If supported by the selected sensor, configure:

* Power-down mode
* Standby mode
* Low-power mode
* Output data rate
* FIFO
* Motion detection
* Wake-up interrupt

The exact register fields must come from the sensor datasheet.

---

## 14. Finalization

After selecting the physical vibration sensor IC, update this document
with:

1. Exact manufacturer
2. Exact part number
3. SPI/I2C configuration
4. Device ID
5. Device address if I2C
6. Complete register map
7. Register bit fields
8. Reset values
9. Accelerometer range
10. Output data rate
11. Bandwidth
12. FIFO configuration
13. Interrupt configuration
14. Data conversion formula
15. Power consumption
16. Low-power configuration

