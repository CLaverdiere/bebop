/* This file contains lex code for the scanner of the language. */

%{

#include <cstdlib>

#include "parser.tab.hh"

extern int line_num;

%}

%%

\<>.*$ {
  /* Comments! */
  /* Single line, not multi-line. */
  /* This just eats them. */
}

"**" {
  /* Exponentiation operator */
  return POW;
}

== {
  /* Relational operators */
  /* Equal */
  return EQ;
}

!= {
  /* Not equal */
  return NEQ;
}

> {
  /* Greater than */
  return GT;
}

>= {
  /* Greater than or equal to*/
  return GEQ;
}

\< {
  /* Less than */
  return LT;
}

\<= {
  /* Less than or equal to*/
  return LEQ;
}

type {
  /* User defined type keyword */
  return UTYPE;
}

(not|and|or) {
  /* Boolean Logic Type */
  if (strcmp(yytext, "not") == 0) return L_NOT;
  else if (strcmp(yytext, "and") == 0) return L_AND;
  else if (strcmp(yytext, "or") == 0) return L_OR;
}

(bool|float|int|none|string) {
  /* Variable Type */
  if (strcmp(yytext, "bool") == 0) yylval.type_val = BBBOOL;
  else if (strcmp(yytext, "float") == 0) yylval.type_val = BBFLOAT;
  else if (strcmp(yytext, "int") == 0) yylval.type_val = BBINT;
  else if (strcmp(yytext, "none") == 0) yylval.type_val = BBNONE;
  else if (strcmp(yytext, "string") == 0) yylval.type_val = BBSTR;
  return TYPE;
}

if {
  /* Conditional (if statement). */
  return COND;
}

while {
  /* Loop conditional (while statement). */
  return LOOP_COND;
}

fin {
  /* Block terminator */
  return END_BLOCK;
}

return {
  /* Function end. */
  return RET_VAL;
}

next {
  /* Continue statement for loops */
  return NEXT;
}

leave {
  /* Break statement for loops */
  return LEAVE;
}

(true|false) {
  /* Boolean Type */
  yylval.str_val = strdup(yytext);
  return BOOL;
}

say {
  /* Printing with newline. */
  return PRINT;
}

write {
  /* Printing without newline. */
  return PRINTN;
}

inp_int {
  return INPUT_INT;
}

inp_float {
  return INPUT_FLOAT;
}

\"[^"\n]*["\n] {
  /* Quoted string. */
  yylval.str_val = strdup(yytext);
  return STRING;
}

[[:digit:]]*\.[[:digit:]]+ {
  /* Floats */
  yylval.float_val = atof(yytext);
  return FLOAT;
}

[[:digit:]]+ {
  /* Integers */
  yylval.int_val = atoi(yytext);
  return INTEGER;
}

[[:alnum:]_]+ {
  /* Variable ID */
  yylval.str_val = strdup(yytext);
  return ID;
}

[ \t]+ {
  /* Eat whitespace */
}

\n {
  /* Newline wrapper. */
  line_num++;
  return NL;
}

.|\n {
  /* Return any unmatched character as is */
  return (int)(*yytext);
}

%%
