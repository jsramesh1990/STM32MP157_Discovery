The BSP directory contains Board Support Package components.

BSP/
│
├── Board initialization
├── LEDs
├── Buttons
├── Sensor interfaces
├── Power control
├── Clock configuration
└── Board-specific peripherals

The BSP layer is responsible for connecting the generic application software
with the STM32MP157 Discovery Kit hardware.

BSP Responsibilities

The BSP can provide APIs for:

GPIO
LEDs
Push buttons
I2C
SPI
UART
ADC
RTC
Timers
Sensor power control
External interrupt configuration
Board-specific hardware

Example architecture:

Application
     │
     ▼
Sensor Manager
     │
     ▼
BSP Sensor Driver
     │
     ▼
I2C / SPI / ADC
     │
     ▼
STM32MP157 Hardware
