#!/bin/sh
set -e

RHASHER="../src/rhasher"

echo "hello" > test.txt
echo "world" > test2.txt

EXPECTED=$(sha1sum test.txt | cut -d' ' -f1)
ACTUAL=$(printf "SHA1 test.txt\n" | $RHASHER)
[ "$EXPECTED" = "$ACTUAL" ] || { echo "SHA1 file test FAILED!"; exit 1; }

EXPECTED=$(md5sum test.txt | cut -d' ' -f1)
ACTUAL=$(printf "MD5 test.txt\n" | $RHASHER)
[ "$EXPECTED" = "$ACTUAL" ] || { echo "MD5 file test FAILED!"; exit 1; }

EXPECTED=$(printf "TTH test.txt\n" | $RHASHER)
ACTUAL=$(printf "TTH test.txt\n" | $RHASHER)
[ "$EXPECTED" = "$ACTUAL" ] || { echo "TTH file test FAILED!"; exit 1; }

EXPECTED=$(echo -n "hello" | sha1sum | cut -d' ' -f1)
ACTUAL=$(printf "SHA1 \"hello\"\n" | $RHASHER)
[ "$EXPECTED" = "$ACTUAL" ] || { echo "SHA1 string test FAILED!"; exit 1; }

EXPECTED=$(echo -n "hello" | md5sum | cut -d' ' -f1)
ACTUAL=$(printf "MD5 \"hello\"\n" | $RHASHER)
[ "$EXPECTED" = "$ACTUAL" ] || { echo "MD5 string test FAILED!"; exit 1; }

EXPECTED=$(printf "TTH \"hello\"\n" | $RHASHER)
ACTUAL=$(printf "TTH \"hello\"\n" | $RHASHER)
[ "$EXPECTED" = "$ACTUAL" ] || { echo "TTH string test FAILED!"; exit 1; }

rm -f test.txt test2.txt
echo "All tests passed!"
