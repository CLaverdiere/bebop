// This file contains functions that generate assembly IO.

#include "types.h"

// Write the sequence of instructions needed to call printf on any type.
// If newline nonzero, then a newline is printed.
void print_call(bbtype_t type, int newline);
