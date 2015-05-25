// This file defines behavior for function code generation.
//
// On a function call, the stack layout is as follows:
//
// -------------
// | BOTTOM    |
// -------------
// | saved ebp |
// | arg1      |
// | ...       |
// | argN      |
// | retval    |
// | localvar1 |
// | ...       |
// | localvarN |
// -------------
// | TOP       |
// -------------
//
// Local variables are assigned a memory offset on the stack at declaration
// time, in the order they are parsed. When referencing a local variable, we
// use the arithmetic:
//
// ebp + 8 * memory_offset + 8
//
// This gives us our correct memory address on the stack.

// Naming convention:
// If the name contains call, the function applies to function calls.
// Otherwise, the function declaration.

#include "types.h"

// Generates code to call function.
void fun_call_init(char*);
void fun_call(char*);

// Handles argument type checking.
void fun_call_new_arg(bbtype_t);

// Creates symbol table entries, and misc initialization.
void fun_init(char*, bbtype_t);

// Action to take when parsing each parameter.
void fun_new_param(char*);

// Generates return jump code.
// Return value stored in rax.
void fun_ret(bbtype_t);

// Generates code for start of function declaration.
void fun_start(char*);

// Cleans up function declaration.
void fun_end();
