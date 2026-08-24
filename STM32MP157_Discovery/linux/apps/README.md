Yes. Then your `linux/apps/` should contain **exactly these 4 application directories**:

```text
STM32MP157_Discovery/
└── linux/
    └── apps/
        ├── power-manager/
        ├── rpmsg-test/
        ├── sensor-manager/
        └── sensor-monitor/
```

I recommend designing them like this:

```text
linux/apps/
│
├── power-manager/
│   ├── README.md
│   ├── main.c
│   ├── power_manager.c
│   └── power_manager.h
│
├── rpmsg-test/
│   ├── README.md
│   ├── main.c
│   ├── rpmsg_test.c
│   └── rpmsg_test.h
│
├── sensor-manager/
│   ├── README.md
│   ├── main.c
│   ├── sensor_manager.c
│   └── sensor_manager.h
│
└── sensor-monitor/
    ├── README.md
    ├── main.c
    ├── sensor_monitor.c
    └── sensor_monitor.h
```

The four applications have different responsibilities.

```text
                         Linux / Cortex-A7
                                │
             ┌──────────────────┼──────────────────┐
             │                  │                  │
             ▼                  ▼                  ▼
      sensor-manager       sensor-monitor     power-manager
             │                  │                  │
             │                  │                  │
             │                  ▼                  │
             │            Display / Logging        │
             │                                     │
             └──────────────┬──────────────────────┘
                            │
                            ▼
                          RPMsg
                            │
                            ▼
                     Cortex-M4 Firmware
                            │
             ┌──────────────┼──────────────┐
             ▼              ▼              ▼
        Temperature      Pressure       Vibration
```

`rpmsg-test` is separate because it is a **development and validation application**, not part of the normal production data path.

### `power-manager`

Responsible for Linux-side power management:

```text
power-manager
      │
      ├── Read power state
      ├── Read battery/supercap status
      ├── Monitor harvested energy
      ├── Request low-power state
      ├── Control sensor activity
      └── Report power status
```

Example:

```text
$ ./power-manager status

Power Source : Solar
Storage      : Supercapacitor
Voltage      : 4.82 V
System State : ACTIVE
Sensor State : ENABLED
```

### `rpmsg-test`

Used to verify Cortex-A7 ↔ Cortex-M4 communication:

```text
Cortex-A7
    │
    ▼
rpmsg-test
    │
    ▼
RPMsg
    │
    ▼
Cortex-M4
    │
    ▼
Response
```

Example:

```text
A7 → M4 : SENSOR_READ
M4 → A7 : TEMP=31.4
A7 → M4 : VIBRATION_READ
M4 → A7 : RMS=0.42
```

This application is especially useful during development before building the complete sensor application.

### `sensor-manager`

This is the main Linux-side sensor coordination application.

```text
                 sensor-manager
                       │
          ┌────────────┼────────────┐
          ▼            ▼            ▼
     Temperature    Pressure     Vibration
          │            │            │
          └────────────┼────────────┘
                       ▼
                     RPMsg
                       │
                       ▼
                    Cortex-M4
```

Responsibilities:

```text
Sensor discovery
Sensor configuration
Measurement requests
Receive sensor data
Validate data
Sensor status
Threshold configuration
Error handling
RPMsg communication
```

### `sensor-monitor`

This is the user-facing monitoring application.

```text
                  sensor-monitor
                         │
              ┌──────────┼──────────┐
              ▼          ▼          ▼
         Temperature   Pressure   Vibration
              │          │          │
              └──────────┼──────────┘
                         ▼
                       Display
                         │
                         ▼
                       Logging
```

Example output:

```text
====================================
 STM32MP157 ENERGY SENSOR MONITOR
====================================

Temperature : 31.6 °C
Pressure    : 101.3 kPa
Vibration   : 0.42 g RMS

Energy
------------------------------------
Source      : SOLAR
Storage     : SUPERCAP
Voltage     : 4.82 V

System
------------------------------------
Cortex-M4   : ACTIVE
Sensors     : ACTIVE
RPMsg       : CONNECTED

Status      : NORMAL
====================================
```

The important architecture is:

```text
             Linux Applications
                    │
       ┌────────────┼────────────┐
       │            │            │
       ▼            ▼            ▼
 sensor-manager sensor-monitor power-manager
       │            │            │
       └──────┬─────┴────────────┘
              │
              ▼
           RPMsg
              │
              ▼
        Cortex-M4
              │
       ┌──────┼──────┐
       ▼      ▼      ▼
    Temp   Pressure Vibration
```

And `rpmsg-test` sits outside the normal production flow:

```text
rpmsg-test
    │
    ▼
Development / Debugging
    │
    ▼
RPMsg
    │
    ▼
Cortex-M4
```

So your current directory is correctly:

```text
STM32MP157_Discovery/linux/apps/
├── power-manager/
├── rpmsg-test/
├── sensor-manager/
└── sensor-monitor/
```

This structure also matches the earlier `cortex-m4/` design: **M4 handles real-time/low-power sensor work, while Linux handles coordination, monitoring, power policy, logging and communication.**

