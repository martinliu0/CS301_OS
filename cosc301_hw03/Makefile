.PHONY: clean

CC=clang
CFLAGS=-Wall -g 

all: problem1 problem2

problem1: arrayrec.o
	$(CC) -o $@ $^ $(CFLAGS) 

problem2: list.o
	$(CC) -o $@ $^ $(CFLAGS) 

clean:
	$(RM) arrayrec.o list.o problem?

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
