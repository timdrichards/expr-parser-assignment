
all: expr-ast

expr-ast: expr-ast.o exp-scanner.o
	gcc expr-ast.o exp-scanner.o -o expr-ast

expr-ast.o: expr-ast.c expr-ast.h
	gcc -c expr-ast.c

exp-scanner.o: exp-scanner.c exp-scanner.h
	$(CC) $(FLAGS) -c exp-scanner.c


clean:
	rm -f *.o *~
	rm -f expr-ast
