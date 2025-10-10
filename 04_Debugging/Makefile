CC = gcc
CFLAGS = -O0 -g
TARGET = range
GDB = gdb
GDB_FLAGS = --batch --quiet

REF1 = test1.ref
REF2 = test2.ref
OUT1 = out1.txt
OUT2 = out2.txt

.PHONY: all test clean

all: $(TARGET)

$(TARGET): range.c
	$(CC) $(CFLAGS) -o $@ $<

test: $(TARGET) $(REF1) $(REF2)
	@echo "Running GDB tests..."

	@echo "[TEST 1] Running test1.gdb..."
	@$(GDB) $(GDB_FLAGS) -x test1.gdb ./$(TARGET) 2>&1 | grep '^@@@' > $(OUT1) || true
	@diff -u $(REF1) $(OUT1) && echo "\033[32mTest 1: PASS\033[0m" || echo "\033[31mTest 1: FAIL\033[0m"

	@echo "[TEST 2] Running test2.gdb..."
	@$(GDB) $(GDB_FLAGS) -x test2.gdb ./$(TARGET) 2>&1 | grep '^@@@' > $(OUT2) || true
	@diff -u $(REF2) $(OUT2) && echo "\033[32mTest 2: PASS\033[0m" || echo "\033[31mTest 2: FAIL\033[0m"

	@echo "Done."

clean:
	rm -f $(TARGET) $(OUT1) $(OUT2)
