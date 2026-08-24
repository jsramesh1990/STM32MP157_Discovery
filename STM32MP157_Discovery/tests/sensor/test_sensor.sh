#!/bin/bash

echo "========================================"
echo " STM32MP157 SENSOR TEST"
echo "========================================"

PASS=0
FAIL=0

for sensor in temperature pressure vibration
do
    echo
    echo "Checking $sensor..."

    if [ -d "../../hardware/sensors/$sensor" ]; then
        echo "[PASS] $sensor configuration exists"
        PASS=$((PASS + 1))
    else
        echo "[FAIL] $sensor configuration missing"
        FAIL=$((FAIL + 1))
    fi
done

echo
echo "Checking sensor-manager..."

if command -v sensor-manager >/dev/null 2>&1; then
    echo "[PASS] sensor-manager available"
    PASS=$((PASS + 1))
else
    echo "[INFO] sensor-manager not installed"
fi

echo
echo "PASS: $PASS"
echo "FAIL: $FAIL"

[ "$FAIL" -eq 0 ]
