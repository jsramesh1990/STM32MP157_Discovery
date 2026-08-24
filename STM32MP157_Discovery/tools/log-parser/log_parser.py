#!/usr/bin/env python3

import sys
import re


def parse_log(filename):
    temperatures = []
    pressures = []
    vibrations = []

    with open(filename, "r", encoding="utf-8") as file:
        for line in file:
            match = re.search(
                r"Temperature\s*:\s*([-+]?[0-9]*\.?[0-9]+)",
                line
            )
            if match:
                temperatures.append(float(match.group(1)))

            match = re.search(
                r"Pressure\s*:\s*([-+]?[0-9]*\.?[0-9]+)",
                line
            )
            if match:
                pressures.append(float(match.group(1)))

            match = re.search(
                r"Vibration\s*:\s*([-+]?[0-9]*\.?[0-9]+)",
                line
            )
            if match:
                vibrations.append(float(match.group(1)))

    print("========================================")
    print(" STM32MP157 LOG SUMMARY")
    print("========================================")

    if temperatures:
        print(f"Temperature samples : {len(temperatures)}")
        print(f"Temperature min     : {min(temperatures):.2f}")
        print(f"Temperature max     : {max(temperatures):.2f}")
        print(f"Temperature average : {sum(temperatures)/len(temperatures):.2f}")

    if pressures:
        print(f"Pressure samples    : {len(pressures)}")
        print(f"Pressure min        : {min(pressures):.2f}")
        print(f"Pressure max        : {max(pressures):.2f}")

    if vibrations:
        print(f"Vibration samples   : {len(vibrations)}")
        print(f"Vibration min       : {min(vibrations):.2f}")
        print(f"Vibration max       : {max(vibrations):.2f}")

    print("========================================")


def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <log-file>")
        return 1

    parse_log(sys.argv[1])
    return 0


if __name__ == "__main__":
    sys.exit(main())
