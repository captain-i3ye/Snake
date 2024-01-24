CC = gcc
CFLAGS = -Wall -Wextra
INCLUDES = -I/usr/include/SDL2
LIBS = -lSDL2 -lm
OBJS = snake.c

all : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(INCLUDES) $(LIBS) -o snake


