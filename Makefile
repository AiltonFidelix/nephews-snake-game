TARGET = snake

CC = gcc
CFLAGS = -I.
DEBUG = -g
LIBS = -lncurses
DEPS = snake.h
SRCS = snake.c
OBJ = snake.o

%.o: $(SRCS) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) $(DEBUG) -o $(TARGET) main.c $(OBJ) $(CFLAGS) $(LIBS)

clean:
	rm $(OBJ) $(TARGET)