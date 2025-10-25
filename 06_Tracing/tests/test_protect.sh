#!/bin/sh
set -eu
TMP=$(dirname "$0")/tmp/protect
mkdir -p "$TMP"
IN="$TMP/file_PROTECT.txt"
OUT="$TMP/out.txt"
echo "secret" > "$IN"
echo "old" > "$OUT"

# run move with libprotect preloaded (path from repo root)
LD_PRELOAD=../libprotect.so ../move "$IN" "$OUT" || rc=$? || true
rc=${rc:-$?}
echo "move rc = $rc"

# infile should remain because unlink should have failed due to libprotect
if [ -e "$IN" ]; then
  echo "protect OK: infile remains"
else
  echo "protect FAILED: infile removed"; exit 1
fi
