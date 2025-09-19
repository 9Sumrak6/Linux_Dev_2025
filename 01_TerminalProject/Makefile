CC = cc
CFLAGS = -Wall -Wextra -pedantic -std=c11
LDFLAGS = -lncurses

TARGET = Show

all: $(TARGET)

$(TARGET): Show.c
	$(CC) $(CFLAGS) -o $(TARGET) Show.c $(LDFLAGS)

clean:
	rm -f $(TARGET)