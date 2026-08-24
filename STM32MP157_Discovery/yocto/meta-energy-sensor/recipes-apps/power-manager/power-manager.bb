SUMMARY = "STM32MP157 Linux Power Manager"
DESCRIPTION = "Power management application for the STM32MP157 energy sensor platform"
LICENSE = "CLOSED"

SRC_URI = "file://power-manager.c \
           file://power_manager.h \
           file://main.c"

S = "${WORKDIR}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} \
        ${S}/main.c \
        ${S}/power-manager.c \
        -o ${S}/power-manager
}

do_install() {
    install -d ${D}${bindir}

    install -m 0755 ${S}/power-manager \
        ${D}${bindir}/power-manager
}

FILES:${PN} += "${bindir}/power-manager"
