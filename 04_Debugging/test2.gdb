set pagination off
set args -100 100 3

break range.c:41
commands
silent
if (i - start >= 28 * step && i - start <= 35 * step)
  echo @@@ i=
  print i
  echo @@@ start=
  print start
  echo @@@ end=
  print end
  echo @@@ step=
  print step
end
continue
end

run
quit
