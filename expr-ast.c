#include <stdio.h>
#include <stdlib.h>
#include "expr-ast.h"
#include "exp-scanner.h"

// Pointer to the AST
Expr* expr = NULL;

// Next token that will be read
Token token;

// Input file
FILE* fp;

Expr* make_int(int value) {
  Int* i = malloc(sizeof(Int));
  i->value = value;
  Expr* e = malloc(sizeof(Expr));
  e->t = INT;
  e->intValue = i;
  return e;
}

Expr* make_add(Expr* left, Expr* right) {
  Term* term = malloc(sizeof(Term));
  term->left = left;
  term->right = right;
  term->op = PLUS;
  Expr* e = malloc(sizeof(Expr));
  e->t = TERM;
  e->term = term;
  return e;
}

Expr* make_sub(Expr* left, Expr* right) {
  Term* term = malloc(sizeof(Term));
  term->left = left;
  term->right = right;
  term->op = MINUS;
  Expr* e = malloc(sizeof(Expr));
  e->t = TERM;
  e->term = term;
  return e;
}

Expr* make_mul(Expr* left, Expr* right) {
  // TODO!
  Factor* factor = malloc(sizeof(Factor));
  factor->left = left;
  factor->right = right;
  factor->op = TIMES;
  Expr* e = malloc(sizeof(Expr));
  e->t = FACTOR;
  e->factor = factor;
  return e;
}

Expr* make_div(Expr* left, Expr* right) {
  // TODO
  Factor* factor = malloc(sizeof(Factor));
  factor->left = left;
  factor->right = right;
  factor->op = DIVIDE;
  Expr* e = malloc(sizeof(Expr));
  e->t = FACTOR;
  e->factor = factor;
  return e;
}

Expr* expr_parse(char* filename) {
  // TODO
  fp = fopen(filename, "r");
  token = scan(fp);
  
//  while(token.t != TOK_SEMI && token.t != EOF) {
//  
//  Parse the input file. The entire AST is a term which is also an expression.
    Expr* e = parse_term();
//  }
    return e;
}

Expr* parse_term() {
  Expr* e;

  // If the input token is not plus then it must be TOK_TIMES or INT
  if(token.t != TOK_PLUS) {
    e = parse_factor();
    // token = scan(fp); This shouldn't be executed since parse_factor() might have 
    // returned after reading a TOKEN_PLUS and we don't want to overwrite it.
  }

  // If the input token is TOK_PLUS, read the next token to see if that is another 
  // operator or an INT and process it accordingly. Note that the second argument to 
  // the make_add() function is the expression that was returned in the previous if statement.
  // This could be another sub tree or just an integer as described in the grammar.
  if(token.t == TOK_PLUS) {
    token = scan(fp);
    e = make_add(parse_term(), e);
  }

  return e;
}

// The parse_factor is similar to the parse_term except that we check for TIMES instead of
// PLUS. The sequence of operations is the same as before.

Expr* parse_factor() {
  Expr* e;
  if(token.t != TOK_TIMES) {
    e = parse_int();
    token = scan(fp);
  }
  if(token.t == TOK_TIMES) {
    token = scan(fp);
    e = make_mul(parse_factor(), e);    
  }
  return e;
}

Expr* parse_int() {
  if(token.t == TOK_SEMI || token.t == TOK_ENDOFFILE) {
    printf("reached semi\n");
    exit(0);
  }
  Expr* e = make_int(atoi(token.value));
//  printf("%d\n",atoi(token.value));
  return e;

}


void expr_print(Expr* expr) {
  // TODO
}

int expr_interpret(Expr* expr) {
  // TODO

  if(expr == NULL) {
    printf("Tree is empty");
    return 0;
  }
  if(expr->t != INT) {
    if(expr->t == TERM) {
      if(expr->term->op == PLUS) {
        return (expr_interpret(expr->term->left) + expr_interpret(expr->term->right));
      }
    }
    if(expr->t == FACTOR) {
      if(expr->factor->op == TIMES) {
        return (expr_interpret(expr->factor->left) * expr_interpret(expr->factor->right));
      }
    }
  }
  else if(expr->t == INT) {
    return (expr->intValue->value);
  }
  return 0;
}

int main(int argc, char* argv[]) {
  if(argc !=2 ) {
    fprintf(stderr,"usage: exp-ast FILE\n");
    exit(1);
  }
  printf("Expr AST\n");
  expr = expr_parse(argv[1]);
  printf(" expr_interpret(expr) = %d\n",expr_interpret(expr));
}
