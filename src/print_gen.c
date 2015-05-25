#include "asm_ops.h"
#include "print_gen.h"
#include "stack_ops.h"
#include "util.h"

void print_call(bbtype_t type, int newline) {
  switch(type) {
    case BBFLOAT:
      if (newline) inst("mov rdi, fmt_float_nl");
      else inst("mov rdi, fmt_float");
      inst("movq xmm0, [rsp]");
      inst("mov al, 1");
      inst("add rsp, 8");
      break;

    case BBINT:
    case BBBOOL:
      if (newline) inst("mov rdi, fmt_decimal_nl");
      else inst("mov rdi, fmt_decimal");
      inst("pop rsi");
      inst("mov al, 0");
      break;

    case BBSTR:
      if (newline) inst("mov rdi, fmt_string_nl");
      else inst("mov rdi, fmt_string");
      inst("pop rsi");
      inst("mov al, 0");
      break;

    default:
      error("Attempted to print invalid type of value %d.", type);
      exit(EXIT_FAILURE);
  }

  // The stack needs to have 16-byte allignment to call printf.
  // This was the source of much frustration.
  // So, stack frame it, then align it. Restore afterwards.
  stack_frame_new();
  inst("and rsp, 0xfffffffffffffff0");
  inst("call printf");
  stack_frame_end();
}
