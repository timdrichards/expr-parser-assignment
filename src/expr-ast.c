#include <stdio.h>
#include <stdlib.h>
#include "expr-scanner.h"
#include "expr-ast.h"
#include "expr-parser.h"

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
  Factor* factor = malloc(sizeof(Factor));
  factor->left = left;
  factor->right = right;
  factor->op = DIVIDE;
  Expr* e = malloc(sizeof(Expr));
  e->t = FACTOR;
  e->factor = factor;
  return e;
}

int expr_print(Expr* expr) {
  // TODO
  return 0;
}

int expr_interpret(Expr* expr) {
  // TODO
  return -1;
}
