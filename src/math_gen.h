// This file contains functions for x86_64 assembly code generation.
// By default, the functions write to stdout.

#include <stdio.h>
#include "types.h"

// Integer / Floating Point addition
bbtype_t add(bbtype_t, bbtype_t);

// Integer / Floating Point subtraction
bbtype_t sub(bbtype_t, bbtype_t);

// Integer / Floating Point multiplication
bbtype_t mul(bbtype_t, bbtype_t);

// Integer / Floating Point division
bbtype_t divi(bbtype_t, bbtype_t);

// Integer / Floating Point modulus
bbtype_t mod(bbtype_t, bbtype_t);

// Integer / Floating Point negation
bbtype_t neg(bbtype_t);

// Integer / Floating Point exponentiation
bbtype_t powr(bbtype_t, bbtype_t);
