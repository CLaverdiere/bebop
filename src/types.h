// This file contains type information used throughout the compiler.

#ifndef TYPES_H
#define TYPES_H

#include <deque>
#include <string>
#include <unordered_map>

// All type values are listed under the bbtype_t enum.
typedef enum {
  BBBOOL,
  BBFLOAT,
  BBINT,
  BBNONE,
  BBSTR,
  BB_TOTAL_PRIMS
} bbtype_t;

static std::string type_names[] =
{
 "bool",
 "float",
 "int",
 "none",
 "str"
};

// IDs can have several "kinds": (parameters, variables, etc.).
typedef enum {
  ARRAY,  // Array of variables
  FUN,    // Function name
  VAR,    // Normal variable
  MEMBER, // Member variable of user defined type
  STRUCT, // User defined type
  PARAM,  // Function Parameter
} kind_t;

// Quick accessor for the type string associated with a given bb_type.
static std::string kind_names[] =
{
  "array",
  "function",
  "global variable",
  "local variable",
  "member variable",
  "user defined type",
  "parameter",
};

// Symbol table data type, used as the symbol table's value.
//
// stack_offset is used for local variables. It stores the variable's offset from
// rbp in 8 byte intervals. So, a value of 2 would indicate a 16 byte offset.
//
// type_offset is used to track the memory offset for each member of a type.
//
// scope is the integer id for this symbol table entry.
//
// inner_scope is used for user types, where the name of the type has its own
// symbol table entry which points to an inner table entry containing member
// variable declarations.
//
// length is used for structures that are more than 8 bytes of contiguous data,
// like arrays, where we must know the number of elements.
//
// local designates whether the variable is local to a function, and hence will
// be stack allocated.
//
// TODO use a void pointer to extra data.
typedef struct sym_t {
  int stack_offset;
  int type_offset;
  int scope;
  int inner_scope;
  int length;
  int local;
  bbtype_t type;
  kind_t kind;
  std::deque<sym_t*> *args;
} sym_t;

// Call status data type, used for argument parsing.
typedef struct call_t {
  int args_parsed;
  std::string fn_name;
} call_t;

// The symbol table, indexed by string for ID lookup.
typedef std::unordered_map<std::string, sym_t*> symbol_table;

// Checks if two types are equal, and explodes the program if not.
void typechk(bbtype_t t1, bbtype_t t2);

// Helper to verify array index type.
void typechk_index(bbtype_t t1);

// Helper to check function types against definition.
void typechk_param(bbtype_t t1);

// Boilerplate called when defining a new type.
void type_init(char*);
void type_start(char*);
void type_end();

// Helper to find name of user type given bbtype_t value.
std::string type_name(bbtype_t t1);

#endif
