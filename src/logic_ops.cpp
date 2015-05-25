#include "asm_ops.h"
#include "logic_ops.h"
#include "util.h"

// Logical not takes only a single operand, so we can do the math directly on
// the stack.
// First, negate the 64 byte quadword. This takes the stack value from
// something like 0x00000001 to 0x11111110. Then we just mask out the first 63
// bits using and to get the final boolean value for logical not.
bbtype_t logic_not(bbtype_t a) {
  inst("not QWORD [rsp]");
  inst("and QWORD [rsp], 0x00000001");

  return BBBOOL;
}

// We can assume that the value on the stack will be 63 zero bytes followed by
// either a 0 or 1 byte. Thus, the bitwise and instruction handles logical and
// as well.
bbtype_t logic_and(bbtype_t a, bbtype_t b) {
  typechk(a, b);

  inst("pop rbx");
  inst("pop rax");
  inst("and rax, rbx");
  inst("push rax");

  return BBBOOL;
}

// Same process as logic_and, but with or.
bbtype_t logic_or(bbtype_t a, bbtype_t b) {
  typechk(a, b);

  inst("pop rbx");
  inst("pop rax");
  inst("or rax, rbx");
  inst("push rax");

  return BBBOOL;
}
