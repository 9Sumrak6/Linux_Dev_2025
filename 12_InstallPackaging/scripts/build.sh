#!/bin/sh
set -e

echo "[1/3] Generate usage.md"
number-game --help-md > doc/usage.md

if command -v doxygen >/dev/null 2>&1; then
    echo "[2/3] Run doxygen"
    doxygen doc/Doxyfile
else
    echo "[2/3] WARNING: doxygen not found, skipping"
fi

echo "[3/3] Done"
