// This file contains Bison code, and defines the grammar for the language.

// NOTES:
// There are a few reduce/reduce errors occuring due to repeated ID and paren
// tokens. These actions evaluate the same rule, so the conflict is a
// non-issue.

%{

#include <iostream>
#include <cmath>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "asm_ops.h"
#include "flow_ops.h"
#include "fun_gen.h"
#include "input_ops.h"
#include "logic_ops.h"
#include "math_gen.h"
#include "print_gen.h"
#include "rel_ops.h"
#include "stack_ops.h"
#include "symt_ops.h"
#include "util.h"

// Enable better error messages.
#define YYERROR_VERBOSE 1
#define YYDEBUG 1

// Parser error reporting routine.
void yyerror(const char *msg);

// Scanner routine defined by Flex.
int yylex();

// Global symbol table structure.
std::vector<symbol_table*> sym_tbls;

// Conditional label stacks.
std::stack<int> cond_stack;
std::stack<int> cond_loop_stack;

// Scope history.
std::vector<int> scope_hist;

// Function call stack.
std::stack<call_t*> call_stack;

// User type maps.
std::unordered_map<std::string, bbtype_t> user_types;
std::vector<std::string> user_type_strings;

// Aggregate type counts.
int total_bounds_checks = 0;
int total_conds = 0;
int total_floats = 0;
int total_functions = 0;
int total_scopes = 0;
int total_strings = 0;
int total_user_types = BB_TOTAL_PRIMS;

// Function / typestatus.
int in_type = 0;
int in_type_body = 0;
int in_function = 0;
int in_function_body = 0;
section_t active_section = S_TEXT;
std::string curr_type_name;
std::string curr_fn_name;
std::string curr_fn_call;

// Keep the current line_number for error reporting purposes.
int line_num = 1;

// Global string streams for sectioning off the assembly file.
std::stringstream data_out;
std::stringstream proc_out;
std::stringstream text_out;

%}

// We need to include the type definitions here so that the yylval union can
// use them.
%code requires {
  #include "types.h"
}

/* yylval union type. */
%union {
  double float_val;
  long int_val;
  char* str_val;
  bbtype_t type_val;
}

/* Miscellaneous token types. */
%token <float_val> FLOAT
%token <int_val> INTEGER
%token <str_val> BOOL
%token <str_val> ID
%token <str_val> INPUT_FLOAT
%token <str_val> INPUT_INT
%token <str_val> STRING
%token <str_val> UTYPE
%token <type_val> TYPE

/* Operators */
%left '+' '-'
%left '*' '/' '%'
%left L_OR
%left L_AND
%left L_NOT
%right UMINUS
%right POW
%nonassoc PRINT PRINTN
%nonassoc EQ NEQ GT GEQ LT LEQ
%nonassoc COND LOOP_COND
%nonassoc END_BLOCK
%nonassoc NEXT LEAVE
%nonassoc RET_VAL
%nonassoc NL

/* Nonterminal types. */
%type <type_val> expr nm_expr nm_prim nm_logic m_expr m_prim m_inp rel_expr
%type <str_val> fn_call

%%

// The entire program is parsed before any assembly is written. The start
// action writes data collected by all global stringstreams at the end of the
// program.
start:
  { new_scope(); } stmt_seq { write_asm(); }
;

// The entire program is a sequence of statements, each separated by an
// arbitrary amount of newlines.
stmt_seq:
  /* EMPTY */
  | stmt_seq stmt
;

// A statement can be either an empty line (for whitespace formatting), or some
// other structure. See each rule section below.
stmt:
  NL
  | assign
  | declare
  | flow
  | fn_call
  | print
  | return
;

// Assignment statement.
assign:
    assign_arr
  | assign_type_data
  | assign_var
;

// Assignment of variable ID to expression value.
assign_var:
  ID '=' expr { assign($1, $3); }
;

// Assignment of array variable to expression value.
assign_arr:
  ID '[' expr ']' '=' expr { assign_arr($1, $6, $3); }
;

// Assign data to field of a user type.
assign_type_data:
  ID '.' ID '=' expr { assign_type($1, $3, $5); }
;

// General declaration.
declare:
    declare_arr
  | declare_fn
  | declare_type
  | declare_type_instance
  | declare_var
;

// Type declaration for array.
declare_arr:
  TYPE ID '[' INTEGER ']' { declare_arr($1, $2, $4); }
;

// Type declaration for user defined types.
declare_type:
  UTYPE ID { type_init($2); } NL { new_scope(); type_start($2); }
    decl_seq
  END_BLOCK { type_end(); end_scope(); }
;

// Instance of type declaration for user defined types.
declare_type_instance:
  ID ID { declare_type_instance($1, $2); }
;

// Type declaration of variable ID to type TYPE.
declare_var:
  TYPE ID { declare_var($1, $2); }
;

// Sequence of declarations.
decl_seq:
  /* EMPTY */
  | decl_seq declare_var NL
;

