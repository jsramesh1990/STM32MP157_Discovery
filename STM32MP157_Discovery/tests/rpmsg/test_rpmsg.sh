#!/bin/bash

echo "========================================"
echo " STM32MP157 RPMSG TEST"
echo "========================================"

PASS=0
FAIL=0

echo
echo "[1] Checking RPMsg devices..."

if ls /dev/rpmsg* >/dev/null 2>&1; then
    echo "[PASS] RPMsg device found"
    ls -l /dev/rpmsg*
    PASS=$((PASS + 1))
else
    echo "[FAIL] RPMsg device not found"
    FAIL=$((FAIL + 1))
fi

echo
echo "[2] Checking remoteproc..."

if [ -d /sys/class/remoteproc ]; then
    echo "[PASS] Remoteproc subsystem available"
    ls /sys/class/remoteproc/
    PASS=$((PASS + 1))
else
    echo "[FAIL] Remoteproc subsystem unavailable"
    FAIL=$((FAIL + 1))
fi

echo
echo "[3] Checking kernel RPMsg messages..."

if dmesg | grep -qi rpmsg; then
    echo "[PASS] RPMsg messages found"
    PASS=$((PASS + 1))
else
    echo "[INFO] No RPMsg messages found"
fi

echo
echo "PASS: $PASS"
echo "FAIL: $FAIL"

[ "$FAIL" -eq 0 ]
