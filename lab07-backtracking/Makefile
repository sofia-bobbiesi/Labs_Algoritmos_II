CFLAGS = -Wall -Werror -Wextra -pedantic  -no-pie -std=c99 -g
CC = gcc
TARGET = knapsack
OBJS = $(SRCS:.c=.o)
SRCS = helpers.c item.c knapsack.c string.c main.c

all: 	$(OBJS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) 

.c.o:
	$(CC) $(CFLAGS)  -c $<  -o $@

.PHONY: clean

clean:
	$(RM) $(OBJS) *~ $(TARGET)
