#!/bin/bash

echo "========================================"
echo " STM32MP157 LOW-POWER TEST"
echo "========================================"

if [ "$(id -u)" -ne 0 ]; then
    echo "ERROR: Run as root."
    exit 1
fi

echo
echo "Supported power states:"
echo "----------------------------------------"

if [ ! -f /sys/power/state ]; then
    echo "ERROR: /sys/power/state not available"
    exit 1
fi

cat /sys/power/state

echo
echo "Current wakeup sources:"
echo "----------------------------------------"

if [ -f /sys/kernel/debug/wakeup_sources ]; then
    cat /sys/kernel/debug/wakeup_sources
else
    echo "wakeup_sources unavailable"
fi

echo
echo "Low-power infrastructure check completed."
echo
echo "WARNING:"
echo "Entering suspend changes the system state."
echo "Use the dedicated linux/scripts/suspend_test.sh"
echo "for an actual suspend/resume test."
