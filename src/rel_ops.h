// This file defines behavior for relational operators (ie: ==, !=, <=, ...)

#include "types.h"

// Compares two values using the supplied assembly instruction suffix.
// ie: rel_cmp(int, int, "ne") would compare the top two values on the stack
// with the "jne" instruction, to test non-equality.
bbtype_t rel_cmp(bbtype_t, bbtype_t, const char *);
