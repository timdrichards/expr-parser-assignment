#ifndef __EXPR_AST_H
#define __EXPR_AST_H

typedef struct Term Term;
typedef struct Factor Factor;
typedef struct Int Int;
typedef struct Expr Expr;
typedef enum termop termop;
typedef enum factorop factorop;
typedef enum expr_type expr_type;

enum termop {
  PLUS = 1,
  MINUS = 2
};

enum factorop {
  TIMES = 3,
  DIVIDE = 4
};

enum expr_type {
  INT = 5,
  TERM = 6,
  FACTOR = 7
};

struct Int {
  int value;
};

struct Term {
  termop op;
  Expr* left;
  Expr* right;
};

struct Factor {
  factorop op;
  Expr* left;
  Expr* right;
};

struct Expr {
  union {
    Int* intValue;
    Term* term;
    Factor* factor;
  };
  expr_type t;
};

Expr* make_int(int value);
Expr* make_add(Expr* left, Expr* right);
Expr* make_sub(Expr* left, Expr* right);
Expr* make_mul(Expr* left, Expr* right);
Expr* make_div(Expr* left, Expr* right);
Expr* expr_parse(char* filename);

Expr* parse_term();
Expr* parse_factor();
Expr* parse_int();

void expr_print(Expr* expr);
int expr_interpret(Expr* expr);

#endif
