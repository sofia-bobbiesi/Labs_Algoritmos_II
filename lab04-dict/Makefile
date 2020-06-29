CFLAGS = -Wall -Werror -Wextra -pedantic  -no-pie -std=c99 -g 
CC = gcc
TARGET = dict
OBJS = $(SRCS:.c=.o)
SRCS = string.c helpers.c main.c dict_helpers.c dict.c 

all: 	$(OBJS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) 

.c.o:
	$(CC) $(CFLAGS)  -c $<  -o $@

clean:
	$(RM) $(OBJS) $(TARGET) *~ $(MAIN)

valgrind: all 
	valgrind --show-reachable=yes --leak-check=full ./$(TARGET)
