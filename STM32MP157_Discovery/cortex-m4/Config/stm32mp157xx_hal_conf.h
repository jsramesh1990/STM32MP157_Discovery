/*
 * stm32mp157xx_hal_conf.h
 *
 * STM32MP157 HAL configuration
 *
 * Energy-Aware Industrial Sensor
 * Cortex-M4 firmware
 */

#ifndef STM32MP157XX_HAL_CONF_H
#define STM32MP157XX_HAL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * --------------------------------------------------------------------------
 * Module Selection
 * --------------------------------------------------------------------------
 */

/*
 * Common HAL module.
 */
#define HAL_MODULE_ENABLED

/*
 * Enable only the peripherals required by this project.
 */

#define HAL_GPIO_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED

/*
 * Sensor interfaces.
 *
 * Enable these when the corresponding hardware is used.
 */
#define HAL_I2C_MODULE_ENABLED
#define HAL_SPI_MODULE_ENABLED

/*
 * UART is useful for debugging and development.
 */
#define HAL_UART_MODULE_ENABLED

/*
 * Timers can be used for periodic sensor sampling.
 */
#define HAL_TIM_MODULE_ENABLED

/*
 * RTC is important for low-power wake-up.
 */
#define HAL_RTC_MODULE_ENABLED

/*
 * ADC can be used for:
 *
 * - Energy measurement
 * - Battery/supercapacitor voltage
 * - Analog sensors
 */
#define HAL_ADC_MODULE_ENABLED

/*
 * --------------------------------------------------------------------------
 * Include STM32MP1 HAL modules
 * --------------------------------------------------------------------------
 */

#ifdef HAL_RCC_MODULE_ENABLED
#include "stm32mp1xx_hal_rcc.h"
#endif

#ifdef HAL_GPIO_MODULE_ENABLED
#include "stm32mp1xx_hal_gpio.h"
#endif

#ifdef HAL_CORTEX_MODULE_ENABLED
#include "stm32mp1xx_hal_cortex.h"
#endif

#ifdef HAL_PWR_MODULE_ENABLED
#include "stm32mp1xx_hal_pwr.h"
#endif

#ifdef HAL_I2C_MODULE_ENABLED
#include "stm32mp1xx_hal_i2c.h"
#endif

#ifdef HAL_SPI_MODULE_ENABLED
#include "stm32mp1xx_hal_spi.h"
#endif

#ifdef HAL_UART_MODULE_ENABLED
#include "stm32mp1xx_hal_uart.h"
#endif

#ifdef HAL_TIM_MODULE_ENABLED
#include "stm32mp1xx_hal_tim.h"
#endif

#ifdef HAL_RTC_MODULE_ENABLED
#include "stm32mp1xx_hal_rtc.h"
#endif

#ifdef HAL_ADC_MODULE_ENABLED
#include "stm32mp1xx_hal_adc.h"
#endif

/*
 * --------------------------------------------------------------------------
 * Oscillator Configuration
 * --------------------------------------------------------------------------
 */

/*
 * These values must match the actual board/clock configuration.
 *
 * Do not blindly change these values.
 * They should correspond to the STM32MP157 clock tree generated
 * by STM32CubeMP1 or your selected BSP configuration.
 */

#define HSE_VALUE              24000000U
#define HSE_STARTUP_TIMEOUT    100U

#define HSI_VALUE              64000000U
#define LSI_VALUE              32000U
#define LSE_VALUE              32768U

#define HSI_STARTUP_TIMEOUT    100U
#define LSI_STARTUP_TIMEOUT    100U
#define LSE_STARTUP_TIMEOUT    5000U

/*
 * --------------------------------------------------------------------------
 * System Configuration
 * --------------------------------------------------------------------------
 */

#define VDD_VALUE              3300U

#define TICK_INT_PRIORITY      0U

#define USE_RTOS               0U

#define PREFETCH_ENABLE        1U

/*
 * --------------------------------------------------------------------------
 * Assert Configuration
 * --------------------------------------------------------------------------
 */

/*
 * Enable this during development to detect invalid HAL parameters.
 *
 * #define USE_FULL_ASSERT 1U
 */

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line);

#endif

/*
 * --------------------------------------------------------------------------
 * HAL Error Handler
 * --------------------------------------------------------------------------
 */

#define HAL_MAX_DELAY          0xFFFFFFFFU

/*
 * --------------------------------------------------------------------------
 * Low Power Configuration
 * --------------------------------------------------------------------------
 */

/*
 * Project-specific low-power configuration.
 *
 * These values are used by the application layer to determine
 * when aggressive power saving should be requested.
 */

#define PROJECT_LOW_POWER_ENABLED       1U

#define PROJECT_RTC_WAKEUP_ENABLED      1U

#define PROJECT_GPIO_WAKEUP_ENABLED     1U

#define PROJECT_SENSOR_POWER_SWITCH      1U

/*
 * --------------------------------------------------------------------------
 * Sensor Configuration
 * --------------------------------------------------------------------------
 */

#define PROJECT_I2C_SENSOR_ENABLED       1U

#define PROJECT_SPI_SENSOR_ENABLED       1U

#define PROJECT_ADC_SENSOR_ENABLED       1U

/*
 * --------------------------------------------------------------------------
 * Debug Configuration
 * --------------------------------------------------------------------------
 */

/*
 * Keep UART enabled during development.
 *
 * For the final ultra-low-power design, disable unnecessary
 * debug interfaces/peripherals.
 */

#define PROJECT_DEBUG_UART_ENABLED       1U

/*
 * --------------------------------------------------------------------------
 * Energy Harvesting Configuration
 * --------------------------------------------------------------------------
 */

/*
 * These are application-level definitions.
 *
 * They are NOT STM32MP157 electrical specifications.
 */

#define ENERGY_HARVESTING_ENABLED        1U

#define ENERGY_LOW_THRESHOLD_PERCENT     20U

#define ENERGY_CRITICAL_THRESHOLD        10U

/*
 * --------------------------------------------------------------------------
 * RPMsg / OpenAMP
 * --------------------------------------------------------------------------
 */

#define PROJECT_RPMSG_ENABLED             1U

/*
 * --------------------------------------------------------------------------
 * Common HAL Configuration
 * --------------------------------------------------------------------------
 */

#define USE_HAL_DRIVER

/*
 * --------------------------------------------------------------------------
 * Macro Compatibility
 * --------------------------------------------------------------------------
 */

#ifndef UNUSED
#define UNUSED(x) ((void)(x))
#endif

/*
 * --------------------------------------------------------------------------
 * C++ Compatibility
 * --------------------------------------------------------------------------
 */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP157XX_HAL_CONF_H */
