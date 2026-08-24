#!/bin/bash

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

echo "========================================"
echo " STM32MP157 DISCOVERY - CLEAN ALL"
echo "========================================"

echo
echo "Cleaning Cortex-M4..."

if [ -d "$PROJECT_ROOT/cortex-m4" ]; then
    cd "$PROJECT_ROOT/cortex-m4"

    if [ -f Makefile ]; then
        make clean || true
    fi
fi

echo
echo "Cleaning Linux applications..."

find "$PROJECT_ROOT/linux/apps" \
    -type f \
    \( -name "power-manager" \
    -o -name "rpmsg-test" \
    -o -name "sensor-manager" \
    -o -name "sensor-monitor" \) \
    -delete

echo
echo "Cleaning Linux services..."

find "$PROJECT_ROOT/linux/services" \
    -type f \
    \( -name "sensor-service" \
    -o -name "power-service" \) \
    -delete

echo
echo "Cleaning logs..."

find "$PROJECT_ROOT" \
    -type f \
    -name "*.log" \
    -delete

echo
echo "========================================"
echo " CLEAN COMPLETED"
echo "========================================"
