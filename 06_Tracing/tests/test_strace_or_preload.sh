#!/bin/sh
set -eu
TMPDIR=$(dirname "$0")/tmp/inject
mkdir -p "$TMPDIR"
LIBFAIL="../libfail.so"
MOVE="../../move"

# prepare basic files
prepare_case() {
  CASE="$TMPDIR/case_$1"
  rm -rf "$CASE"
  mkdir -p "$CASE"
  echo "DATA" > "$CASE/in"
  echo "OLD" > "$CASE/out"
  echo "$CASE"
}

run_and_check() {
  CASE="$1"
  shift
  CMD="$@"
  # run command
  sh -c "$CMD"
  rc=$?
  echo "rc=$rc"
  # infile should exist if failure happened BEFORE unlink (we expect that)
  if [ -e "$CASE/in" ]; then
    echo "infile exists (expected on failure)"
  else
    echo "infile removed"
  fi
  return $rc
}

# check if strace supports inject option by printing help and grepping
if strace -V 2>&1 | grep -q 'inject'; then
  STRACE_OK=1
else
  # some strace versions don't print 'inject' in -V; try a small help check
  if strace -h 2>&1 | grep -q 'inject'; then STRACE_OK=1; else STRACE_OK=0; fi
fi

echo "strace inject support: $STRACE_OK"

# list of syscalls to test via injection and expected behavior:
CASES="open read write rename unlink"

for sc in $CASES; do
  CASEDIR=$(prepare_case "$sc")
  if [ "$STRACE_OK" -eq 1 ]; then
    echo "Trying strace-inject for $sc (if your strace supports exact syntax, adjust if needed)..."
    # Common strace inject syntax (many distributions support: -e inject=SYSCALL:when=1:error=EIO)
    # If it fails because of syntax, the following will return nonzero; we then fallback below.
    set +e
    strace -o /dev/null -e inject=$sc:when=1:error=EIO "$MOVE" "$CASEDIR/in" "$CASEDIR/out"
    rc=$?
    set -e
    if [ $rc -ne 0 ]; then
      echo "strace-inject run returned $rc; will fallback to LD_PRELOAD for $sc"
      # fallback to libfail
      export FAIL_SYSCALL="$sc"
      export FAIL_AFTER=1
      export FAIL_ERRNO=EIO
      LD_PRELOAD="$LIBFAIL" "$MOVE" "$CASEDIR/in" "$CASEDIR/out" || true
      unset FAIL_SYSCALL FAIL_AFTER FAIL_ERRNO
    fi
  else
    echo "No strace inject support detected — using LD_PRELOAD libfail for $sc"
    export FAIL_SYSCALL="$sc"
    export FAIL_AFTER=1
    export FAIL_ERRNO=EIO
    LD_PRELOAD="$LIBFAIL" "$MOVE" "$CASEDIR/in" "$CASEDIR/out" || true
    unset FAIL_SYSCALL FAIL_AFTER FAIL_ERRNO
  fi

  # Check that infile was NOT removed (expected on failures)
  if [ -e "$CASEDIR/in" ]; then
    echo "OK: infile remains after induced failure ($sc)"
  else
    echo "FAIL: infile removed for case $sc"
    exit 1
  fi
done

echo "inject tests done"
