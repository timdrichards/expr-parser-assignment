CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: expr-parser

expr-parser: $(OBJS)
	$(CC) $(FLAGS) -o $@ $^

%.o: %.c
	$(CC) $(FLAGS) -c $<

clean:
	rm -f $(ASMS)
	rm -f $(OBJS)
	rm -f expr-parser
	rm -f *~
