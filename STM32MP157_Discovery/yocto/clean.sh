#!/bin/bash

set -e

echo "========================================"
echo " STM32MP157 YOCTO CLEAN"
echo "========================================"

echo
echo "Cleaning build output..."

bitbake -c cleanall energy-sensor-image

echo
echo "Clean completed."
