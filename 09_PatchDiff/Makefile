CC = gcc
CFLAGS = -Wall -Wextra -O2

SRC0 = maze.c
SRC1 = maze_size.c
SRC2 = maze_symbols.c
SRC3 = maze_seed.c

BIN0 = maze0
BIN1 = maze1
BIN2 = maze2
BIN3 = maze3

all: $(BIN0) $(BIN1) $(BIN2) $(BIN3) run

$(BIN0): $(SRC0)
	$(CC) $(CFLAGS) $< -o $@

$(SRC1): $(SRC0) patches/0001-size.patch
	patch -o $@ $< patches/0001-size.patch

$(SRC2): $(SRC1) patches/0002-symbols.patch
	patch -o $@ $< patches/0002-symbols.patch

$(SRC3): $(SRC2) patches/0003-seed.patch
	patch -o $@ $< patches/0003-seed.patch

$(BIN1): $(SRC1)
	$(CC) $(CFLAGS) $< -o $@

$(BIN2): $(SRC2)
	$(CC) $(CFLAGS) $< -o $@

$(BIN3): $(SRC3)
	$(CC) $(CFLAGS) $< -o $@

run: all
	./maze0
	./maze1 12
	./maze2 ".#" 12
	./maze3 42 ".#" 12

clean:
	rm -f maze? maze_*.c
