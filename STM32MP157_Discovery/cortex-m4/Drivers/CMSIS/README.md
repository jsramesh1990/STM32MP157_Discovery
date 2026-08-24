The CMSIS directory contains the ARM/STM32 CMSIS dependencies required
by the Cortex-M4 firmware.

CMSIS provides the processor-level definitions required by the firmware,
including:

CMSIS
 │
 ├── Cortex-M4 core definitions
 ├── NVIC
 ├── SysTick
 ├── Interrupt definitions
 ├── SCB
 ├── MPU
 └── Compiler abstraction

The CMSIS layer is below the application and HAL layers.

3. Driver Architecture

The complete Cortex-M4 software stack is:

┌──────────────────────────────────────────┐
│              Application                 │
│                                          │
│  app_sensor.c                            │
│  app_power.c                             │
│  app_rpmsg.c                             │
└────────────────────┬─────────────────────┘
                     │
                     ▼
┌──────────────────────────────────────────┐
│            Manager Layer                 │
│                                          │
│  sensor_manager.c                        │
│  power_manager.c                         │
│  system_config.c                         │
└────────────────────┬─────────────────────┘
                     │
                     ▼
┌──────────────────────────────────────────┐
│               BSP Layer                  │
│                                          │
│  GPIO                                     │
│  I2C                                      │
│  SPI                                      │
│  UART                                     │
│  ADC                                      │
│  RTC                                      │
│  TIM                                      │
└────────────────────┬─────────────────────┘
                     │
                     ▼
┌──────────────────────────────────────────┐
│              STM32 HAL                   │
│                                          │
│  HAL_GPIO                                │
│  HAL_I2C                                  │
│  HAL_SPI                                  │
│  HAL_UART                                 │
│  HAL_ADC                                  │
│  HAL_RTC                                  │
│  HAL_TIM                                  │
└────────────────────┬─────────────────────┘
                     │
                     ▼
┌──────────────────────────────────────────┐
│                 CMSIS                    │
│                                          │
│  Cortex-M4                                │
│  NVIC                                     │
│  SysTick                                  │
│  SCB                                      │
└────────────────────┬─────────────────────┘
                     │
                     ▼
              STM32MP157 SoC
4. Sensor Driver Flow

Sensor data follows this path:

Sensor
  │
  ▼
I2C / SPI / ADC
  │
  ▼
BSP Driver
  │
  ▼
sensor_manager.c
  │
  ▼
app_sensor.c
  │
  ▼
Cortex-M4 Application

Example:

Temperature Sensor
        │
        │ I2C
        ▼
    I2C Driver
        │
        ▼
   BSP Sensor API
        │
        ▼
 Sensor Manager
        │
        ▼
 App Sensor
        │
        ▼
 Threshold Detection
        │
        ▼
 RPMsg
        │
        ▼
 Cortex-A7 / Linux
5. Power Driver Flow

Power management follows:

Energy Source
     │
     ▼
Energy Harvesting PMIC
     │
     ▼
Power Monitoring
     │
     ▼
BSP Power Driver
     │
     ▼
power_manager.c
     │
     ▼
app_power.c
     │
     ▼
Low-Power Mode

The power-management layer can control:

Sensor power
Peripheral power
GPIO-controlled regulators
Wake-up sources
RTC wake-up
Low-power transitions
Energy monitoring
6. Low-Power Architecture

The Cortex-M4 firmware is designed around duty cycling.

             ┌───────────────┐
             │   LOW POWER   │
             └───────┬───────┘
                     │
                     ▼
              Wake-up Event
                     │
                     ▼
             ┌───────────────┐
             │ Sensor Power  │
             │     ON        │
             └───────┬───────┘
                     │
                     ▼
             ┌───────────────┐
             │ Read Sensor   │
             └───────┬───────┘
                     │
                     ▼
             ┌───────────────┐
             │ Process Data  │
             └───────┬───────┘
                     │
                     ▼
             ┌───────────────┐
             │ Event?        │
             └───┬───────┬───┘
                 │       │
                NO      YES
                 │       │
                 │       ▼
                 │   RPMsg Event
                 │       │
                 │       ▼
                 │   Cortex-A7
                 │
                 ▼
             Sensor OFF
                 │
                 ▼
             Low Power
7. CMSIS and Interrupts

CMSIS provides the Cortex-M4 processor abstraction.

Typical interrupt flow:

Hardware Event
      │
      ▼
NVIC
      │
      ▼
Interrupt Vector
      │
      ▼
stm32mp157xx_it.c
      │
      ▼
HAL Handler
      │
      ▼
Application Callback
      │
      ▼
Sensor / Power Manager

Examples include:

RTC Wake-up
GPIO Interrupt
I2C Interrupt
SPI Interrupt
UART Interrupt
Timer Interrupt
ADC Interrupt
8. Driver Design Rules

