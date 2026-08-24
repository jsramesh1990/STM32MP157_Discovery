#!/bin/bash

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

LINUX_SCRIPTS="$PROJECT_ROOT/linux/scripts"

echo "========================================"
echo " STM32MP157 COMPLETE TEST"
echo "========================================"

PASS=0
FAIL=0

run_test()
{
    NAME="$1"
    SCRIPT="$2"

    echo
    echo "----------------------------------------"
    echo "Running: $NAME"
    echo "----------------------------------------"

    if "$SCRIPT"; then
        echo "[PASS] $NAME"
        PASS=$((PASS + 1))
    else
        echo "[FAIL] $NAME"
        FAIL=$((FAIL + 1))
    fi
}

run_test \
    "Power Test" \
    "$LINUX_SCRIPTS/power_test.sh"

run_test \
    "Sensor Test" \
    "$LINUX_SCRIPTS/sensor_test.sh"

echo
echo "Suspend and wakeup tests may require root."

if [ "$(id -u)" -eq 0 ]; then

    run_test \
        "Suspend Test" \
        "$LINUX_SCRIPTS/suspend_test.sh"

    run_test \
        "Wakeup Test" \
        "$LINUX_SCRIPTS/wakeup_test.sh"

else

    echo "[SKIP] Suspend Test - root required"
    echo "[SKIP] Wakeup Test - root required"

fi

echo
echo "========================================"
echo " TEST SUMMARY"
echo "========================================"

echo "PASS : $PASS"
echo "FAIL : $FAIL"

if [ "$FAIL" -eq 0 ]; then
    echo "RESULT: ALL TESTS PASSED"
    exit 0
else
    echo "RESULT: TEST FAILURES DETECTED"
    exit 1
fi
