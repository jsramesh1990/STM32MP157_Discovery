# Vibration Sensor Interface

## 1. Overview

A vibration sensor generally produces high-rate acceleration data.
SPI is preferred when high sampling rates and large data transfers are
required.

I2C can also be used when the selected sensor and sampling requirements
permit it.

The interface can include:

- SPI
- I2C
- GPIO interrupt
- Sensor power enable

---

## 2. SPI Architecture

```text
                    STM32MP157
                    Cortex-M4
                        │
             ┌──────────┼──────────┐
             │          │          │
            SCLK       MOSI       MISO
             │          │          │
             └──────────┼──────────┘
                        │
                       CS
                        │
                        ▼
                Vibration Sensor
````

SPI signals:

```text
SCLK → Serial Clock
MOSI → Master Out / Sensor In
MISO → Sensor Out / Master In
CS   → Chip Select
```

---

## 3. Sensor Interrupt

A vibration sensor normally provides an interrupt signal.

```text
Vibration Sensor
       │
       │ INT
       ▼
STM32MP157 GPIO
       │
       ▼
Cortex-M4 Interrupt
```

Possible interrupt events:

* Data ready
* FIFO watermark
* FIFO overflow
* Motion detection
* Threshold exceeded
* Sensor fault

---

## 4. FIFO Operation

High-rate sensors commonly contain a FIFO.

```text
                 Sensor
                    │
                    ▼
              ADC / Samples
                    │
                    ▼
                 FIFO
                    │
              FIFO Threshold
                    │
                    ▼
                Interrupt
                    │
                    ▼
                Cortex-M4
                    │
                    ▼
              Read FIFO Burst
```

This reduces processor overhead.

---

## 5. Acquisition Sequence

```text
Sensor Interrupt
       │
       ▼
Wake Cortex-M4
       │
       ▼
Read FIFO Status
       │
       ▼
Read FIFO Samples
       │
       ▼
Clear Interrupt
       │
       ▼
Process Samples
```

---

## 6. Sensor Power Enable

```text
Cortex-M4 GPIO
      │
      ▼
 Load Switch
      │
      ▼
Vibration Sensor
```

Typical operation:

```text
GPIO = ON
   ↓
Sensor Powered

GPIO = OFF
   ↓
Sensor Power Disabled
```

The actual polarity depends on the hardware.

---

## 7. SPI Transfer

Typical transaction:

```text
CS LOW
  │
  ▼
Register Address
  │
  ▼
Read / Write Command
  │
  ▼
Data Transfer
  │
  ▼
CS HIGH
```

For a FIFO burst:

```text
CS LOW
  │
  ▼
FIFO Read Command
  │
  ▼
Sample 0
  │
  ▼
Sample 1
  │
  ▼
Sample 2
  │
  ▼
...
  │
  ▼
CS HIGH
```

---

## 8. Vibration Data Flow

```text
Accelerometer
      │
      ▼
Raw X/Y/Z Samples
      │
      ▼
Cortex-M4
      │
      ▼
Filtering
      │
      ▼
Feature Extraction
      │
      ├── RMS
      ├── Peak
      ├── Frequency
      └── Threshold
      │
      ▼
Event Detection
```

---

## 9. Signal Processing

The Cortex-M4 can calculate:

### RMS

```text
RMS = sqrt(sum(x²) / N)
```

### Peak

```text
Peak = maximum absolute sample
```

### Peak-to-Peak

```text
Peak-to-Peak = Maximum - Minimum
```

### Frequency

Frequency analysis can be implemented using:

* Zero-crossing
* FFT
* Sensor hardware features

The exact algorithm depends on the application.

---

## 10. Communication Parameters

The final configuration must define:

| Parameter           | Value            |
| ------------------- | ---------------- |
| Interface           | SPI / I2C        |
| SPI Mode            | Sensor dependent |
| SPI Frequency       | Sensor dependent |
| Chip Select         | Sensor dependent |
| Interrupt GPIO      | Sensor dependent |
| Supply Voltage      | Sensor dependent |
| Sample Rate         | Sensor dependent |
| Accelerometer Range | Sensor dependent |
| FIFO Size           | Sensor dependent |

---

## 11. Error Handling

Possible errors:

```text
SPI Error
   │
   ├── Sensor Not Responding
   ├── Invalid Device ID
   ├── Transfer Timeout
   ├── FIFO Overflow
   ├── FIFO Underflow
   └── Invalid Data
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
 Report Fault
```

---

## 12. Low-Power Acquisition

```text
                    Sleep
                      │
                      ▼
                  Wake M4
                      │
                      ▼
              Enable Sensor
                      │
                      ▼
              Start Sampling
                      │
                      ▼
                FIFO Fill
                      │
                      ▼
                INT → M4
                      │
                      ▼
                Read FIFO
                      │
                      ▼
              Process Samples
                      │
                      ▼
             Sensor Power OFF
                      │
                      ▼
                    Sleep
```
