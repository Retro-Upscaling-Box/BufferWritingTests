CC = gcc
CFLAGS = -std=c11 -O3

EXEC = fb

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,%.o,$(SRC))

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(CFLAGS) $(OBJ)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC) *.o