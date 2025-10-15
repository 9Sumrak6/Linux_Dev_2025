CC = gcc
CFLAGS = -O0 -g
TARGET = esub

.PHONY: all clean test

all: $(TARGET)

$(TARGET): esub.c
	$(CC) $(CFLAGS) -o $@ $<

test: $(TARGET)
	@echo "Running tests..."
	@echo "Test 1: simple substitution"
	@./$(TARGET) 'o' 'O' hello | diff -u <(echo hello | sed -E 's/o/O/') - && echo "PASS" || echo "FAIL"

	@echo "Test 2: group substitution"
	@./$(TARGET) '(foo)(bar)' '\2-\1' foobar | diff -u <(echo foobar | sed -E 's/(foo)(bar)/\2-\1/') - && echo "PASS" || echo "FAIL"

clean:
	rm -f $(TARGET)
