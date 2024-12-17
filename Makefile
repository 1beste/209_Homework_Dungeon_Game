
---

## `Makefile`

```makefile
# Makefile for Dungeon Adventure Game

CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = dungeon_game
SRCS = dungeon_game.c
HEADER = homeworkHeader.h

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADER)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)


