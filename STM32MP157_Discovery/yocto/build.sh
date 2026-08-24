#!/bin/bash

set -e

YOCTO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "========================================"
echo " STM32MP157 YOCTO BUILD"
echo "========================================"

cd "$YOCTO_ROOT"

if [ -f "setup.sh" ]; then
    source ./setup.sh
fi

echo
echo "Building STM32MP157 image..."

bitbake core-image-minimal

echo
echo "========================================"
echo " YOCTO BUILD COMPLETED"
echo "========================================"
