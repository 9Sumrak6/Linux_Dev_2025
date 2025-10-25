#!/bin/sh
set -eu
TMP=$(dirname "$0")/tmp/basic
mkdir -p "$TMP"
echo "hello world" > "$TMP/infile"
echo "OLD" > "$TMP/outfile"


./move "$TMP/infile" "$TMP/outfile"
rc=$?
if [ "$rc" -ne 0 ]; then
  echo "move failed rc=$rc"
  exit 1
fi

echo "here" 
if [ -e "$TMP/infile" ]; then
  echo "infile still present"
  exit 1
fi

if ! grep -q "hello world" "$TMP/outfile"; then
  echo "outfile content wrong"
  exit 1
fi

echo "basic ok"
