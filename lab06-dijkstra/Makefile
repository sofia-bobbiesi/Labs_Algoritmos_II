CFLAGS = -Wall -Werror -Wextra -pedantic  -no-pie -std=c99 -g -I.
CC = gcc
TARGET = dijkstra
OBJS = $(SRCS:.c=.o)
SRCS = cost.c dijkstra.c main.c graph.c
STAR = dijkstra_star
STARSRCS = cost.c dijkstra.c main_star.c graph.c
STAROBJS = $(STARSRCS:.c=.o)
INPUTDIR = input/



all: 	$(OBJS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) set.o
	@read -p "Input file name:  "  FILE; ./$(TARGET) $(INPUTDIR)$$FILE

star: $(STAROBJS)
	$(CC) $(CFLAGS) -o $(STAR) $(STAROBJS) set.o
	./$(STAR) 

.c.o:
	$(CC) $(CFLAGS)  -c $<  -o $@

.PHONY: clean

clean:
	$(RM) $(OBJS) $(STAROBJS) *~ $(MAIN)

valgrind: 
	@read -p "Input file name:  " FILE; valgrind --leak-check=full ./$(TARGET) $(INPUTDIR)$$FILE

valgrind_star: 
	 valgrind --leak-check=full ./$(STAR)