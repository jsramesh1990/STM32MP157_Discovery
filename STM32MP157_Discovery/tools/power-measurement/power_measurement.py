#!/usr/bin/env python3

import sys


def calculate_power(voltage, current):
    return voltage * current


def calculate_energy(power, time_seconds):
    return power * time_seconds


def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <voltage> <current>")
        print("Example: power_measurement.py 3.3 0.002")
        return 1

    voltage = float(sys.argv[1])
    current = float(sys.argv[2])

    power = calculate_power(voltage, current)

    print("========================================")
    print(" STM32MP157 POWER MEASUREMENT")
    print("========================================")
    print(f"Voltage : {voltage:.6f} V")
    print(f"Current : {current:.9f} A")
    print(f"Power   : {power:.9f} W")
    print(f"Power   : {power * 1000:.6f} mW")
    print("========================================")

    return 0


if __name__ == "__main__":
    sys.exit(main())
