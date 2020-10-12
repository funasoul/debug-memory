PROG = memtest
OBJS = debug_memory.o
TEST_OBJS = test.o
CC = gcc
CFLAGS = -Wall
#CFLAGS = -Wall -g -DDEBUG_MEMORY_DEBUG
LDFLAGS =

.PHONY: all
all: $(PROG)

run: all
	./$(PROG)

$(TEST_OBJS): EXTRA_FLAGS := -Wno-unused-variable

.SUFFIXES: .o .c
.c.o:
	$(CC) $(CFLAGS) $(EXTRA_FLAGS) -c $<

$(PROG): $(OBJS) $(TEST_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(PROG) $(OBJS) $(TEST_OBJS)
