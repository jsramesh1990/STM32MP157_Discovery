The purpose of each test group is different:

boot/
  │
  └── Verify STM32MP157 boot chain
       ROM → TF-A → U-Boot → Linux

energy/
  │
  └── Verify energy source / power availability
       Solar / Thermal / Kinetic
              ↓
       PMIC / Storage
              ↓
       System

low-power/
  │
  └── Verify
       Run
        ↓
       Stop
        ↓
       LP-Stop
        ↓
       LPLV-Stop
        ↓
       Standby

rpmsg/
  │
  └── Verify
       Cortex-A7 Linux
             ↕
           RPMsg
             ↕
       Cortex-M4

sensor/
  │
  └── Verify
       Temperature
       Pressure
       Vibration

wakeup/
  │
  └── Verify
       RTC
       GPIO
       Sensor interrupt
       RPMsg/event


Each directory's README.md should explain what is being tested, prerequisites, commands, expected result, and failure troubleshooting.

The complete test architecture then becomes:

                         tests/
                           │
       ┌───────────────────┼────────────────────┐
       │                   │                    │
       ▼                   ▼                    ▼
     boot              rpmsg                  sensor
       │                   │                    │
       ▼                   ▼                    ▼
 Boot chain          A7 ↔ M4              Sensors
       │                   │                    │
       └───────────────────┼────────────────────┘
                           │
                 ┌─────────┴─────────┐
                 ▼                   ▼
              energy             low-power
                 │                   │
                 │                   ▼
                 │                suspend
                 │                   │
                 └─────────┬─────────┘
                           ▼
                         wakeup

And linux/scripts/ vs tests/ should not duplicate each other:

linux/scripts/
    power_test.sh
    sensor_test.sh
    suspend_test.sh
    wakeup_test.sh
          │
          └── Quick runtime tests on the target


tests/
    boot/
    energy/
    low-power/
    rpmsg/
    sensor/
    wakeup/
          │
          └── Structured validation/test suite

Finally, your top-level automation can run everything:

scripts/build_all.sh
        ↓
    Build project
        ↓
scripts/deploy_all.sh
        ↓
    Deploy to DK
        ↓
scripts/run_tests.sh
        ↓
       tests/
   ┌────┼────┬────┬────┬────┐
   ↓    ↓    ↓    ↓    ↓    ↓
 boot energy low  rpmsg sensor wakeup
              power
        ↓
scripts/collect_logs.sh

This gives the GitHub project a much more professional structure: firmware → device tree → hardware → Linux applications/services → runtime scripts → automated validation tests.

