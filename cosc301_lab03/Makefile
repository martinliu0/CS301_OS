.PHONY: clean

CC=clang
CFLAGS=-Wall -g 

all: fork01 fork03

fork01: fork01.c
	$(CC) -o $@ $^ $(CFLAGS) 

fork03: fork03.c
	$(CC) -o $@ $^ $(CFLAGS) 

clean:
	$(RM) fork01 fork03 *.o *~

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
