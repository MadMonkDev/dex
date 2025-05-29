
CC=gcc
CFLAGS=-Wall -I.

SRC=app/src/dex.c
OBJ=$(SRC:.c=.o)
BIN=dex

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

clean:
	rm -f $(BIN)

