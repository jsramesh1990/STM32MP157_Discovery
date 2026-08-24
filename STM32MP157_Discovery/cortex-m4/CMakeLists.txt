cmake_minimum_required(VERSION 3.20)

project(STM32MP157_M4
        VERSION 1.0.0
        LANGUAGES C ASM)

# ============================================================================
# STM32MP157 Cortex-M4
# Energy-Aware Industrial Sensor Node
# ============================================================================

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ----------------------------------------------------------------------------
# Cross compiler
# ----------------------------------------------------------------------------

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_SIZE arm-none-eabi-size)

# ----------------------------------------------------------------------------
# CPU configuration
# ----------------------------------------------------------------------------

set(CPU_FLAGS
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

# ----------------------------------------------------------------------------
# Compile definitions
# ----------------------------------------------------------------------------

add_compile_definitions(
    STM32MP157Cxx
    USE_HAL_DRIVER
    PROJECT_ENERGY_HARVESTING
    PROJECT_LOW_POWER
    PROJECT_RPMSG
)

# ----------------------------------------------------------------------------
# Include directories
# ----------------------------------------------------------------------------

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/BSP
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32MP1xx/Include
)

# ----------------------------------------------------------------------------
# Core sources
# ----------------------------------------------------------------------------

set(CORE_SOURCES

    Core/Src/main.c

    Core/Src/app_sensor.c
    Core/Src/app_power.c
    Core/Src/app_rpmsg.c

    Core/Src/sensor_manager.c
    Core/Src/power_manager.c
    Core/Src/system_config.c
)

# ----------------------------------------------------------------------------
# HAL sources
# ----------------------------------------------------------------------------

file(GLOB HAL_SOURCES
    Drivers/STM32MP1xx_HAL_Driver/Src/*.c
)

# ----------------------------------------------------------------------------
# CMSIS/device sources
# ----------------------------------------------------------------------------

file(GLOB CMSIS_SOURCES
    Drivers/CMSIS/Device/ST/STM32MP1xx/Source/*.c
)

# ----------------------------------------------------------------------------
# OpenAMP
# ----------------------------------------------------------------------------

file(GLOB OPENAMP_SOURCES
    Middlewares/OpenAMP/*.c
)

# ----------------------------------------------------------------------------
# Startup
# ----------------------------------------------------------------------------

file(GLOB STARTUP_SOURCES
    Drivers/CMSIS/Device/ST/STM32MP1xx/Source/Templates/gcc/*.s
)

# ----------------------------------------------------------------------------
# Executable
# ----------------------------------------------------------------------------

add_executable(${PROJECT_NAME}.elf

    ${CORE_SOURCES}

    ${HAL_SOURCES}

    ${CMSIS_SOURCES}

    ${OPENAMP_SOURCES}

    ${STARTUP_SOURCES}
)

# ----------------------------------------------------------------------------
# Compiler options
# ----------------------------------------------------------------------------

target_compile_options(${PROJECT_NAME}.elf PRIVATE

    ${CPU_FLAGS}

    -ffunction-sections
    -fdata-sections
    -fno-common

    -Wall
    -Wextra

    -O2
    -g3
)

# ----------------------------------------------------------------------------
# Linker
# ----------------------------------------------------------------------------

target_link_options(${PROJECT_NAME}.elf PRIVATE

    ${CPU_FLAGS}

    -T${CMAKE_CURRENT_SOURCE_DIR}/linker/STM32MP157_M4.ld

    -Wl,--gc-sections

    -Wl,-Map=${PROJECT_NAME}.map

    --specs=nano.specs
    --specs=nosys.specs
)

# ----------------------------------------------------------------------------
# Generate binary
# ----------------------------------------------------------------------------

add_custom_command(
    TARGET ${PROJECT_NAME}.elf
    POST_BUILD

    COMMAND ${CMAKE_OBJCOPY}
            -O binary
            ${PROJECT_NAME}.elf
            ${PROJECT_NAME}.bin

    COMMENT "Generating Cortex-M4 binary"
)

# ----------------------------------------------------------------------------
# Generate HEX
# ----------------------------------------------------------------------------

add_custom_command(
    TARGET ${PROJECT_NAME}.elf
    POST_BUILD

    COMMAND ${CMAKE_OBJCOPY}
            -O ihex
            ${PROJECT_NAME}.elf
            ${PROJECT_NAME}.hex

    COMMENT "Generating Cortex-M4 HEX"
)

# ----------------------------------------------------------------------------
# Display memory usage
# ----------------------------------------------------------------------------

add_custom_command(
    TARGET ${PROJECT_NAME}.elf
    POST_BUILD

    COMMAND ${CMAKE_SIZE}
            ${PROJECT_NAME}.elf

    COMMENT "Cortex-M4 memory usage"
)
