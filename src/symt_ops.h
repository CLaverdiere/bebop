// This file contains symbol table related functions.

#include <vector>

#include "types.h"

// We have a single symbol table for each scope, and several files that
// modify it.
extern std::vector<symbol_table*> sym_tbls;

// Creates a new symbol table entry.
void add_symt_entry(std::string, sym_t*, bbtype_t);

// Generates code to assign a value to the given ID.
void assign(char*, bbtype_t);

// Generates code to assign a value to an array variable.
void assign_arr(char*, bbtype_t, bbtype_t);

// Generates code to assign a value to a user defined type.
void assign_type(char* id, char* member, bbtype_t type);

// Creates a symbol table entry for the given ID and type.
// Can be a function or variable declaration.
// Fails if the variable was previously declared.
void declare(bbtype_t, kind_t, char*, int);

// Wrappers for various kinds of declarations.
void declare_arr(bbtype_t, char*, int);
void declare_type(char*);
void declare_type_instance(char*, char*);
void declare_var(bbtype_t, char*);

// Utility function to quickly access a symbol table entry by ID. Searches
// each symbol table in the scope stack for the id. If it reaches global scope
// and no id is found, there is no entry.  If no entry is found, return a null
// pointer. Basically a nice wrapper around std::find.
sym_t* lookup(std::string);

// Wrapper for quick type member access.
sym_t* lookup_member(std::string, std::string);

// Wrapper for symbol table entry lookup with error checking.
sym_t* lookup_valid(std::string);

// Boilerplate to occur on each new scope level.
void new_scope();

// Boilerplate to occur on end of each scope level.
void end_scope();

// Helper accessor for global symbol table data.
sym_t* global_lookup(std::string);
