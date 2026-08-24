The responsibilities are:

tools/
│
├── log-parser
│      │
│      └── Analyze logs collected from STM32MP157
│
├── power-measurement
│      │
│      └── Calculate voltage/current/power/energy
│
└── serial-monitor
       │
       └── Monitor UART console

The overall project flow becomes:

STM32MP157-DK
      │
      ├── UART ──────────────► serial-monitor
      │
      ├── System logs ───────► log-parser
      │
      └── Power analyzer ────► power-measurement
tools/log-parser/log_parser.py

This tool should parse logs such as:

Temperature : 31.5 C
Pressure    : 101.2 kPa
Vibration   : 0.42 g RMS
Status      : NORMAL


Run:

python3 log_parser.py sensor.log


tools/power-measurement/power_measurement.py

This should help calculate:

Voltage
Current
Power
Energy
Average power

would calculate approximately:

Voltage : 3.300000 V
Current : 0.000002000 A
Power   : 0.000006600 W
Power   : 0.006600 mW

This is particularly useful for your ultra-low-power investigation, but remember that the actual current must come from a real current measurement instrument; this Python tool only performs the calculations.

Run:

python3 serial_monitor.py /dev/ttyUSB0 115200


Your final tools directory therefore stays clean:

STM32MP157_Discovery/tools/
│
├── log-parser/
│   ├── README.md
│   └── log_parser.py
│
├── power-measurement/
│   ├── README.md
│   └── power_measurement.py
│
└── serial-monitor/
    ├── README.md
    └── serial_monitor.py

And the separation across the whole GitHub project is now:

cortex-m4/
    → Firmware

device-tree/
    → Hardware configuration

hardware/
    → Board + sensor + energy-harvesting documentation

linux/apps/
    → User-space applications

linux/services/
    → Background Linux services

linux/scripts/
    → Target-side runtime scripts

tests/
    → Structured validation

scripts/
    → Project-wide build/deploy/test automation

tools/
    → PC/developer diagnostic tools

That is the right separation for the STM32MP157 energy-harvesting sensor platform project.



