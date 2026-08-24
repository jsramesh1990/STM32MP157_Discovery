#!/bin/bash

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

LOG_DIR="$PROJECT_ROOT/logs"

mkdir -p "$LOG_DIR"

TIMESTAMP="$(date +"%Y%m%d_%H%M%S")"

OUTPUT="$LOG_DIR/collect_$TIMESTAMP"

mkdir -p "$OUTPUT"

echo "========================================"
echo " STM32MP157 LOG COLLECTION"
echo "========================================"

echo "Output: $OUTPUT"

echo
echo "[1] Kernel log"

dmesg > "$OUTPUT/dmesg.log" 2>&1 || true

echo
echo "[2] RPMsg log"

dmesg | grep -i rpmsg > "$OUTPUT/rpmsg.log" 2>&1 || true

echo
echo "[3] Remoteproc log"

dmesg | grep -i remoteproc > "$OUTPUT/remoteproc.log" 2>&1 || true

echo
echo "[4] Power information"

if [ -d /sys/class/power_supply ]; then
    find /sys/class/power_supply \
        -type f \
        -maxdepth 3 \
        -print \
        > "$OUTPUT/power_files.txt" 2>&1 || true
fi

cat /sys/power/state \
    > "$OUTPUT/power_states.txt" 2>&1 || true

echo
echo "[5] Wakeup sources"

cat /sys/kernel/debug/wakeup_sources \
    > "$OUTPUT/wakeup_sources.log" 2>&1 || true

echo
echo "[6] CPU information"

cat /proc/cpuinfo \
    > "$OUTPUT/cpuinfo.log" 2>&1 || true

echo
echo "[7] Memory information"

cat /proc/meminfo \
    > "$OUTPUT/meminfo.log" 2>&1 || true

echo
echo "Logs collected successfully."
echo "Location: $OUTPUT"
