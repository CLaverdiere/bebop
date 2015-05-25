// This file contains utility functions, mostly for IO.

#include <stack>
#include <string>
#include <vector>

#include "asm_ops.h"
#include "types.h"

// TODO consider moving all the externs into better places.

#define INDENT_WIDTH 2
#define FLOAT_PREC 6
#define ARG_WIDTH 8

// Boilerplate to include at beginning / end of each assembly file.
extern const char* SBP_FILENAME;
extern const char* EBP_FILENAME;

// Other boilerpate paths.
extern const char* EXTERNS_FILENAME;
extern const char* STRINGS_FILENAME;
extern const char* PROC_FILENAME;

// Current line number state. Storing here for now.
extern int line_num;

// Total floats increments for each float constant encountered, NOT the amount
// of declared float variables. Each label given to a float constant is simply
// "fN", where N is total_floats. Strings behave analogously.
extern int total_bounds_checks;
extern int total_conds;
extern int total_floats;
extern int total_functions;
extern int total_scopes;
extern int total_strings;
extern int total_user_types;

// Function state:
// Somewhat dirty method to determine if the compiler is currently parsing a
// function. We need to know this because variable declaration is local for
// functions, but global outside of them.
extern int in_type;
extern int in_type_body;
extern int in_function;
extern int in_function_body;
extern section_t active_section;

// The name of the function / type declaration currently being parsed.
extern std::string curr_type_name;
extern std::string curr_fn_name;

// The name of the function call currently being parsed.
extern std::string curr_fn_call;

// For conditional code generation, a conditional statement can be nested
// arbitrarily many times. Thus when generating labels, we use a stack to
// track each level of nesting.
extern std::stack<int> cond_stack;
extern std::stack<int> cond_loop_stack;

// The call stack is a stack of function names, with the most recently called
// function name at the top. This allows us to use function calls as arguments
// to other functions.
extern std::stack<call_t*> call_stack;

// Each scope can have its own set of local variables. It's legal for a local
// variable in one scope to have the same name as the scope above it. It's also
// legal to reference a local variable from a parent scope that doesn't exist
// in the current scope. This is much like a tree structure, where if we want
// to check if a variable is in scope, we traverse up the scope tree until
// hitting root (global scope).
//
// We need fast access to the current active scope, and the parent scope. Any
// data structure supporting constant time stack operations is sufficient, but
// we must be able to look at the 2nd to last element easily. As vectors have
// contiguous memory, and have amortized constant insertion, they're sufficient
// for this case. A list could also be used.
extern std::vector<int> scope_hist;

// User types must be assigned a unique integer ID for type checking purposes.
// When a new type is declared, a new entry gets added to this map. When an
// instance of that type is declared, it checks this map for its type code.
// A vector of strings is also provided to map in the opposite direction.
extern std::unordered_map<std::string, bbtype_t> user_types;
extern std::vector<std::string> user_type_strings;

// Return a random insult.
std::string insult();

// Write a file to stdout.
void print_file(const char*);

// Simple error reporting function used by Bison.
extern void yyerror(const char*);

// Various other error reporting functions.
void error(const char* fmt, ...);
void warning(const char* fmt, ...);
