# Temperature Sensor

## 1. Overview

The temperature sensor subsystem measures the temperature of the
industrial environment and provides the measurement to the
STM32MP157 Cortex-M4.

The Cortex-M4 performs sensor acquisition, processing and low-power
control. The Cortex-A7/Linux subsystem can perform logging, analytics,
visualization and communication.

## 2. System Architecture

```text
                    STM32MP157
                         │
             ┌───────────┴───────────┐
             │                       │
         Cortex-A7               Cortex-M4
             │                       │
           Linux               Sensor Manager
             │                       │
             │                       ▼
             │                Temperature Sensor
             │                       │
             │                    I2C/SPI
             │                       │
             └────── RPMsg ──────────┘
````

## 3. Sensor Responsibilities

The temperature sensor subsystem provides:

* Sensor initialization
* Sensor configuration
* Temperature measurement
* Raw-data acquisition
* Temperature conversion
* Calibration
* Error detection
* Sensor power control
* Low-power operation
* Optional interrupt handling

## 4. Measurement Flow

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
        Start Measurement
                 │
                 ▼
        Wait for Conversion
                 │
                 ▼
        Read Raw Temperature
                 │
                 ▼
        Convert Raw Data
                 │
                 ▼
        Apply Calibration
                 │
                 ▼
        Validate Measurement
                 │
                 ▼
        Store / Send Result
                 │
                 ▼
        Disable Sensor
                 │
                 ▼
             Low Power
```

## 5. Low-Power Strategy

The temperature sensor should be active only when a measurement is
required.

```text
                 SLEEP
                   │
                   ▼
                Wake M4
                   │
                   ▼
          Sensor Power ON
                   │
                   ▼
          Start Measurement
                   │
                   ▼
          Wait for Conversion
                   │
                   ▼
          Read Temperature
                   │
                   ▼
          Process Temperature
                   │
                   ▼
          Sensor Power OFF
                   │
                   ▼
                 SLEEP
```

This duty-cycled operation reduces average energy consumption.

## 6. Cortex-M4 Role

The Cortex-M4 handles:

```text
Temperature Sensor
        │
        ▼
   Sensor Driver
        │
        ▼
   Sensor Manager
        │
        ▼
 Raw Temperature
        │
        ▼
 Calibration
        │
        ▼
 Temperature Value
        │
        ▼
 Threshold Detection
        │
        ▼
      RPMsg
        │
        ▼
    Cortex-A7
```

## 7. Cortex-A7 Role

Linux/Cortex-A7 can perform:

* Temperature logging
* Database storage
* Network communication
* Cloud communication
* User interface
* Analytics
* Configuration
* Alarm reporting

The A7 does not need to remain active for every temperature
measurement.

## 8. Temperature Monitoring

A typical monitoring cycle is:

```text
Temperature Sample
        │
        ▼
Compare With Threshold
        │
    ┌───┴────┐
    │        │
 Normal    Abnormal
    │        │
    ▼        ▼
 Sleep    Generate Event
             │
             ▼
           Wake A7
```

## 9. Industrial Applications

Possible applications include:

* Motor temperature monitoring
* Machine temperature monitoring
* Industrial equipment
* Battery temperature monitoring
* Power-supply monitoring
* Pipeline monitoring
* Environmental monitoring
* Remote sensor nodes

## 10. Energy-Harvesting Integration

```text
Solar / Thermal / Kinetic
          │
          ▼
 Energy Harvesting PMIC
          │
          ▼
      Energy Storage
          │
          ▼
     Power Management
          │
          ▼
      STM32MP157
          │
          ▼
       Cortex-M4
          │
          ▼
   Temperature Sensor
```

## 11. Event-Based Operation

The temperature sensor can be used with threshold detection.

```text
             Temperature
                  │
                  ▼
             Cortex-M4
                  │
                  ▼
           Compare Threshold
                  │
          ┌───────┴───────┐
          │               │
       Normal           Alarm
          │               │
          ▼               ▼
        Sleep        Wake Cortex-A7
                          │
                          ▼
                    Linux Application
                          │
                          ▼
                    Log / Network
```

## 12. Project Goal

The temperature sensor module demonstrates:

* STM32MP157
* Cortex-M4 sensor acquisition
* I2C/SPI communication
* GPIO interrupt handling
* Sensor power gating
* Low-power measurement
* Energy-aware scheduling
* Device Tree integration
* OpenAMP/RPMsg communication

## 13. Sensor Selection

The exact temperature sensor IC must be selected before final hardware
implementation.

The following must be documented after selection:

* Manufacturer
* Part number
* Interface
* I2C address
* Supply voltage
* Temperature range
* Accuracy
* Resolution
* Conversion time
* Operating current
* Standby current
* Register map
* Interrupt behavior

