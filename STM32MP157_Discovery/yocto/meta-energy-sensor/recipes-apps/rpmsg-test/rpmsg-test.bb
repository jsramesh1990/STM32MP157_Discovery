SUMMARY = "STM32MP157 RPMsg Test Application"
DESCRIPTION = "Tests RPMsg communication between Cortex-A7 Linux and Cortex-M4"
LICENSE = "CLOSED"

SRC_URI = "file://main.c \
           file://rpmsg_test.c \
           file://rpmsg_test.h"

S = "${WORKDIR}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} \
        ${S}/main.c \
        ${S}/rpmsg_test.c \
        -o ${S}/rpmsg-test
}

do_install() {
    install -d ${D}${bindir}

    install -m 0755 ${S}/rpmsg-test \
        ${D}${bindir}/rpmsg-test
}

FILES:${PN} += "${bindir}/rpmsg-test"
