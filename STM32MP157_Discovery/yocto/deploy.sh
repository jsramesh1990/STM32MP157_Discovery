#!/bin/bash

set -e

YOCTO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

DEPLOY_DIR="$YOCTO_ROOT/build/tmp/deploy/images/stm32mp1"

OUTPUT_DIR="$YOCTO_ROOT/deploy"

mkdir -p "$OUTPUT_DIR"

echo "========================================"
echo " STM32MP157 YOCTO DEPLOY"
echo "========================================"

if [ ! -d "$DEPLOY_DIR" ]; then
    echo "ERROR:"
    echo "Deploy directory not found:"
    echo "$DEPLOY_DIR"
    exit 1
fi

echo
echo "Copying boot artifacts..."

find "$DEPLOY_DIR" \
    -maxdepth 1 \
    -type f \
    \( -name "*.wic" \
    -o -name "*.wic.gz" \
    -o -name "*.wic.bmap" \
    -o -name "*.dtb" \
    -o -name "Image" \
    -o -name "u-boot*" \) \
    -exec cp {} "$OUTPUT_DIR/" \;

echo
echo "Deployment artifacts:"
ls -lh "$OUTPUT_DIR"

echo
echo "Deployment preparation completed."
