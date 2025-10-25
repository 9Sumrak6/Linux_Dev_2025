CC = gcc
CFLAGS = -Wall -Wextra -O2 -fPIC
LDFLAGS = -ldl

all: move libprotect.so libfail.so

move: move.c
	$(CC) $(CFLAGS) -o move move.c

libprotect.so: libprotect.c
	$(CC) $(CFLAGS) -shared -o libprotect.so libprotect.c -ldl

libfail.so: libfail.c
	$(CC) $(CFLAGS) -shared -o libfail.so libfail.c -ldl

test: all
	@./tests/run_all_tests.sh

clean:
	rm -f move libprotect.so libfail.so
	rm -rf tests/tmp tests/logs
