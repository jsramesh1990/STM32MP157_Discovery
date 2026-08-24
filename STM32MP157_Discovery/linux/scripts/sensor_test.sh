#!/bin/bash

echo "========================================"
echo " STM32MP157 SENSOR TEST"
echo "========================================"

PASS=0
FAIL=0

echo
echo "Checking sensor directories..."
echo "----------------------------------------"

for sensor in temperature pressure vibration
do
    if [ -d "../../hardware/sensors/$sensor" ]; then
        echo "[PASS] $sensor configuration found"
        PASS=$((PASS + 1))
    else
        echo "[FAIL] $sensor configuration not found"
        FAIL=$((FAIL + 1))
    fi
done

echo
echo "Checking sensor-manager..."
echo "----------------------------------------"

if command -v sensor-manager >/dev/null 2>&1; then
    echo "[PASS] sensor-manager found"
    PASS=$((PASS + 1))
else
    echo "[INFO] sensor-manager not installed in PATH"
fi

echo
echo "Checking RPMsg..."
echo "----------------------------------------"

if ls /dev/rpmsg* >/dev/null 2>&1; then
    echo "[PASS] RPMsg device found"
    ls -l /dev/rpmsg*
    PASS=$((PASS + 1))
else
    echo "[INFO] RPMsg device not found"
fi

echo
echo "========================================"
echo " SENSOR TEST RESULT"
echo "========================================"

echo "PASS : $PASS"
echo "FAIL : $FAIL"

if [ "$FAIL" -eq 0 ]; then
    echo "RESULT: PASS"
    exit 0
else
    echo "RESULT: CHECK REQUIRED"
    exit 1
fi
