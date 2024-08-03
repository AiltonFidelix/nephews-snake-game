TARGET = snake
CC = gcc
CFLAGS = -I. -Wall
DEBUG = -g
LIBS = -lncurses
DEPS = snake.h
SRCS = snake.c
OBJ = snake.o

$(TARGET): $(OBJ)
	$(CC) $(DEBUG) -o $(TARGET) main.c $(OBJ) $(CFLAGS) $(LIBS)

$(OBJ): $(SRCS) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

default: $(TARGET)
	
run: default
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)