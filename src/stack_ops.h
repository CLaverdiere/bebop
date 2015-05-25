// This file defines operations for interacting with the stack.

#include "types.h"

// Push array element onto stack.
bbtype_t pusharr(char *, bbtype_t);

// Push boolean onto stack.
bbtype_t pushb(char *);

// Push float onto stack.
bbtype_t pushf(double);

// Push function call value onto the stack.
bbtype_t pushfn(char *);

// Push integer onto stack.
bbtype_t pushi(int);

// Push id semantic value onto stack.
bbtype_t pushid(char *);

// Push member from user type onto stack.
bbtype_t pushmember(char *, char *);

// Push string address onto stack.
bbtype_t pushs(char *);

// Stack frame setup and teardown code.
void stack_frame_new();
void stack_frame_end();
