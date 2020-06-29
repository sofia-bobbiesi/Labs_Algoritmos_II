CFLAGS = -Wall -Werror -Wextra -pedantic  -no-pie -std=c99 -g
CC = gcc
TARGET = set
OBJS = $(SRCS:.c=.o)
SRCS = test_set.c set.c

all: 	$(OBJS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) list-x86_64.o

.c.o:
	$(CC) $(CFLAGS)  -c $<  -o $@

.PHONY: clean

clean:
	$(RM) $(OBJS) *~ $(TARGET)

valgrind: all
	valgrind --show-reachable=yes --leak-check=full ./$(TARGET)
