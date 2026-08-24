# Solar Energy Harvesting

## 1. Overview

Solar harvesting is the primary energy source considered for the
STM32MP157 Energy-Aware Industrial Sensor Node.

```text
        Sunlight
           │
           ▼
      Solar Panel
           │
           ▼
   Energy Harvesting PMIC
           │
           ├──────────────► System Power
           │
           ▼
     Energy Storage
     Supercapacitor
           │
           ▼
       STM32MP157
           │
           ├── Cortex-M4
           │
           └── Cortex-A7
````

## 2. Main Components

```text
Solar Panel
    │
    ▼
Input Protection
    │
    ▼
Energy Harvesting PMIC
    │
    ▼
Storage Element
    │
    ├── Supercapacitor
    └── Rechargeable battery
    │
    ▼
Regulator / Power Tree
    │
    ▼
STM32MP157
```

## 3. Operating Principle

The solar panel converts light energy into electrical energy.

The harvesting PMIC:

* Accepts the panel output
* Performs power-point management
* Charges the storage element
* Provides regulated system power
* Disconnects the load when energy is insufficient

## 4. Energy Budget

The system must satisfy:

```text
Average harvested energy
        >
Average system energy consumption
```

Example:

```text
Harvested:
    25 mJ/hour

Consumed:
    15 mJ/hour

Energy margin:
    10 mJ/hour
```

The actual values must be measured on the final hardware.

## 5. Duty Cycling

The Cortex-M4 should operate periodically:

```text
        Sleep
          │
          ▼
       Wake M4
          │
          ▼
     Read Sensor
          │
          ▼
     Process Data
          │
          ▼
     Store/Transmit
          │
          ▼
        Sleep
```

The Cortex-A7 should remain suspended whenever high-level processing is
not required.

## 6. Solar Availability

Solar input varies with:

* Time of day
* Weather
* Panel orientation
* Temperature
* Indoor/outdoor conditions
* Shading

Therefore, the system requires energy-aware scheduling.

```text
High Energy
    │
    ├── Sensor sampling
    ├── Processing
    └── Communication
    │
    ▼
Low Energy
    │
    ├── Reduce sampling
    ├── Disable radio
    └── Deep sleep
```

## 7. Recommended Architecture

```text
Solar Panel
     │
     ▼
Harvesting PMIC
     │
     ▼
Supercapacitor
     │
     ▼
Power Management
     │
     ▼
STM32MP157
     │
     ├── M4 → Sensor
     │
     └── A7 → Linux
```

## 8. Prototype Consideration

The STM32MP157 Discovery Kit is useful for software and power-management
experiments, but the complete development board is not designed to operate
as a sub-1 µA solar sensor node.

A production implementation requires a custom low-leakage PCB.

````

