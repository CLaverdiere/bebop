#include "asm_ops.h"
#include "input_ops.h"

// We use scanf for input. scanf can write directly to the stack, but we must
// reserve a spot to avoid overwriting whatever's there.
bbtype_t inp_int() {
  inst("mov rdi, fmt_decimal");
  inp_call();

  return BBINT;
}

bbtype_t inp_float() {
  inst("mov rdi, fmt_float");
  inp_call();

  return BBFLOAT;
}

void inp_call() {
  inst("sub rsp, 8");
  inst("mov rsi, rsp");
  inst("mov al, 0");
  inst("call scanf");
}