The driver layer should follow these rules:

Hardware-specific code stays in the driver/BSP layer.
Application code should not directly access registers.
Sensor drivers should expose simple APIs.
Power drivers should provide explicit ON/OFF control.
Interrupt handlers should remain short.
Long processing should be performed outside interrupt context.
Sensor power should be disabled when the sensor is not required.
Debug peripherals should be disabled in the final low-power build.
Every driver should report errors to the manager layer.
Low-power behavior must be validated by measuring actual board current.
9. Example Driver API

A sensor BSP driver can expose:

int BSP_Sensor_Init(void);


int BSP_Sensor_DeInit(void);


int BSP_Sensor_PowerOn(void);


int BSP_Sensor_PowerOff(void);


int BSP_Sensor_Read(sensor_data_t *data);


int BSP_Sensor_EnableInterrupt(void);


int BSP_Sensor_DisableInterrupt(void);

The application should not need to know whether the sensor uses:

I2C
SPI
ADC
GPIO
10. Power Driver API

Example:

int BSP_Power_Init(void);


int BSP_Power_EnableSensor(void);


int BSP_Power_DisableSensor(void);


int BSP_Power_EnablePeripheral(void);


int BSP_Power_DisablePeripheral(void);


int BSP_Power_SetWakeupSource(void);


int BSP_Power_EnterLowPower(void);


int BSP_Power_Wakeup(void);
11. RPMsg Driver Relationship

RPMsg is used for communication between:

Cortex-A7
     │
     │ Linux
     │
     ▼
 OpenAMP / RPMsg
     │
     ▼
 Cortex-M4
     │
     ▼
 Application

The Cortex-M4 can send:

Sensor data
Sensor events
Power status
Wake-up events
Error information

The Cortex-A7 can send:

Start sensor
Stop sensor
Read sensor
Enter low power
Wake up
Get status
Reset
12. Energy-Harvesting System

The final product architecture is:

       Solar / Thermal / Kinetic
                  │
                  ▼
        Energy Harvesting PMIC
                  │
                  ▼
        Supercapacitor / Storage
                  │
                  ▼
            Power Control
                  │
                  ▼
             STM32MP157
                  │
          ┌───────┴────────┐
          │                │
       Cortex-A7        Cortex-M4
          │                │
       Linux          Sensor Control
          │                │
          └───────┬────────┘
                  │
                  ▼
                Sensors
13. Development vs Production

The STM32MP157 Discovery Kit is primarily used for development and
validation.

Development
     │
     ▼
STM32MP157 Discovery Kit
     │
     ├── Firmware development
     ├── Sensor testing
     ├── RPMsg testing
     ├── Low-power experiments
     └── Power measurements

A production energy-harvesting sensor should use:

Custom STM32MP157 PCB
       │
       ├── Low-leakage regulators
       ├── Energy-harvesting PMIC
       ├── Supercapacitor
       ├── Load switches
       ├── Low-power sensors
       └── Optimized PCB
14. Important Low-Power Note

The Drivers directory itself does not guarantee sub-1 µA operation.

System-level current depends on:

STM32MP157
   +
DDR
   +
PMIC
   +
Sensors
   +
Regulators
   +
GPIO leakage
   +
Board leakage
   +
Debug interfaces
   +
External peripherals

Therefore, the project should measure:

Active Current
      ↓
Sensor Current
      ↓
Idle Current
      ↓
Stop Current
      ↓
Standby Current
      ↓
Average Current

The final target should be defined as an energy budget, not simply a
single CPU current number.

15. Driver Development Strategy

Implement the drivers in this order:

1. GPIO
      ↓
2. UART Debug
      ↓
3. I2C
      ↓
4. SPI
      ↓
5. ADC
      ↓
6. RTC
      ↓
7. Sensor Driver
      ↓
8. Power Driver
      ↓
9. Interrupts
      ↓
10. RPMsg/OpenAMP
      ↓
11. Low-Power Modes
      ↓
12. Energy Monitoring
16. Final Driver Layer

The final project should maintain this separation:

Application
     │
     ▼
Managers
     │
     ▼
BSP
     │
     ▼
STM32 HAL
     │
     ▼
CMSIS
     │
     ▼
STM32MP157 Cortex-M4

This architecture makes the firmware easier to test, maintain and migrate
from the Discovery Kit to a custom energy-harvesting STM32MP157 board.



Your `Drivers` directory is therefore:


```text
STM32MP157_Discovery/
└── cortex-m4/
    └── Drivers/
        ├── BSP/
        ├── CMSIS/
        └── README.md

No additional files are needed at this level. The actual STM32 HAL/CMSIS source trees can be supplied by the STM32CubeMP1/BSP dependency rather than duplicating them into your GitHub application repository.
