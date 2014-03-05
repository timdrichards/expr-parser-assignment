#include <stdio.h>
#include <stdlib.h>
#include "expr-ast.h"
#include "expr-parser.h"

int main(int argc, char* argv[]) {
  if(argc !=2 ) {
    fprintf(stderr,"usage: expr-parser FILE\n");
    exit(1);
  }
  
  Expr* expr = expr_parse(argv[1]);
  printf("expr = ");
  expr_print(expr);
  printf("\n%d\n", expr_interpret(expr));
}
