#include "asm_ops.h"
#include "flow_ops.h"
#include "util.h"

void cond_start() {
  cond_stack.push(total_conds++);
}

void cond_test(bbtype_t b) {
  typechk(b, BBBOOL);

  inst("pop rax");
  inst("cmp QWORD rax, 0");
  inst("je near .ec%d", cond_stack.top());
}

void cond_end() {
  label(active_section, ".ec%d:", cond_stack.top());
  cond_stack.pop();
}

void loop_start() {
  cond_loop_stack.push(total_conds++);
  label(active_section, ".sc%d:", cond_loop_stack.top());
}

void loop_test(bbtype_t b) {
  typechk(b, BBBOOL);

  inst("pop rax");
  inst("cmp QWORD rax, 0");
  inst("je near .ec%d", cond_loop_stack.top());
}

void loop_end() {
  inst("jmp near .sc%d", cond_loop_stack.top());
  label(active_section, ".ec%d:", cond_loop_stack.top());
  cond_loop_stack.pop();
}

void loop_leave() {
  if (cond_loop_stack.size() == 0) {
    error("leave called outside of any while loop.");
  }
  inst("jmp .ec%d", cond_loop_stack.top());
}

void loop_next() {
  if (cond_loop_stack.size() == 0) {
    error("next called outside of any while loop.");
  }
  inst("jmp .sc%d", cond_loop_stack.top());
}
