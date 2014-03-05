CC = gcc
SRCS = $(wildcard soln-src/*.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: expr-parser

expr-parser: $(OBJS)
	$(CC) $(FLAGS) -o $@ $^

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(ASMS)
	rm -f $(OBJS)
	rm -f expr-parser
	rm -f *~
