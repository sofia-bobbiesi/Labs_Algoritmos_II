CFLAGS = -Wall -Werror -Wextra -pedantic  -no-pie -std=c99 -g
CC = gcc
TARGET = queue
OBJS = $(SRCS:.c=.o)
SRCS = queue.c main.c

all: 	$(OBJS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) 

.c.o:
	$(CC) $(CFLAGS)  -c $<  -o $@

.PHONY: clean

clean:
	$(RM) $(OBJS) *~ $(TARGET)

valgrind: 
	valgrind --show-reachable=yes --leak-check=full ./$(TARGET)