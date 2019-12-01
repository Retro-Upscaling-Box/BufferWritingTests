CC = gcc
CFLAGS = -std=c11 -O3 -g -Wall

EXEC = fb

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,%.o,$(SRC))

all: $(EXEC)

run: $(EXEC)
	./$<

test: $(EXEC)
	valgrind --leak-check=full ./$<

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(CFLAGS) $(OBJ)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC) *.o
