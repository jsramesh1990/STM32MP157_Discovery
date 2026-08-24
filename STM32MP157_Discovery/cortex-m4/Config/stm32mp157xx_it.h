/*
 * stm32mp157xx_it.h
 *
 * STM32MP157 Cortex-M4 interrupt declarations.
 *
 * Energy-Aware Industrial Sensor
 */

#ifndef STM32MP157XX_IT_H
#define STM32MP157XX_IT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32mp1xx_hal.h"

/*
 * --------------------------------------------------------------------------
 * Cortex-M4 Core Interrupt Handlers
 * --------------------------------------------------------------------------
 */

/**
 * @brief Non-maskable interrupt handler.
 */
void NMI_Handler(void);

/**
 * @brief Hard fault interrupt handler.
 */
void HardFault_Handler(void);

/**
 * @brief Memory management fault handler.
 */
void MemManage_Handler(void);

/**
 * @brief Bus fault handler.
 */
void BusFault_Handler(void);

/**
 * @brief Usage fault handler.
 */
void UsageFault_Handler(void);

/**
 * @brief Debug monitor handler.
 */
void DebugMon_Handler(void);

/**
 * @brief Supervisor call handler.
 */
void SVC_Handler(void);

/**
 * @brief PendSV handler.
 */
void PendSV_Handler(void);

/**
 * @brief SysTick handler.
 */
void SysTick_Handler(void);

/*
 * --------------------------------------------------------------------------
 * Peripheral Interrupt Handlers
 * --------------------------------------------------------------------------
 */

/*
 * UART
 */
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);

/*
 * I2C
 */
void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);

void I2C2_EV_IRQHandler(void);
void I2C2_ER_IRQHandler(void);

void I2C3_EV_IRQHandler(void);
void I2C3_ER_IRQHandler(void);

/*
 * SPI
 */
void SPI1_IRQHandler(void);
void SPI2_IRQHandler(void);
void SPI3_IRQHandler(void);

/*
 * Timers
 */
void TIM1_UP_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);

/*
 * RTC
 */
void RTC_WKUP_IRQHandler(void);
void RTC_ALARM_IRQHandler(void);

/*
 * ADC
 */
void ADC1_IRQHandler(void);
void ADC2_IRQHandler(void);

/*
 * GPIO / External interrupts
 */
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);

void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

/*
 * --------------------------------------------------------------------------
 * Project-specific interrupt handlers
 * --------------------------------------------------------------------------
 */

/*
 * Sensor interrupt.
 *
 * Example:
 *   Accelerometer data ready
 *   Vibration threshold
 *   Temperature alarm
 */
void SENSOR_EXTI_IRQHandler(void);

/*
 * Energy-harvesting / power-good interrupt.
 */
void ENERGY_WAKEUP_IRQHandler(void);

/*
 * RPMsg/OpenAMP interrupt/event handler.
 */
void RPMSG_IRQHandler(void);

/*
 * Low-power wake-up handler.
 */
void LOW_POWER_WAKEUP_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* STM32MP157XX_IT_H */
