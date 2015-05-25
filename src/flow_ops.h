// This file generates flow structures (if / while statements).

#include "types.h"

// The cond series of functions generates code for conditional statements (if
// statements). cond_start handles any boilerplate needed prior to conditional
// generation. cond_test generates branching code for the conditional on the
// top of the stack. cond_end adds the label boilerplate at the end of each
// conditional block.
//
// If the condition is true, continue as usual, otherwise jump to the end
// label. We need to separate these calls, as the conditional statement
// contains statements in-between, and the label jumped to on conditional
// failure must follow these statements. See the Bison grammar to see when each
// function is called.
void cond_start();
void cond_test(bbtype_t);
void cond_end();

// Loop tests (while loops) are similar to conditional statements above, but
// require that the program flow loop back to the first statement inside the
// loop block on the specified condition. loop_start places a start label
// before the comparison takes place, so if any variable changes inside the
// loop block, the comparison is reevaluated on each loop. loop_test jumps back
// to the start condition at the end of each block. If the condition fails,
// control jumps to the loop specified in loop_end.
//
// While the condition is true, repeat the loop block.
void loop_start();
void loop_test(bbtype_t);
void loop_end();

// Loops have statements for flow control to either leave the current loop, or
// immediately continue onto the next iteration of the loop.
void loop_leave();
void loop_next();
