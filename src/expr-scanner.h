#ifndef __TOKEN_H
#define __TOKEN_H

#include <stdio.h>

#define MAX_VALUE_SIZE 100
#define TOKEN_STR_LEN  50

typedef enum TOKEN_TYPE TOKEN_TYPE;
enum TOKEN_TYPE {
  TOK_NEWLINE,
  TOK_ENDOFFILE,
  TOK_ERROR,
  TOK_LP,
  TOK_RP,
  TOK_PLUS,
  TOK_MINUS,
  TOK_TIMES,
  TOK_DIVIDE,
  TOK_SEMI,
  TOK_INT
};

typedef struct Token Token;
struct Token {
  TOKEN_TYPE t;
  char value[MAX_VALUE_SIZE];
};

Token scan(FILE* fp);
int tok_str(char* s, TOKEN_TYPE t);
TOKEN_TYPE whatOP(char c);

#endif
