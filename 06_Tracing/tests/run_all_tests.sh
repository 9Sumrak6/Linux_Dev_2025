#!/bin/sh
set -eu
HERE=$(dirname "$0")
mkdir -p "$HERE/tmp" "$HERE/logs"
rm -f "$HERE/logs"/*

echo "1) basic success test..."
"$HERE"/test_basic.sh > "$HERE/logs/basic.txt" 2>&1 || { echo "basic failed — see logs"; exit 1; }
echo "OK"

echo "2) try strace injection tests (if supported), otherwise fallback to LD_PRELOAD libfail..."
"$HERE"/test_strace_or_preload.sh > "$HERE/logs/inject.txt" 2>&1 || { echo "inject tests failed — see logs"; exit 1; }
echo "OK"

echo "3) LD_PRELOAD protect test..."
"$HERE"/test_protect.sh > "$HERE/logs/protect.txt" 2>&1 || { echo "protect failed — see logs"; exit 1; }
echo "OK"

echo "All tests done. Logs in $HERE/logs/"
