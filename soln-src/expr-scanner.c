#include <string.h>
#include "expr-scanner.h"
#include "ctype.h"

#define NL    '\n'
#define TAB   '\t'
#define WS    ' '
#define LP '('
#define RP ')'
#define PLUS '+'
#define MINUS '-'
#define TIMES '*'
#define DIVIDE '/'
#define SEMI ';'
#define OP(c) (c == LP || c == RP || c == PLUS || c == MINUS || c == TIMES || c == DIVIDE)  // macro that checks if character c is any of LP, RP, PLUS, MINUS, TIMES, DIVIDE

/*  The state diagram has the following states:
 *  START_STATE : The scanner remains in this state when it reads a WS/TAB/NL
 *  INT_STATE : The scanner is in this state when it reads an integer token
 *  OP_STATE : The scanner is in this state when it reads an operator - LP, RP, PLUS, MINUS, TIMES, DIVIDE
 *  EOF_STATE : The scanner is in this state when it reaches EOF. Once this state is reached, the scanner stops scanning.
 *  ERROR_STATE : The scanner is in this state when is reads any character that is not represented by the states above. If this state is reached, the program should exit with
 *  an error message.
 */

typedef enum state state;
enum state {
  START_STATE = 1, 
  INT_STATE = 2, 
  OP_STATE = 3,
  SEMI_STATE = 4,
  EOF_STATE   = 5, 
  ERROR_STATE = 6 
};

// function that determines the type of operator read

TOKEN_TYPE whatOP(char c) {
  if (c == LP) return TOK_LP;
  if (c == RP) return TOK_RP;
  if (c == PLUS) return TOK_PLUS;
  if (c == MINUS) return TOK_MINUS;
  if (c == TIMES) return TOK_TIMES;
  return TOK_DIVIDE;
}

Token scan(FILE* fp) {
  // The character we are reading in:
  static char c;

  // Indicates if this is the first call to scan:
  static int first_time = 1;

  // If this is the first call
  if (first_time) {
    c = getc(fp);
    first_time = 0;
  }

  // We begin in the start state:
  static state curr_state = START_STATE;

  // The token to return to the caller:
  Token token;

  // An index used to remember the value characters:
  int value_idx = -1;

  // Run the machine:
  while (1) {
    switch (curr_state) {
    case START_STATE:
      if (c == TAB || c == WS || c == NL) {
    	curr_state = START_STATE;
	c = getc(fp);
      }
      else if (OP(c)) {
    	curr_state = OP_STATE;
      }
      else if (c == SEMI) {
    	curr_state = SEMI_STATE;
      }
      else if (c == EOF) {
	curr_state = EOF_STATE;
      }
      else if (isdigit(c)){
    	curr_state = INT_STATE;
      }
      else {
        token.value[++value_idx] = c;
	token.value[++value_idx] = '\0';
        token.t = TOK_ERROR;
	return token;
      }
      break;

    case INT_STATE:
      if (c == SEMI) {
        token.value[++value_idx] = '\0';
	token.t = TOK_INT;
	curr_state = SEMI_STATE;
	return token;
      }
      else if (OP(c)) {
        token.value[++value_idx] = '\0';
	curr_state = OP_STATE;
	token.t = TOK_INT;
	return token;
      }
      else if (c == TAB || c == WS || c == NL) {
        token.value[++value_idx] = '\0';
	curr_state = START_STATE;
	token.t = TOK_INT;
	c = getc(fp);
	return token;
      }
      else if (c >= '0' && c <= '9'){
        token.value[++value_idx] = c;
	curr_state = INT_STATE;
	c = getc(fp);
      }
      else {
        token.value[++value_idx] = c;
	token.value[++value_idx] = '\0';
        token.t = TOK_ERROR;
	return token;
      }
      break;

    case SEMI_STATE:
      token.value[++value_idx] = ';';
	token.value[++value_idx] = '\0';
      token.t = TOK_SEMI;
      c = getc(fp);
      curr_state = START_STATE;
      return token;
      break;

    case OP_STATE:
      if (OP(c)) {
    	token.value[++value_idx] = c;
	token.value[++value_idx] = '\0';
    	curr_state = START_STATE;
	token.t = whatOP(token.value[value_idx - 1]);
	c = getc(fp);
	return token;
      }
      else if (c == SEMI) {
    	curr_state = SEMI_STATE;
      }
      else if (c == TAB || c == WS || c == NL) {
	curr_state = START_STATE;
      }
      else if (c == EOF) {
	curr_state = EOF_STATE;
      }
      else if (isdigit(c)){ // value character
	curr_state = INT_STATE;
      }
      else {
        token.value[++value_idx] = c;
	token.value[++value_idx] = '\0';
        token.t = TOK_ERROR;
	return token;
      }
      break;

    case EOF_STATE:
      sprintf(token.value, "end of file");
      token.t = TOK_ENDOFFILE;
      curr_state = EOF_STATE;
      return token;

    default:
      token.t = TOK_ERROR;
      sprintf(token.value, "unexpected input character: %c", c);
      return token;
    }
  }
}

int tok_str(char* s, TOKEN_TYPE t) {
  switch (t) {
  case TOK_INT:
    strcpy(s, "INT");
    return 1;
  case TOK_SEMI:
    strcpy(s, "SEMI");
    return 1;
  case TOK_NEWLINE:
    strcpy(s, "Newline");
    return 1;
  case TOK_ENDOFFILE:
    strcpy(s, "EndOfFile");
    return 1;
  case TOK_ERROR:
    strcpy(s, "Error");
    return 1;
  case TOK_LP:
    strcpy(s, "LP");
    return 1;
  case TOK_RP:
    strcpy(s, "RP");
    return 1;
  case TOK_PLUS:
    strcpy(s, "PLUS");
    return 1;
  case TOK_MINUS:
    strcpy(s, "MINUS");
    return 1;
  case TOK_TIMES:
    strcpy(s, "TIMES");
    return 1;
  case TOK_DIVIDE:
    strcpy(s, "DIVIDE");
    return 1;
  default:
    return 0;
  }
}
