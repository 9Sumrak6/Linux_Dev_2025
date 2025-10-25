#!/bin/sh
set -eu
TMP=$(dirname "$0")/tmp/protect
mkdir -p "$TMP"
IN="$TMP/file_PROTECT.txt"
OUT="$TMP/out.txt"
echo "secret" > "$IN"
echo "old" > "$OUT"

LD_PRELOAD=../libprotect.so ../move "$IN" "$OUT" || rc=$? || true
rc=${rc:-$?}
echo "move rc = $rc"

if [ -e "$IN" ]; then
  echo "protect OK: infile remains"
else
  echo "protect FAILED: infile removed"; exit 1
fi
