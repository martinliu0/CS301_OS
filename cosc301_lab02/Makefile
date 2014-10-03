.PHONY: clean

CC=clang
CFLAGS= -Wall -g 
OBJS=tokenify.o
TARGET=lab02

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) 

clean:
	$(RM) $(OBJS) $(TARGET)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
