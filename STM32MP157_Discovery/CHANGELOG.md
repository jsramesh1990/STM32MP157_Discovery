# Changelog

All notable changes to the STM32MP157 Energy-Aware Sensor project
will be documented in this file.

The project follows a version-based changelog format.

---

## [Unreleased]

### Added

- Initial project architecture
- STM32MP157 energy-aware sensor concept
- Cortex-A7 / Cortex-M4 architecture definition
- Low-power operating-mode documentation
- Energy-harvesting architecture definition
- Initial GitHub repository structure

### Planned

- OpenSTLinux / Yocto build environment
- Custom Yocto layer
- Cortex-M4 sensor firmware
- RPMsg/OpenAMP communication
- Linux sensor-manager application
- Device Tree configuration
- RTC wake-up support
- GPIO wake-up support
- Sensor power gating
- Low-power testing scripts
- Power measurement framework
- Energy-budget calculation
- Solar energy-harvesting prototype
- Automated test framework

---

## [0.1.0] - Initial Development

### Added

- Initial repository structure
- STM32MP157 Discovery Kit project definition
- System architecture
- Cortex-A7 and Cortex-M4 responsibility definition
- Initial low-power strategy
- Initial energy-harvesting strategy
- Development roadmap

### Architecture

```text
Energy Source
      |
      v
Energy Harvester
      |
      v
Energy Storage
      |
      v
Power Management
      |
      v
STM32MP157
   /       \
Cortex-A7  Cortex-M4
   |          |
 Linux     Sensors
   |          |
   +-- RPMsg -+
        |
        v
    Data Processing
        |
        v
    Low Power
        |
        v
      Wake
