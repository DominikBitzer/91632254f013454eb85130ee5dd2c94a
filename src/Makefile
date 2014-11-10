CC=gcc
CFLAGS=-std=c99 -Wall -Werror -g
OBJECTS=utils.o config.o performConnection.o main.o

all: client

client: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o client

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean: 
	rm -rf *.o client
