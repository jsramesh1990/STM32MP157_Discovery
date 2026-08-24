# Vibration Sensor

## 1. Overview

The vibration sensor subsystem monitors mechanical vibration from
industrial equipment such as motors, pumps, compressors and rotating
machines.

The sensor provides vibration data to the STM32MP157 Cortex-M4.
The Cortex-M4 performs low-latency acquisition and signal processing,
while the Cortex-A7/Linux subsystem performs high-level analysis,
logging and communication.

## 2. System Architecture

```text
                       STM32MP157
                            │
             ┌──────────────┴──────────────┐
             │                             │
         Cortex-A7                     Cortex-M4
             │                             │
           Linux                    Sensor Manager
             │                             │
             │                             ▼
             │                     Vibration Sensor
             │                             │
             │                          SPI/I2C
             │                             │
             └──────── RPMsg ──────────────┘
````

## 3. Vibration Monitoring

```text
Machine
   │
   ▼
Mechanical Vibration
   │
   ▼
Vibration Sensor
   │
   ▼
Cortex-M4
   │
   ▼
Signal Processing
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
   │
   ├── Normal
   │
   └── Fault
```

## 4. Sensor Responsibilities

The vibration sensor subsystem provides:

* Sensor initialization
* Sensor configuration
* Vibration data acquisition
* Accelerometer data acquisition
* FIFO handling
* Data filtering
* RMS calculation
* Peak detection
* Frequency analysis
* Threshold detection
* Fault/event detection
* Interrupt handling
* Low-power operation

## 5. Measurement Flow

```text
              Wake-up
                 │
                 ▼
        Enable Sensor Power
                 │
                 ▼
        Initialize Sensor
                 │
                 ▼
        Configure Sensor
                 │
                 ▼
         Start Acquisition
                 │
                 ▼
          Read Sensor FIFO
                 │
                 ▼
          Process Samples
                 │
                 ▼
       Calculate Vibration
             Features
                 │
        ┌────────┴────────┐
        │                 │
      Normal             Fault
        │                 │
        ▼                 ▼
      Sleep          Generate Event
                          │
                          ▼
                       Wake A7
                          │
                          ▼
                       Linux
```

## 6. Cortex-M4 Role

The Cortex-M4 is responsible for low-latency vibration processing.

```text
Vibration Sensor
       │
       ▼
Sensor Driver
       │
       ▼
FIFO / Samples
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
       │
       ▼
RPMsg
       │
       ▼
Cortex-A7
```

## 7. Cortex-A7 Role

Linux/Cortex-A7 can perform:

* Long-term vibration logging
* FFT analysis
* Machine-health monitoring
* Data visualization
* Database storage
* Network communication
* Cloud communication
* Fault reporting
* Configuration

The A7 does not need to process every raw vibration sample.

## 8. Event-Based Architecture

```text
                    Vibration
                        │
                        ▼
                       M4
                        │
                        ▼
                 Analyze Samples
                        │
                        ▼
                Compare Threshold
                        │
                ┌───────┴───────┐
                │               │
              Normal           Fault
                │               │
                ▼               ▼
              Sleep          Wake A7
                                │
                                ▼
                              Linux
                                │
                                ▼
                         Store / Transmit
```

## 9. Low-Power Strategy

The sensor can operate using periodic or event-based sampling.

```text
Low Power
    │
    ▼
Wake M4
    │
    ▼
Enable Sensor
    │
    ▼
Acquire Samples
    │
    ▼
Process Samples
    │
    ▼
Fault/Event?
   /       \
 NO         YES
 │           │
 ▼           ▼
Sleep      Wake A7
 │           │
 └─────┬─────┘
       ▼
     Sleep
```

## 10. Industrial Applications

Possible applications include:

* Motor monitoring
* Pump monitoring
* Compressor monitoring
* Bearing monitoring
* Gearbox monitoring
* Fan monitoring
* Rotating machinery
* Industrial predictive maintenance
* Structural vibration monitoring

## 11. Energy-Harvesting Integration

Vibration monitoring is particularly suitable for an energy-aware
industrial sensor because the machine vibration can potentially be used
both as:

1. The measurement source
2. The energy source

```text
                Industrial Machine
                       │
             ┌─────────┴─────────┐
             │                   │
        Mechanical             Vibration
          Energy                  │
             │                    ▼
             ▼              Vibration Sensor
      Energy Harvester            │
             │                    ▼
             ▼                 Cortex-M4
      Energy Storage               │
             │                    ▼
             └──────────────► Sensor Processing
```

## 12. Project Goal

The vibration sensor module demonstrates:

* STM32MP157
* Cortex-M4
* SPI/I2C
* GPIO interrupt
* FIFO acquisition
* Signal processing
* Event detection
* Sensor power gating
* Low-power operation
* Energy-aware scheduling
* Device Tree integration
* OpenAMP/RPMsg communication

## 13. Sensor Selection

The exact vibration sensor IC must be selected before final hardware
implementation.

The following information must be documented:

* Manufacturer
* Part number
* Interface
* Device address
* Supply voltage
* Accelerometer range
* Resolution
* Sampling rate
* Bandwidth
* FIFO size
* Operating current
* Standby current
* Register map
* Interrupt behavior

