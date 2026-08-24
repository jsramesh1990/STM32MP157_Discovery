SUMMARY = "STM32MP157 Energy Sensor Device Tree"
DESCRIPTION = "Custom Device Tree configuration for STM32MP157 energy harvesting sensor platform"
LICENSE = "CLOSED"

SRC_URI = " \
    file://stm32mp157-energy-sensor.dts \
    file://stm32mp157-energy-sensor-overlay.dts \
    file://stm32mp157-energy-sensor-pinctrl.dtsi \
"

S = "${WORKDIR}"

do_compile() {
    echo "Compiling STM32MP157 Energy Sensor Device Tree"

    dtc \
        -I dts \
        -O dtb \
        -o ${S}/stm32mp157-energy-sensor.dtb \
        ${S}/stm32mp157-energy-sensor.dts
}

do_install() {
    install -d ${D}/boot

    install -m 0644 \
        ${S}/stm32mp157-energy-sensor.dtb \
        ${D}/boot/stm32mp157-energy-sensor.dtb
}

FILES:${PN} += "/boot/stm32mp157-energy-sensor.dtb"
