SUMMARY = "STM32MP157 Energy Sensor Application"
DESCRIPTION = "Energy harvesting and sensor monitoring application for STM32MP157"
LICENSE = "CLOSED"

SRC_URI = " \
    file://energy-sensor.c \
    file://energy-sensor.service \
"

S = "${WORKDIR}"

inherit systemd

SYSTEMD_SERVICE:${PN} = "energy-sensor.service"
SYSTEMD_AUTO_ENABLE:${PN} = "enable"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} \
        ${S}/energy-sensor.c \
        -o ${S}/energy-sensor
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/energy-sensor \
        ${D}${bindir}/energy-sensor

    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${S}/energy-sensor.service \
        ${D}${systemd_system_unitdir}/energy-sensor.service
}

FILES:${PN} += " \
    ${bindir}/energy-sensor \
    ${systemd_system_unitdir}/energy-sensor.service \
"
