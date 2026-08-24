Yes. Keep exactly these two service recipes:

```text
STM32MP157_Discovery/yocto/meta-energy-sensor/recipes-services/
├── power-service/
└── sensor-service/
```

For consistency with your project, each directory should contain **one `.bb` recipe only**:

```text
recipes-services/
├── power-service/
│   └── power-service.bb
│
└── sensor-service/
    └── sensor-service.bb
```

Their roles are different from `recipes-apps`:

```text
recipes-apps/
    → User applications
    → power-manager
    → sensor-manager
    → sensor-monitor
    → rpmsg-test

recipes-services/
    → Background system services
    → power-service
    → sensor-service
```

The runtime architecture is:

```text
                    Linux
                      │
          ┌───────────┴───────────┐
          │                       │
          ▼                       ▼
   power-service            sensor-service
          │                       │
          ▼                       ▼
    Power Manager           Sensor Manager
          │                       │
          └───────────┬───────────┘
                      ▼
                System / Sensors
```

`power-service.bb` should package and install the power-management daemon, while `sensor-service.bb` should package and install the sensor daemon.

For example, the recipe structure:

```bitbake
SUMMARY = "STM32MP157 Power Service"
DESCRIPTION = "Background power management service"
LICENSE = "CLOSED"

SRC_URI = "file://power_service.c \
           file://power_service.h \
           file://power-service.service"

S = "${WORKDIR}"

inherit systemd

SYSTEMD_SERVICE:${PN} = "power-service.service"
SYSTEMD_AUTO_ENABLE:${PN} = "enable"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} \
        ${S}/power_service.c \
        -o ${S}/power-service
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/power-service ${D}${bindir}/power-service

    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${S}/power-service.service \
        ${D}${systemd_system_unitdir}/power-service.service
}

FILES:${PN} += " \
    ${bindir}/power-service \
    ${systemd_system_unitdir}/power-service.service \
"
```

And `sensor-service.bb` follows the same model:

```text
sensor-service source
        ↓
sensor-service.bb
        ↓
BitBake
        ↓
/usr/bin/sensor-service
        +
sensor-service.service
        ↓
systemd
        ↓
Sensor service running
```

One important point: **these services should not duplicate your `linux/apps` applications unnecessarily.**

Think of the architecture this way:

```text
linux/apps/
│
├── power-manager
│     → User/control application
│
├── sensor-manager
│     → Sensor management application
│
├── sensor-monitor
│     → Monitoring/debug application
│
└── rpmsg-test
      → Test application


linux/services/
│
├── power-service
│     → Long-running power daemon
│
└── sensor-service
      → Long-running sensor daemon
```

Then Yocto packages those runtime components:

```text
linux/services/power-service
             │
             ▼
recipes-services/power-service/
             │
             ▼
       power-service.bb
             │
             ▼
          BitBake
             │
             ▼
       STM32MP157 rootfs


linux/services/sensor-service
             │
             ▼
recipes-services/sensor-service/
             │
             ▼
       sensor-service.bb
             │
             ▼
          BitBake
             │
             ▼
       STM32MP157 rootfs
```

So your `recipes-services` directory is correctly limited to:

```text
recipes-services/
├── power-service/
│   └── power-service.bb
└── sensor-service/
    └── sensor-service.bb
```

No additional directories are required at this level.

