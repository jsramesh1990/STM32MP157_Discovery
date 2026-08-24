#!/bin/bash

echo "========================================"
echo " STM32MP157 POWER TEST"
echo "========================================"

echo
echo "Power Supply Information:"
echo "----------------------------------------"

if [ -d /sys/class/power_supply ]; then
    for supply in /sys/class/power_supply/*; do
        if [ -d "$supply" ]; then
            echo "Supply: $(basename "$supply")"

            [ -f "$supply/status" ] &&
                echo "Status : $(cat "$supply/status")"

            [ -f "$supply/voltage_now" ] &&
                echo "Voltage: $(cat "$supply/voltage_now")"

            [ -f "$supply/current_now" ] &&
                echo "Current: $(cat "$supply/current_now")"

            echo
        fi
    done
else
    echo "No power-supply interface found."
fi

echo "System Power State:"
echo "----------------------------------------"

if [ -f /sys/power/state ]; then
    echo "Supported states:"
    cat /sys/power/state
else
    echo "/sys/power/state not available."
fi

echo
echo "CPU Information:"
echo "----------------------------------------"

if [ -f /proc/cpuinfo ]; then
    grep -E "model name|processor" /proc/cpuinfo | head
fi

echo
echo "Power test completed."
