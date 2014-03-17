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
  if(expr == NULL) {
    printf("Tree is empty");
    return 0;
  }

  switch (expr->t) {
    case INT:
      printf("%d", expr->intValue->value);
      break;
    case TERM:
      if (expr->term->op == PLUS) {
        printf("(");
        expr_print(expr->term->left);
        printf("+");
        expr_print(expr->term->right);
        printf(")");
        return 1;
      }
      else {
        printf("(");
        expr_print(expr->term->left);
        printf("-");
        expr_print(expr->term->right);
        printf(")");
        return 1;
      }
      break;
    case FACTOR:
      if (expr->term->op == TIMES) {
        printf("(");
        expr_print(expr->term->left);
        printf("*");
        expr_print(expr->term->right);
        printf(")");
        return 1;
      }
      else {
        printf("(");
        expr_print(expr->term->left);
        printf("/");
        expr_print(expr->term->right);
        printf(")");
        return 1;
      }
    break;
    default:
      printf("ERROR: AST is not properly formed\n");
      return 0;
  }
}

int expr_interpret(Expr* expr) {
  if(expr == NULL) {
    printf("Tree is empty");
    return -1;
  }

  switch (expr->t) {
    case INT:
      return expr->intValue->value;
      break;
    case TERM:
      if (expr->term->op == PLUS)
        return expr_interpret(expr->term->left) +
               expr_interpret(expr->term->right);
      else
        return expr_interpret(expr->term->left) -
               expr_interpret(expr->term->right);
      break;
    case FACTOR:
      if (expr->term->op == TIMES)
        return expr_interpret(expr->term->left) *
               expr_interpret(expr->term->right);
      else
        return expr_interpret(expr->term->left) /
               expr_interpret(expr->term->right);        
    break;
    default:
      printf("ERROR: AST is not properly formed\n");
  }
}
