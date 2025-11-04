CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -Isrc
LDFLAGS = 

TARGET = batalha_naval

SRCS = src/main.c \
       src/board.c \
       src/fleet.c \
       src/game.c \
       src/io.c \
       src/rnd.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean