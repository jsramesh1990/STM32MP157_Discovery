#!/bin/bash

echo "========================================"
echo " STM32MP157 WAKEUP TEST"
echo "========================================"

if [ "$(id -u)" -ne 0 ]; then
    echo "ERROR: Run this script as root."
    echo
    echo "Example:"
    echo "  sudo ./wakeup_test.sh"
    exit 1
fi

echo
echo "Wakeup sources:"
echo "----------------------------------------"

if [ -f /sys/kernel/debug/wakeup_sources ]; then
    cat /sys/kernel/debug/wakeup_sources
else
    echo "wakeup_sources not available."
fi

echo
echo "Configured wakeup devices:"
echo "----------------------------------------"

for device in /sys/class/wakeup/*; do
    if [ -d "$device" ]; then
        echo "$(basename "$device")"

        if [ -f "$device/name" ]; then
            echo "  Name: $(cat "$device/name")"
        fi

        if [ -f "$device/power/wakeup" ]; then
            echo "  Wakeup: $(cat "$device/power/wakeup")"
        fi

        echo
    fi
done

echo "========================================"
echo " WAKEUP TEST"
echo "========================================"

echo
echo "System will enter suspend in 5 seconds."
echo "Trigger the configured wakeup source."
echo

sleep 5

if [ -w /sys/power/state ]; then
    echo "Entering suspend..."
    echo mem > /sys/power/state
else
    echo "ERROR: /sys/power/state unavailable."
    exit 1
fi

echo
echo "System resumed successfully."

echo
echo "Wakeup test completed."
