#!/bin/bash

echo "========================================"
echo " STM32MP157 SUSPEND TEST"
echo "========================================"

if [ "$(id -u)" -ne 0 ]; then
    echo "ERROR: Run this script as root."
    echo
    echo "Example:"
    echo "  sudo ./suspend_test.sh"
    exit 1
fi

echo
echo "Supported Linux power states:"
echo "----------------------------------------"

if [ -f /sys/power/state ]; then
    cat /sys/power/state
else
    echo "ERROR: /sys/power/state not available."
    exit 1
fi

echo
echo "Checking wakeup sources..."
echo "----------------------------------------"

if [ -f /sys/kernel/debug/wakeup_sources ]; then
    cat /sys/kernel/debug/wakeup_sources
else
    echo "wakeup_sources is not available."
fi

echo
echo "Current time before suspend:"
date

echo
echo "System will enter suspend in 5 seconds..."
sleep 5

echo
echo "Entering suspend..."

if [ -w /sys/power/state ]; then
    echo mem > /sys/power/state
else
    echo "ERROR: Unable to access /sys/power/state."
    exit 1
fi

echo
echo "System resumed."

echo
echo "Current time after resume:"
date

echo
echo "Suspend test completed."
