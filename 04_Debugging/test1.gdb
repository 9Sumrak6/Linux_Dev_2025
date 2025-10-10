set pagination off
set args 1 12

break range.c:41
commands
silent
if (i % 5 == 0)
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
