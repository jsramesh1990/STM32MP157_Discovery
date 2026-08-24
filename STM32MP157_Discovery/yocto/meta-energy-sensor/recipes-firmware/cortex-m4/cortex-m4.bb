SUMMARY = "STM32MP157 Cortex-M4 Energy Sensor Firmware"
DESCRIPTION = "Cortex-M4 firmware for low-power sensor and energy management"
LICENSE = "CLOSED"

SRC_URI = " \
    file://Makefile \
    file://Core/Inc/main.h \
    file://Core/Inc/app_sensor.h \
    file://Core/Inc/app_power.h \
    file://Core/Inc/app_rpmsg.h \
    file://Core/Inc/sensor_manager.h \
    file://Core/Inc/power_manager.h \
    file://Core/Inc/system_config.h \
    file://Core/Src/main.c \
    file://Core/Src/app_sensor.c \
    file://Core/Src/app_power.c \
    file://Core/Src/app_rpmsg.c \
    file://Core/Src/sensor_manager.c \
    file://Core/Src/power_manager.c \
    file://Core/Src/system_config.c \
    file://Config/stm32mp157xx_hal_conf.h \
    file://Config/stm32mp157xx_it.h \
    file://linker/STM32MP157_M4.ld \
"

S = "${WORKDIR}"

do_compile() {
    oe_runmake
}

do_install() {
    install -d ${D}${nonarch_base_libdir}/firmware

    install -m 0644 \
        ${S}/build/stm32mp157-m4.elf \
        ${D}${nonarch_base_libdir}/firmware/stm32mp157-m4.elf
}

FILES:${PN} += \
    "${nonarch_base_libdir}/firmware/stm32mp157-m4.elf"