// Flow control construct.
flow:
    cond
  | loop_cond
  | LEAVE { loop_leave(); }
  | NEXT  { loop_next(); }
;

// Conditional expression (if statement).
cond:
  COND { cond_start(); } nm_logic { cond_test($3); } NL { new_scope(); }
    stmt_seq NL
  END_BLOCK { cond_end(); end_scope(); }
;

// Looping conditional expression (while statement).
// TODO code duplication.
loop_cond:
  LOOP_COND { loop_start(); } nm_logic { loop_test($3); } NL { new_scope(); }
    stmt_seq NL
  END_BLOCK { loop_end(); end_scope(); }
;

// Function declaration.
declare_fn:
  TYPE ID '(' { fun_init($2, $1); new_scope(); } decl_list ')' NL { fun_start($2); }
    stmt_seq NL
  END_BLOCK { fun_end(); end_scope(); }
;

// Function call.
fn_call:
  ID '(' { fun_call_init($1); } arg_list ')' { fun_call($1); } { $$ = $1; }
;

// List of function arguments for declaration, types specified, separated by
// commas.
decl_list:
  /* EMPTY */
  | decl_list_tail
;

// Production that allows an decl_list to be empty without leaving trailing
// commas.
decl_list_tail:
    TYPE ID { declare_var($1, $2); fun_new_param($2); }
  | TYPE ID { declare_var($1, $2); fun_new_param($2); } ',' decl_list_tail
;

// List of function arguments for call, separated by commas.
arg_list:
  /* EMPTY */
  | arg_list_tail
;

// Analagous to decl_list_tail.
arg_list_tail:
    expr { fun_call_new_arg($1); }
  | expr { fun_call_new_arg($1); } ',' arg_list_tail
;

// Expressions can be printed either with, or without a newline appended.
// The PRINTN variant excludes the newline.
print:
    PRINT expr   { print_call($2, 1); } // Print with newline.
  | PRINTN expr  { print_call($2, 0); } // Print without newline.
;

// All inclusive expression.
expr:
    m_expr
  | nm_expr
;

// Non-math primitive.
nm_prim:
  STRING { $$ = pushs($1); }
;

// Relational expression.
rel_expr:
    m_expr EQ  m_expr { $$ = rel_cmp($1, $3, "e"); }
  | m_expr NEQ m_expr { $$ = rel_cmp($1, $3, "ne"); }
  | m_expr LT  m_expr { $$ = rel_cmp($1, $3, "l"); }
  | m_expr LEQ m_expr { $$ = rel_cmp($1, $3, "le"); }
  | m_expr GT  m_expr { $$ = rel_cmp($1, $3, "g"); }
  | m_expr GEQ m_expr { $$ = rel_cmp($1, $3, "ge"); }
;

// Logic expression.
nm_logic:
    ID                      { $$ = pushid($1); }
  | fn_call                 { $$ = pushfn($1); }
  | BOOL                    { $$ = pushb($1); }
  | rel_expr
  | L_NOT nm_logic          { $$ = logic_not($2); }
  | nm_logic L_AND nm_logic { $$ = logic_and($1, $3); }
  | nm_logic L_OR  nm_logic { $$ = logic_or($1, $3); }
  | '(' nm_logic ')'        { $$ = $2; }
;

// Non-math expression.
nm_expr:
    nm_prim
  | nm_logic
;

// Math input.
m_inp:
    INPUT_INT         { $$ = inp_int(); }
  | INPUT_FLOAT       { $$ = inp_float(); }
;

// Math primitive.
m_prim:
    INTEGER           { $$ = pushi($1); }
  | FLOAT             { $$ = pushf($1); }
;

// Math expression.
m_expr:
    ID                 { $$ = pushid($1); }
  | ID '[' expr ']'    { $$ = pusharr($1, $3); }
  | ID '.' ID          { $$ = pushmember($1, $3); }
  | m_prim
  | m_inp
  | fn_call            { $$ = pushfn($1); }
  | m_expr '+' m_expr  { $$ = add($1, $3); }
  | m_expr '-' m_expr  { $$ = sub($1, $3); }
  | m_expr '*' m_expr  { $$ = mul($1, $3); }
  | m_expr '/' m_expr  { $$ = divi($1, $3); }
  | m_expr '%' m_expr  { $$ = mod($1, $3); }
  | '-' m_expr         { $$ = neg($2); }
  | m_expr POW m_expr  { $$ = powr($1, $3); }
  | '(' m_expr ')'     { $$ = $2; }
;

// Return statement.
// Void functions can leave off any expression value, so we allow a variant
// with and without a trailing expression.
return:
    RET_VAL      { fun_ret(BBNONE); }
  | RET_VAL expr { fun_ret($2); }
;

%%

// Error function called whenever the parser explodes.
void yyerror(const char *msg)
{
  fprintf(stderr, "Parser error (line %d): %s\n", line_num, msg);
  exit(EXIT_FAILURE);
}

// All Bison executes is yyparse.
int main()
{
  return yyparse();
}
