Yes. This directory:

```text
STM32MP157_Discovery/yocto/meta-energy-sensor/recipes-kernel/linux/linux-stm32mp/
```

should be used for **Linux kernel customization**, not for your normal Linux applications.

For your project, I recommend keeping it simple:

```text
STM32MP157_Discovery/yocto/meta-energy-sensor/recipes-kernel/
└── linux/
    └── linux-stm32mp/
        └── linux-stm32mp_%.bbappend
```

So the directory contains **one file only**:

```text
linux-stm32mp_%.bbappend
```

The purpose is:

```text
ST Linux kernel
       │
       ▼
linux-stm32mp_%.bbappend
       │
       ├── Device Tree customization
       ├── Kernel configuration
       ├── RPMsg configuration
       ├── Remoteproc configuration
       └── Sensor/low-power kernel options
       │
       ▼
Custom STM32MP157 Linux kernel
```

A starting `linux-stm32mp_%.bbappend` could be:

```bitbake
FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
"

# Project-specific kernel configuration
KERNEL_FEATURES:append = " "

# Enable required kernel functionality
CONFIG_RPMSG := "y"
CONFIG_REMOTEPROC := "y"
```

But there is an important correction here: **don't put arbitrary `CONFIG_*` assignments directly into a `.bbappend` unless the kernel recipe actually consumes them that way.** For a proper Yocto kernel configuration, use a configuration fragment.

For example, the professional structure would become:

```text
linux-stm32mp/
├── linux-stm32mp_%.bbappend
└── files/
    └── energy-sensor.cfg
```

where `energy-sensor.cfg` contains:

```text
CONFIG_REMOTEPROC=y
CONFIG_RPMSG=y
CONFIG_RPMSG_VIRTIO=y
```

and the `.bbappend` contains:

```bitbake
FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
    file://energy-sensor.cfg \
"

KERNEL_CONFIG_FRAGMENTS += " \
    ${WORKDIR}/energy-sensor.cfg \
"
```

Then your kernel customization flow is:

```text
energy-sensor.cfg
       │
       ▼
linux-stm32mp_%.bbappend
       │
       ▼
ST Linux kernel recipe
       │
       ▼
Kernel configuration
       │
       ▼
Linux kernel
```

For your **STM32MP157 energy-harvesting project**, kernel customization should eventually cover:

```text
Linux Kernel
│
├── RemoteProc
│
├── RPMsg
│
├── Cortex-M4 communication
│
├── GPIO
│
├── I2C
│
├── SPI
│
├── Sensor interfaces
│
├── RTC
│
├── Wake-up sources
│
├── Power management
│
└── Suspend / resume
```

So I would make your directory:

```text
STM32MP157_Discovery/yocto/meta-energy-sensor/recipes-kernel/linux/
└── linux-stm32mp/
    ├── linux-stm32mp_%.bbappend
    └── files/
        └── energy-sensor.cfg
```

**But if you want to maintain your earlier rule of "one file only" inside this directory, keep only:**

```text
linux-stm32mp/
└── linux-stm32mp_%.bbappend
```

and add the kernel configuration fragment later when we actually define which STM32MP157 kernel features your project needs.

