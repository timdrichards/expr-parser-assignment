CC = gcc
SRCS = $(wildcard soln-src/*.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: expr-parser doc

dist: expr-parser-assignment.zip

expr-parser-assignment.zip: expr-parser-assignment
	zip -r expr-parser-assignment expr-parser-assignment

expr-parser-assignment: expr-parser doc
	mkdir expr-parser-assignment
	cp expr-parser expr-parser-assignment/expr-parser-soln
	cp -r src expr-parser-assignment/
	cp grammar.txt expr-parser-assignment/
	cp Makefile.student expr-parser-assignment/Makefile
	cp -r test expr-parser-assignment/
	cp doc/expr-parser-assignment.pdf expr-parser-assignment/

doc: doc/expr-parser-assignment.pdf

doc/expr-parser-assignment.pdf: doc/expr-parser-assignment.tex
	cd doc; pdflatex expr-parser-assignment.tex; pdflatex expr-parser-assignment.tex

expr-parser: $(OBJS)
	$(CC) $(FLAGS) -o $@ $^

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(ASMS)
	rm -f $(OBJS)
	rm -f expr-parser
	rm -f *~
	rm -f expr-parser-assignment.zip
	rm -rf expr-parser-assignment
	rm -f doc/*~ doc/*.pdf doc/*.aux doc/*.toc doc/*.log
