#!/bin/bash

echo "========================================"
echo " STM32MP157 WAKEUP TEST"
echo "========================================"

PASS=0
FAIL=0

echo
echo "[1] Checking wakeup sources..."

if [ -f /sys/kernel/debug/wakeup_sources ]; then
    echo "[PASS] Wakeup source interface available"
    PASS=$((PASS + 1))
else
    echo "[FAIL] Wakeup source interface unavailable"
    FAIL=$((FAIL + 1))
fi

echo
echo "[2] Checking wakeup devices..."

COUNT=0

for device in /sys/class/wakeup/*; do
    if [ -d "$device" ]; then
        echo "Wakeup device: $(basename "$device")"
        COUNT=$((COUNT + 1))
    fi
done

if [ "$COUNT" -gt 0 ]; then
    echo "[PASS] Wakeup devices detected"
    PASS=$((PASS + 1))
else
    echo "[INFO] No wakeup devices detected"
fi

echo
echo "[3] Checking power state interface..."

if [ -f /sys/power/state ]; then
    echo "[PASS] Suspend interface available"
    cat /sys/power/state
    PASS=$((PASS + 1))
else
    echo "[FAIL] Suspend interface unavailable"
    FAIL=$((FAIL + 1))
fi

echo
echo "PASS: $PASS"
echo "FAIL: $FAIL"

[ "$FAIL" -eq 0 ]
