The responsibilities should be:

setup.sh
   ↓
Prepare Yocto environment
   ↓
build.sh
   ↓
Build Linux image
   ↓
deploy.sh
   ↓
Copy artifacts / prepare deployment
   ↓
flash_sd.sh
   ↓
Flash SD card
   ↓
STM32MP157 Discovery Kit

clean.sh is used whenever you need to remove Yocto build artifacts.

For meta-energy-sensor, keep the custom Yocto layer separate from the scripts:

meta-energy-sensor/
├── conf/
│   └── layer.conf
│
├── recipes-apps/
│   ├── power-manager/
│   ├── sensor-manager/
│   ├── sensor-monitor/
│   └── rpmsg-test/
│
├── recipes-services/
│   ├── power-service/
│   └── sensor-service/
│
├── recipes-firmware/
│   └── cortex-m4/
│
├── recipes-kernel/
│   └── linux/
│
├── recipes-bsp/
│   └── device-tree/
│
└── README.md

This is where your GitHub project becomes connected to the actual Yocto build.

For example:

linux/apps/sensor-manager/
        │
        │ source code
        ▼
meta-energy-sensor/
recipes-apps/
sensor-manager/
        │
        │ Yocto recipe
        ▼
BitBake
        │
        ▼
root filesystem
        │
        ▼
STM32MP157 Linux

Similarly:

cortex-m4/
        │
        ▼
meta-energy-sensor/
recipes-firmware/
cortex-m4/
        │
        ▼
BitBake
        │
        ▼
M4 firmware
        │
        ▼
STM32MP157

And your custom Device Tree:

device-tree/
    │
    ▼
meta-energy-sensor/
recipes-bsp/
device-tree/
    │
    ▼
Yocto
    │
    ▼
Linux DTB



# STM32MP157 Yocto Build

This directory contains the Yocto/OpenEmbedded build environment
for the STM32MP157 Discovery energy-harvesting sensor project.

## Structure

```text
yocto/
├── setup.sh
├── build.sh
├── clean.sh
├── deploy.sh
├── flash_sd.sh
├── meta-energy-sensor/
└── README.md
Purpose

The Yocto layer integrates:

Cortex-M4 firmware
Sensor applications
Power management applications
Linux services
Device Tree configuration
Required runtime packages
System configuration
Build Flow
setup.sh
    ↓
Yocto environment
    ↓
meta-energy-sensor
    ↓
BitBake
    ↓
Linux kernel
    ↓
Device Tree
    ↓
Root filesystem
    ↓
Cortex-M4 firmware
    ↓
Bootable image
Setup
cd yocto
./setup.sh
Build
./build.sh
Deploy
./deploy.sh
Flash
sudo ./flash_sd.sh deploy/<image>.wic
Clean
./clean.sh
Custom Layer

The meta-energy-sensor layer contains the project-specific
Yocto recipes.

It integrates the Linux applications, services, firmware and
Device Tree configuration into the final image.


One important correction to the earlier project structure: **don't duplicate the source files inside `yocto/meta-energy-sensor`**. The actual C source should remain under:

```text
linux/apps/
linux/services/
cortex-m4/

and the Yocto recipes should fetch/reference those sources.

So the architecture is:

                    GitHub Project
                         │
        ┌────────────────┼────────────────┐
        │                │                │
        ▼                ▼                ▼
   Source Code       Hardware         Yocto Layer
        │                │                │
        │                │                │
        ▼                ▼                ▼
 linux/apps        device-tree     recipes-apps
 linux/services    sensors         recipes-services
 cortex-m4         energy          recipes-firmware
        │                │                │
        └────────────────┼────────────────┘
                         ▼
                       BitBake
                         │
             ┌───────────┼───────────┐
             ▼           ▼           ▼
          Kernel        DTB        RootFS
             │           │           │
             └───────────┼───────────┘
                         ▼
                  STM32MP157 Image
                         │
                         ▼
                    Discovery Kit

This makes yocto/ the build/integration layer, rather than another copy of your application source.

