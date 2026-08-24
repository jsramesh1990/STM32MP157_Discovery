#!/bin/bash

set -e

YOCTO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$YOCTO_ROOT/build"

echo "========================================"
echo " STM32MP157 YOCTO SETUP"
echo "========================================"

echo "Yocto root: $YOCTO_ROOT"

if [ -z "$BUILDDIR" ]; then
    export BUILDDIR="$BUILD_DIR"
fi

echo
echo "Build directory:"
echo "$BUILDDIR"

mkdir -p "$BUILDDIR"

echo
echo "Yocto environment prepared."

echo
echo "Next step:"
echo "  ./build.sh"
