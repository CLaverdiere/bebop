#include <math.h>

#include "asm_ops.h"
#include "math_gen.h"
#include "symt_ops.h"
#include "types.h"
#include "util.h"

// Mathematical Functions
//
// The compiler handles mathematical integer operations by popping the last
// computed value from the stack into rax, performing the operation, and
// pushing the value back onto the stack. Sometimes this requires storing
// intermediate results, like in division and multiplication, while other times
// we can perform instructions directly on the stack pointer, like in addition
// and subtraction.
//
// Floating point operations are handled with the x87 FPU stack, and most are
// handled with built in float instructions that automatically pop the result
// into st0, the first register. For functions like power and modulus, C
// external functions are used to reduce complexity of code.
//
// The Bison parser passes the type into each function, and typechecks all
// binary operations to make sure there are no conflicting types. For example,
// floats may not be added with ints. With this type information, we can
// include a simple case statement in each function, rather than manually
// overloading each function for each type. Some would call this bad
// programming practice. I like it though.
//
// The return value for each math function is the resulting type of the
// expression, and is returned to the compiler for future type checking.

// Pop from the top of the stack and add directly to the stack pointer value.
bbtype_t add(bbtype_t a, bbtype_t b) {
  typechk(a, b);

  switch(a) {
    case BBFLOAT:
      inst("fld QWORD [rsp+8]");
      inst("fld QWORD [rsp]");
      inst("faddp");
      inst("add rsp, 8");
      inst("fstp QWORD [rsp]");
      break;
    case BBINT:
      inst("pop rax");
      inst("add [rsp], rax");
      break;
    default:
      error("Operation (+) not defined for types %s and %s.",
          type_names[a].c_str(), type_names[b].c_str());
  }

  return a;
}

// Same pattern as addition but with subtraction.
bbtype_t sub(bbtype_t a, bbtype_t b) {
  typechk(a, b);

  switch(a) {
    case BBFLOAT:
      inst("fld QWORD [rsp+8]");
      inst("fld QWORD [rsp]");
      inst("fsubp");
      inst("add rsp, 8");
      inst("fstp QWORD [rsp]");
      break;
    case BBINT:
      inst("pop rax");
      inst("sub [rsp], rax");
      break;
    default:
      error("Operation (-) not defined for types %s and %s.",
          type_names[a].c_str(), type_names[b].c_str());
  }

  return a;
}

// We can only use the imul instruction on a register, so we deviate slightly
//   from the add/sub pattern, storing the intermediate result of
//   multiplication.
bbtype_t mul(bbtype_t a, bbtype_t b) {
  typechk(a, b);

  switch(a) {
    case BBFLOAT:
      inst("fld QWORD [rsp+8]");
      inst("fld QWORD [rsp]");
      inst("fmulp");
      inst("add rsp, 8");
      inst("fstp QWORD [rsp]");
      break;
    case BBINT:
      inst("pop rax");
      inst("imul rax, [rsp]");
      inst("mov [rsp], rax");
      break;
    default:
      error("Operation (*) not defined for types %s and %s.",
          type_names[a].c_str(), type_names[b].c_str());
  }

  return a;
}

// With division, the idiv instruction stores the remainder in rdx, and the
// quotient in rax. Here, we only care about rax.
bbtype_t divi(bbtype_t a, bbtype_t b) {
  typechk(a, b);

  switch(a) {
    case BBFLOAT:
      inst("fld QWORD [rsp+8]");
      inst("fld QWORD [rsp]");
      inst("fdivp");
      inst("add rsp, 8");
      inst("fstp QWORD [rsp]");
      break;
    case BBINT:
      inst("pop rcx");
      inst("pop rax");
      inst("cqo");
      inst("idiv QWORD rcx");
      inst("push QWORD rax");
      break;
    default:
      error("Operation (/) not defined for types %s and %s.",
          type_names[a].c_str(), type_names[b].c_str());
  }

  return a;
}

// Same as division, except we care about rdx, the modulus.
bbtype_t mod(bbtype_t a, bbtype_t b) {
  typechk(a, b);

  switch(a) {
    case BBFLOAT:
      // Here we just extern for fmod, since there's no real x87 instruction
      // for it.
      inst("movq xmm1, [rsp]");
      inst("movq xmm0, [rsp+8]");
      inst("mov al, 2");
      inst("call fmod");
      inst("add rsp, 8");
      inst("movq [rsp], xmm0");
      break;
    case BBINT:
      inst("pop rcx");
      inst("pop rax");
      inst("cqo");
      inst("idiv QWORD rcx");
      inst("push QWORD rdx");
      break;
    default:
      error("Operation (%) not defined for types %s and %s.",
          type_names[a].c_str(), type_names[b].c_str());
  }

  return a;
}

// Negation can just be applied directly to the stack pointer.
bbtype_t neg(bbtype_t a) {
  switch(a) {
    case BBFLOAT:
      inst("fld QWORD [rsp]");
      inst("fchs");
      inst("fstp QWORD [rsp]");
      break;
    case BBINT:
      inst("neg QWORD [rsp]");
      break;
    default:
      error("Negation operation not defined for type %s. %s",
          type_names[a].c_str());
  }

  return a;
}

// Power function, with base a and exponent b.
// The intpow function itself is a handwritten x64 procedure.
// The base is stored in rsi, and the exponent in rdi.
// The result is stored in rax.
bbtype_t powr(bbtype_t a, bbtype_t b) {
  typechk(a, b);

  switch(a) {
    case BBFLOAT:
      // Here we just extern for fpow, since there's no real x87 instruction
      // for it.
      inst("movq xmm1, [rsp]");
      inst("movq xmm0, [rsp+8]");
      inst("mov al, 2");
      inst("call pow");
      inst("add rsp, 8");
      inst("movq [rsp], xmm0");
      break;
    case BBINT:
      inst("pop rdi");
      inst("pop rsi");
      inst("call intpow");
      inst("push QWORD rax");
      break;
    default:
      error("Operation (**) not defined for types %s and %s.",
          type_names[a].c_str(), type_names[b].c_str());
  }

  return a;
}
