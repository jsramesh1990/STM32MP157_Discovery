# ============================================================================
# STM32MP157 Cortex-M4 Makefile
# ============================================================================
#
# Project:
#   Energy-Aware Industrial Sensor Node
#
# Target:
#   STM32MP157 Cortex-M4
#
# Build:
#   make
#
# Clean:
#   make clean
#
# Debug:
#   make debug
#
# Release:
#   make release
#
# ============================================================================

PROJECT      := STM32MP157_M4
BUILD_DIR    := build
OUTPUT_DIR   := $(BUILD_DIR)/output

TARGET       := $(OUTPUT_DIR)/$(PROJECT)

# ----------------------------------------------------------------------------
# Toolchain
# ----------------------------------------------------------------------------

CROSS_COMPILE ?= arm-none-eabi-

CC      := $(CROSS_COMPILE)gcc
CXX     := $(CROSS_COMPILE)g++
AS      := $(CROSS_COMPILE)gcc
AR      := $(CROSS_COMPILE)ar
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump
SIZE    := $(CROSS_COMPILE)size

# ----------------------------------------------------------------------------
# CPU
# ----------------------------------------------------------------------------

CPU       := cortex-m4
FPU       := fpv4-sp-d16
FLOAT_ABI := hard

CPU_FLAGS := -mcpu=$(CPU) \
             -mthumb \
             -mfpu=$(FPU) \
             -mfloat-abi=$(FLOAT_ABI)

# ----------------------------------------------------------------------------
# Project definitions
# ----------------------------------------------------------------------------

DEFINES := \
	-DSTM32MP157Cxx \
	-DUSE_HAL_DRIVER \
	-DPROJECT_ENERGY_HARVESTING \
	-DPROJECT_LOW_POWER \
	-DPROJECT_RPMSG

# ----------------------------------------------------------------------------
# Include directories
# ----------------------------------------------------------------------------

INCLUDES := \
	-IConfig \
	-ICore/Inc \
	-IDrivers/BSP \
	-IDrivers/CMSIS/Include \
	-IDrivers/CMSIS/Device/ST/STM32MP1xx/Include

# ----------------------------------------------------------------------------
# Compiler flags
# ----------------------------------------------------------------------------

COMMON_FLAGS := \
	$(CPU_FLAGS) \
	-ffunction-sections \
	-fdata-sections \
	-fno-common \
	-fmessage-length=0 \
	-Wall \
	-Wextra

CFLAGS := $(COMMON_FLAGS) \
	-std=gnu11 \
	-O2 \
	-g3 \
	$(DEFINES) \
	$(INCLUDES)

ASFLAGS := $(CPU_FLAGS) \
	-g3 \
	$(DEFINES) \
	$(INCLUDES)

LDFLAGS := \
	$(CPU_FLAGS) \
	-Tlinker/STM32MP157_M4.ld \
	-Wl,--gc-sections \
	-Wl,-Map=$(TARGET).map \
	-specs=nano.specs \
	-specs=nosys.specs

LIBS := -lc -lm -lnosys

# ----------------------------------------------------------------------------
# Source files
# ----------------------------------------------------------------------------

CORE_SRCS := \
	Core/Src/main.c \
	Core/Src/app_sensor.c \
	Core/Src/app_power.c \
	Core/Src/app_rpmsg.c \
	Core/Src/sensor_manager.c \
	Core/Src/power_manager.c \
	Core/Src/system_config.c

# ----------------------------------------------------------------------------
# HAL sources
#
# Adjust this list to match the STM32CubeMP1 HAL package used by the project.
# ----------------------------------------------------------------------------

