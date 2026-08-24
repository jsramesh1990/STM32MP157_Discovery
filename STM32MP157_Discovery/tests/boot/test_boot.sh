#!/bin/bash

echo "========================================"
echo " STM32MP157 BOOT TEST"
echo "========================================"

PASS=0
FAIL=0

echo
echo "[1] Checking kernel..."

if [ -f /proc/version ]; then
    echo "[PASS] Linux kernel running"
    PASS=$((PASS + 1))
else
    echo "[FAIL] Linux kernel information unavailable"
    FAIL=$((FAIL + 1))
fi

echo
echo "[2] Checking CPU..."

if grep -q "ARMv7" /proc/cpuinfo; then
    echo "[PASS] ARM processor detected"
    PASS=$((PASS + 1))
else
    echo "[INFO] ARM processor information differs"
fi

echo
echo "[3] Checking device tree..."

if [ -d /proc/device-tree ]; then
    echo "[PASS] Device Tree available"
    PASS=$((PASS + 1))
else
    echo "[FAIL] Device Tree unavailable"
    FAIL=$((FAIL + 1))
fi

echo
echo "[4] Checking boot messages..."

if dmesg | grep -qi "Linux version"; then
    echo "[PASS] Linux boot messages found"
    PASS=$((PASS + 1))
else
    echo "[FAIL] Linux boot messages not found"
    FAIL=$((FAIL + 1))
fi

echo
echo "========================================"
echo " BOOT TEST RESULT"
echo "========================================"

echo "PASS: $PASS"
echo "FAIL: $FAIL"

[ "$FAIL" -eq 0 ]
