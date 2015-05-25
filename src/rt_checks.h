// The file handles code generation for runtime checks.

#include "types.h"

// Array bounds checking.
// If the user supplies a value outside of the interval [0, n-1] for an array
// of size n, an error message is printed and the program exits.
void array_bounds_check(sym_t* st_entry);
