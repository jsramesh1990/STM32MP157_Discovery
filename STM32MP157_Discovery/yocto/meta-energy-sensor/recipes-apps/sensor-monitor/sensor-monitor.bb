SUMMARY = "STM32MP157 Sensor Monitor"
DESCRIPTION = "Monitors sensor values and reports sensor status"
LICENSE = "CLOSED"

SRC_URI = "file://main.c \
           file://sensor_monitor.c \
           file://sensor_monitor.h"

S = "${WORKDIR}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} \
        ${S}/main.c \
        ${S}/sensor_monitor.c \
        -o ${S}/sensor-monitor
}

do_install() {
    install -d ${D}${bindir}

    install -m 0755 ${S}/sensor-monitor \
        ${D}${bindir}/sensor-monitor
}

FILES:${PN} += "${bindir}/sensor-monitor"
