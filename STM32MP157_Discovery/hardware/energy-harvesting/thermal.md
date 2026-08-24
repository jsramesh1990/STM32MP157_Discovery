# Thermal Energy Harvesting

## 1. Overview

Thermal harvesting converts a temperature difference into electrical
energy.

```text
       Heat Source
           │
           ▼
   Thermoelectric Generator
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
````

## 2. Thermoelectric Generator

A thermoelectric generator (TEG) produces voltage when there is a
temperature difference between its two sides.

```text
 Hot Side
   │
   ▼
┌───────────────┐
│      TEG      │
└───────────────┘
   │
   ▼
Cold Side

Temperature Difference
          ↓
Electrical Energy
```

## 3. Energy Harvesting Chain

```text
Temperature Difference
          │
          ▼
          TEG
          │
          ▼
  Low-Voltage Harvester
          │
          ▼
       Storage
          │
          ▼
     Voltage Regulator
          │
          ▼
      STM32MP157
```

## 4. Important Parameters

The design depends on:

* Temperature difference
* TEG output voltage
* TEG output current
* Harvester efficiency
* Storage capacity
* STM32MP157 average power
* Sensor power
* Communication power

## 5. Low-Power Strategy

Thermal energy may be available continuously but at a very low rate.

Therefore:

```text
TEG
 │
 ▼
Continuous small energy input
 │
 ▼
Storage
 │
 ▼
Periodic sensor operation
```

The system should accumulate energy before performing expensive operations.

## 6. Energy-Aware Scheduling

```text
Energy Available?
       │
   ┌───┴───┐
   │       │
  YES      NO
   │       │
   ▼       ▼
Measure   Sleep
Sensor      │
   │        │
   ▼        │
Process     │
   │        │
   └────────┘
```

## 7. Use Case

Suitable applications include:

* Industrial machinery
* Engine monitoring
* Heat pipes
* Boilers
* Industrial pipelines
* Factory equipment

The heat source can provide continuous energy while the sensor monitors
the equipment periodically.

## 8. Prototype

The Discovery Kit can be used to develop:

* Sensor firmware
* Energy-aware scheduling
* M4 low-power operation
* Wake-up handling
* Linux/M4 communication

The actual TEG power-management hardware should be evaluated separately
because the Discovery Kit itself is not an energy-harvesting evaluation
board.

````

