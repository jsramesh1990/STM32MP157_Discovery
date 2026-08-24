#!/bin/bash

echo "========================================"
echo " STM32MP157 ENERGY TEST"
echo "========================================"

PASS=0
FAIL=0

echo
echo "[1] Checking power supply interface..."

if [ -d /sys/class/power_supply ]; then
    echo "[PASS] Power supply subsystem available"
    PASS=$((PASS + 1))
else
    echo "[INFO] No Linux power-supply device exposed"
fi

echo
echo "[2] Checking voltage information..."

FOUND=0

for supply in /sys/class/power_supply/*; do
    if [ -f "$supply/voltage_now" ]; then
        echo "Supply: $(basename "$supply")"
        echo "Voltage: $(cat "$supply/voltage_now")"
        FOUND=1
    fi
done

if [ "$FOUND" -eq 1 ]; then
    echo "[PASS] Voltage information available"
    PASS=$((PASS + 1))
else
    echo "[INFO] Voltage information unavailable"
fi

echo
echo "[3] Checking power state..."

if [ -f /sys/power/state ]; then
    echo "[PASS] Linux power management available"
    echo "Supported:"
    cat /sys/power/state
    PASS=$((PASS + 1))
else
    echo "[FAIL] Power management unavailable"
    FAIL=$((FAIL + 1))
fi

echo
echo "PASS: $PASS"
echo "FAIL: $FAIL"

[ "$FAIL" -eq 0 ]
