#include <stdlib.h>
#include "expr-scanner.h"
#include "expr-ast.h"
#include "expr-parser.h"

// Pointer to the AST
Expr* expr = NULL;

// Next token that will be read
Token token;

// Input file:
FILE* fp = NULL;

// Function prototypes:
Expr* parse_expr();
Expr* parse_expr_prime(Expr* right);
Expr* parse_term();
Expr* parse_term_prime(Expr* right);
Expr* parse_factor();
Expr* parse_prim();
Expr* parse_int();

/**
 * Matches a token type with the current token type. If they
 * match we advance the scanner forward and return 1. If they 
 * do not match we do not advance the scanner and return 0.
 */
int consume(TOKEN_TYPE ttype) {
  if (token.t == ttype) {
    token = scan(fp);
    return 1;
  }
  else {
    return 0;
  }
}

/**
 * Checks the token type with the current token type. Returns
 * 1 if they match; 0 otherwise.
 */
int match(TOKEN_TYPE ttype) {
  if (token.t == ttype) {
    return 1;
  }
  else {
    return 0;
  }
}

/**
 * This is the main entry point to the parser. Its first and
 * only argument is the name of a file (filename) containing
 * an expression. It returns an Expr AST. It corresponds to the
 * first production rule in the simple expression grammar
 * (see grammar.txt):
 *
 *   line => expr SEMI
 *
 */
Expr* expr_parse(char* filename) {
  // First, we open the file and check for errors:
  fp = fopen(filename, "r");

  if (fp == NULL) {
    printf("ERROR: %s does not exist.\n", filename);
    exit(1);
  }

  // Next, scan the first token in and begin the parsing process:
  token = scan(fp);
  Expr* e = parse_expr();

  // The very last token must be a ';'. If it is not, it is an error:
  if (!match(TOK_SEMI)) {
    printf("ERROR: expected ;, found %s\n", token.value);
    exit(1);    
  }

  // Return the constructed Expr AST:
  return e;
}

/**
 * The parse_expr function corresponds to the second rule
 * in the simple expression grammar (see grammar.txt):
 *
 *   expr => term expr_prime
 *
 * It returns an expression.
 *
 */
Expr* parse_expr() {
  // TODO
  return NULL;
}

/**
 * The parse_expr_prime function corresponds to the third rule
 * in the simple expression grammar (see grammar.txt):
 *
 *   expr_prime => PLUS expr
 *              |  MINUS expr
 *              |  <empty>
 *
 * This rule allows us to recognize a PLUS or MINUS followed by
 * an expression. To construct the proper AST structure we must
 * pass in the left-hand side of the expression.
 *
 * It returns a new expression based on the matched operator or
 * the `left` expression passed into it if it does not match a
 * PLUS or MINUS (this corresponds to the <empty> part of the
 * rule).
 *
 */
Expr* parse_expr_prime(Expr* left) {
  Expr* e = NULL;
  // TODO
  return e;
}

/**
 * The parse_term function corresponds to the fourth rule
 * in the simple expression grammar (see grammar.txt):
 *
 *   term => factor term_prime
 *
 * It will parse the left-hand side of a term (a factor)
 * followed by the rest of the factor (parse_term_prime).
 *
 * It returns a term expression.
 *
 */
Expr* parse_term() {
  // TODO
  return NULL;  
}

/**
 * The parse_term_prime function corresponds to the fifth rule
 * in the simple expression grammar (see grammar.txt):
 *
 *   expr_prime => TIMES term
 *              |  DIVIDE term
 *              |  <empty>
 *
 * This rule allows us to recognize a TIMES or DIVIDE followed by
 * a term. To construct the proper AST structure we must
 * pass in the left-hand side of the expression.
 *
 * It returns a new expression based on the matched operator or
 * the `left` expression passed into it if it does not match a
 * TIMES or DIVIDE (this corresponds to the <empty> part of the
 * rule).
 *
 */
Expr* parse_term_prime(Expr* left) {
  Expr* e = left;
  // TODO
  return e;
}

/**
 * The parse_factor function corresponds to the sixth rule
 * in the simple expression grammar (see grammar.txt):
 *
 *   factor => int
 *          |  LP expr RP
 *
 * This rule allows us to recognize an `int` or an expression
 * contained within parenthesis.
 *
 * It returns an expression.
 *
 */
Expr* parse_factor() {
  Expr* e = NULL;
  if (match(TOK_INT)) {
    e = make_int(atoi(token.value));    
    consume(TOK_INT);
  }
  else if (consume(TOK_LP)) {
    e = parse_expr();
    if (consume(TOK_RP)) {
      // do nothing more
    }
    else {
      printf("ERROR: expected ), found %s\n", token.value);
      exit(1);
    }
  }
  else {
    printf("ERROR: expected int or (, found %s\n", token.value);
    exit(1);    
  }
  return e;
}