HAL_SRCS := \
	$(wildcard Drivers/CMSIS/Device/ST/STM32MP1xx/Source/*.c) \
	$(wildcard Drivers/STM32MP1xx_HAL_Driver/Src/*.c)

# ----------------------------------------------------------------------------
# Startup
# ----------------------------------------------------------------------------

STARTUP_SRC := \
	$(wildcard Drivers/CMSIS/Device/ST/STM32MP1xx/Source/Templates/gcc/*.s)

# ----------------------------------------------------------------------------
# Middleware
# ----------------------------------------------------------------------------

OPENAMP_SRCS := \
	$(wildcard Middlewares/OpenAMP/*.c)

# ----------------------------------------------------------------------------
# All sources
# ----------------------------------------------------------------------------

C_SOURCES := \
	$(CORE_SRCS) \
	$(HAL_SRCS) \
	$(OPENAMP_SRCS)

ASM_SOURCES := \
	$(STARTUP_SRC)

# ----------------------------------------------------------------------------
# Object files
# ----------------------------------------------------------------------------

C_OBJECTS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES))

ASM_OBJECTS := $(patsubst %.s,$(BUILD_DIR)/%.o,$(ASM_SOURCES))

OBJECTS := $(C_OBJECTS) $(ASM_OBJECTS)

# ----------------------------------------------------------------------------
# Default target
# ----------------------------------------------------------------------------

.PHONY: all

all: $(TARGET).elf $(TARGET).bin $(TARGET).hex
	@echo ""
	@echo "=============================================="
	@echo " STM32MP157 Cortex-M4 Build Complete"
	@echo "=============================================="
	@$(SIZE) $(TARGET).elf
	@echo ""
	@echo "Output:"
	@echo "  $(TARGET).elf"
	@echo "  $(TARGET).bin"
	@echo "  $(TARGET).hex"
	@echo "  $(TARGET).map"
	@echo ""

# ----------------------------------------------------------------------------
# Create directories
# ----------------------------------------------------------------------------

$(BUILD_DIR):
	@mkdir -p $@

$(OUTPUT_DIR):
	@mkdir -p $@

# ----------------------------------------------------------------------------
# Compile C
# ----------------------------------------------------------------------------

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "[CC] $<"
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# ----------------------------------------------------------------------------
# Assemble
# ----------------------------------------------------------------------------

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	@echo "[AS] $<"
	@$(AS) $(ASFLAGS) -c $< -o $@

# ----------------------------------------------------------------------------
# Link
# ----------------------------------------------------------------------------

$(TARGET).elf: $(OBJECTS) | $(OUTPUT_DIR)
	@echo "[LD] $@"
	@$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

# ----------------------------------------------------------------------------
# Binary
# ----------------------------------------------------------------------------

$(TARGET).bin: $(TARGET).elf
	@echo "[BIN] $@"
	@$(OBJCOPY) -O binary $< $@

# ----------------------------------------------------------------------------
# HEX
# ----------------------------------------------------------------------------

$(TARGET).hex: $(TARGET).elf
	@echo "[HEX] $@"
	@$(OBJCOPY) -O ihex $< $@

# ----------------------------------------------------------------------------
# Disassembly
# ----------------------------------------------------------------------------

.PHONY: disassemble

disassemble: $(TARGET).elf
	@$(OBJDUMP) -d -S $(TARGET).elf > $(TARGET).lst
	@echo "Generated: $(TARGET).lst"

# ----------------------------------------------------------------------------
# Size
# ----------------------------------------------------------------------------

.PHONY: size

size: $(TARGET).elf
	@$(SIZE) $(TARGET).elf

# ----------------------------------------------------------------------------
# Debug build
# ----------------------------------------------------------------------------

.PHONY: debug

debug:
	$(MAKE) CFLAGS="$(COMMON_FLAGS) -std=gnu11 -O0 -g3 $(DEFINES) $(INCLUDES)"

# ----------------------------------------------------------------------------
# Release build
# ----------------------------------------------------------------------------

.PHONY: release

release:
	$(MAKE) CFLAGS="$(COMMON_FLAGS) -std=gnu11 -Os -DNDEBUG $(DEFINES) $(INCLUDES)"

# ----------------------------------------------------------------------------
# Clean
# ----------------------------------------------------------------------------

.PHONY: clean

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)

# ----------------------------------------------------------------------------
# Dependency files
# ----------------------------------------------------------------------------

-include $(C_OBJECTS:.o=.d)
