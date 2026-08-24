#!/bin/bash

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

echo "========================================"
echo " STM32MP157 DISCOVERY - BUILD ALL"
echo "========================================"

echo "Project root: $PROJECT_ROOT"

echo
echo "[1/4] Building Cortex-M4..."
cd "$PROJECT_ROOT/cortex-m4"

if [ -f Makefile ]; then
    make
else
    echo "Cortex-M4 Makefile not found"
fi

echo
echo "[2/4] Building Linux applications..."

for app in "$PROJECT_ROOT"/linux/apps/*; do
    if [ -d "$app" ] && [ -f "$app/main.c" ]; then
        echo "Building $(basename "$app")..."

        cd "$app"

        gcc -Wall -Wextra \
            main.c \
            *.c \
            -o "$(basename "$app")"
    fi
done

echo
echo "[3/4] Building Linux services..."

for service in "$PROJECT_ROOT"/linux/services/*; do
    if [ -d "$service" ] && [ -f "$service/main.c" ]; then
        echo "Building $(basename "$service")..."

        cd "$service"

        gcc -Wall -Wextra \
            main.c \
            *.c \
            -o "$(basename "$service")"
    fi
done

echo
echo "[4/4] Checking Device Tree..."

if [ -d "$PROJECT_ROOT/device-tree" ]; then
    echo "Device Tree directory found"
else
    echo "Device Tree directory not found"
fi

echo
echo "========================================"
echo " BUILD COMPLETED"
echo "========================================"
