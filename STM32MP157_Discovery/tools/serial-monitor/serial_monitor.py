#!/usr/bin/env python3

import sys

try:
    import serial
except ImportError:
    print("pyserial is required.")
    print("Install with:")
    print("    python3 -m pip install pyserial")
    sys.exit(1)


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <serial-device> [baudrate]")
        print(f"Example: {sys.argv[0]} /dev/ttyUSB0 115200")
        return 1

    port = sys.argv[1]
    baudrate = int(sys.argv[2]) if len(sys.argv) > 2 else 115200

    print("========================================")
    print(" STM32MP157 SERIAL MONITOR")
    print("========================================")
    print(f"Port     : {port}")
    print(f"Baudrate : {baudrate}")
    print("Press Ctrl+C to exit.")
    print()

    try:
        with serial.Serial(
            port=port,
            baudrate=baudrate,
            timeout=1
        ) as ser:

            while True:
                data = ser.readline()

                if data:
                    print(
                        data.decode(
                            "utf-8",
                            errors="replace"
                        ),
                        end=""
                    )

    except KeyboardInterrupt:
        print("\nSerial monitor stopped.")

    except serial.SerialException as error:
        print(f"Serial error: {error}")
        return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())
