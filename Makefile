CC = gcc
CFLAGS = -ansi -Wall
SRCS = $(wildcard *.c)
EXECS = $(patsubst %.c, %, $(SRCS))

all: $(EXECS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	-rm -f $(EXECS)
