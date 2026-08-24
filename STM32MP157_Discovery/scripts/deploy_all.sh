#!/bin/bash

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

TARGET="${TARGET:-root@stm32mp157}"

REMOTE_DIR="${REMOTE_DIR:-/opt/stm32mp157}"

echo "========================================"
echo " STM32MP157 DEPLOY"
echo "========================================"

echo "Target      : $TARGET"
echo "Remote path : $REMOTE_DIR"

echo
echo "[1] Creating target directory..."

ssh "$TARGET" \
    "mkdir -p $REMOTE_DIR/apps $REMOTE_DIR/services"

echo
echo "[2] Deploying Linux applications..."

for app in "$PROJECT_ROOT"/linux/apps/*; do

    if [ -d "$app" ]; then

        APP_NAME="$(basename "$app")"

        if [ -f "$app/$APP_NAME" ]; then

            echo "Deploying $APP_NAME..."

            scp "$app/$APP_NAME" \
                "$TARGET:$REMOTE_DIR/apps/"
        fi
    fi

done

echo
echo "[3] Deploying Linux services..."

for service in "$PROJECT_ROOT"/linux/services/*; do

    if [ -d "$service" ]; then

        SERVICE_NAME="$(basename "$service")"

        if [ -f "$service/$SERVICE_NAME" ]; then

            echo "Deploying $SERVICE_NAME..."

            scp "$service/$SERVICE_NAME" \
                "$TARGET:$REMOTE_DIR/services/"
        fi
    fi

done

echo
echo "[4] Deploying Cortex-M4 firmware..."

M4_BINARY="$PROJECT_ROOT/cortex-m4/build/stm32mp157-m4.elf"

if [ -f "$M4_BINARY" ]; then

    scp "$M4_BINARY" \
        "$TARGET:$REMOTE_DIR/"

else

    echo "M4 firmware not found:"
    echo "$M4_BINARY"

fi

echo
echo "========================================"
echo " DEPLOYMENT COMPLETED"
echo "========================================"
