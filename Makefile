PROG = memtest
OBJS = debug_memory.o test.o
CC = gcc
CFLAGS = -Wall
LDFLAGS =

.PHONY: all
all: $(PROG)

.SUFFIXES: .o .c
.c.o:
	$(CC) $(CFLAGS) -c $<

$(PROG): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(PROG) $(OBJS)
