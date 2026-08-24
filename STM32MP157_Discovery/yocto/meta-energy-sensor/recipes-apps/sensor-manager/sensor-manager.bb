SUMMARY = "STM32MP157 Sensor Manager"
DESCRIPTION = "Manages temperature, pressure and vibration sensors"
LICENSE = "CLOSED"

SRC_URI = "file://main.c \
           file://sensor_manager.c \
           file://sensor_manager.h"

S = "${WORKDIR}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} \
        ${S}/main.c \
        ${S}/sensor_manager.c \
        -o ${S}/sensor-manager
}

do_install() {
    install -d ${D}${bindir}

    install -m 0755 ${S}/sensor-manager \
        ${D}${bindir}/sensor-manager
}

FILES:${PN} += "${bindir}/sensor-manager"
