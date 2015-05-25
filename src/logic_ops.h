// This file defines all logical operations for the boolean type.

#include "types.h"

// Logical NOT. Inverts the boolean.
bbtype_t logic_not(bbtype_t a);

// Logical AND. True only if both true.
bbtype_t logic_and(bbtype_t a, bbtype_t b);

// Logical OR. True if either (or both) are true.
bbtype_t logic_or(bbtype_t a, bbtype_t b);
