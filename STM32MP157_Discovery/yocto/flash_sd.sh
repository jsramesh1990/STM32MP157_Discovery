#!/bin/bash

set -e

IMAGE="${1:-}"

echo "========================================"
echo " STM32MP157 SD CARD FLASH"
echo "========================================"

if [ -z "$IMAGE" ]; then
    echo "Usage:"
    echo "  sudo ./flash_sd.sh <image.wic>"
    exit 1
fi

if [ ! -f "$IMAGE" ]; then
    echo "ERROR: Image not found:"
    echo "$IMAGE"
    exit 1
fi

echo
echo "Available block devices:"
lsblk -o NAME,SIZE,TYPE,MOUNTPOINTS

echo
read -rp "Enter SD card device (example: /dev/sdb): " DEVICE

if [ -z "$DEVICE" ]; then
    echo "ERROR: No device specified."
    exit 1
fi

if [ "$DEVICE" = "/" ] || [ "$DEVICE" = "/dev/nvme0n1" ]; then
    echo "ERROR: Refusing potentially dangerous device."
    exit 1
fi

echo
echo "WARNING!"
echo "This will ERASE:"
echo "$DEVICE"

echo
read -rp "Type YES to continue: " CONFIRM

if [ "$CONFIRM" != "YES" ]; then
    echo "Cancelled."
    exit 1
fi

echo
echo "Unmounting partitions..."

for partition in "${DEVICE}"*; do
    if mountpoint -q "$partition" 2>/dev/null; then
        umount "$partition"
    fi
done

echo
echo "Writing image..."

dd if="$IMAGE" of="$DEVICE" \
    bs=4M \
    status=progress \
    conv=fsync

sync

echo
echo "========================================"
echo " SD CARD FLASH COMPLETED"
echo "========================================"
