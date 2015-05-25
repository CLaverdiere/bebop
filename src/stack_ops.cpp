#include <iomanip>
#include <iostream>
#include <string.h>

#include "asm_ops.h"
#include "rt_checks.h"
#include "stack_ops.h"
#include "symt_ops.h"
#include "types.h"
#include "util.h"

bbtype_t pusharr(char* id, bbtype_t index_type) {
  std::string id_str(id);

  typechk_index(index_type);

  sym_t* st_entry = lookup_valid(id_str);
  bbtype_t id_type = st_entry->type;

  inst("pop rbx");
  array_bounds_check(st_entry);

  if (st_entry->local) {
    int offset = st_entry->stack_offset * 8 + 8;
    inst("neg rbx");
    inst("push QWORD [r12 + rbx * 8 - %d]", offset);

  } else {
    inst("push QWORD [%s_%d + rbx * 8]", id, st_entry->scope);
  }

  return id_type;
}

bbtype_t pushb(char* b_str) {
  int b_val = strcmp(b_str, "true") == 0 ? 1 : 0;
  inst("push QWORD %d", b_val);
  return BBBOOL;
}

bbtype_t pushi(int a) {
  inst("push QWORD %d", a);
  return BBINT;
}

bbtype_t pushf(double a) {
  label(S_DATA, "f%d: dq %lf", total_floats, a);
  inst("push QWORD [f%d]", total_floats);
  total_floats++;
  return BBFLOAT;
}

bbtype_t pushfn(char* fn_id) {
  std::string id_str(fn_id);

  sym_t* st_entry = lookup_valid(id_str);
  inst("push rax");

  return st_entry->type;
}

bbtype_t pushid(char* id) {
  std::string id_str(id);

  // ID must be previously declared for defined behavior.
  sym_t* st_entry = lookup_valid(id_str);

  int id_scope = st_entry->scope;
  bbtype_t type = st_entry->type;

  if (st_entry->local) {
    // We lookup the offset of the local variable needed, and add an 8 offset
    // to move past the saved ebp register for the stack frame.
    int offset = st_entry->stack_offset * 8 + 8;
    inst("push QWORD [r12 - %d]", offset);

  } else {
    inst("push QWORD [%s_%d]", id, id_scope);
  }

  return type;
}

bbtype_t pushmember(char* id, char* member) {
  std::string id_str(id);
  std::string member_str(member);

  sym_t* record = lookup_valid(id_str);
  sym_t* member_record = lookup_member(id_str, member_str);

  if (record->local) {
    int stack_offset = record->stack_offset;
    inst("push QWORD [r12 - %d]",
        (member_record->type_offset + stack_offset) * 8 + 8);

  } else {
    inst("push QWORD [%s_%d + %d]", id, record->scope,
        member_record->type_offset * 8);
  }

  return member_record->type;
}

bbtype_t pushs(char* str) {
  // Null terminate the string for use with printf.
  label(S_DATA, "s%d: db %s, 0", total_strings, str);
  inst("push s%d", total_strings);

  total_strings++;
  return BBSTR;
}

void stack_frame_new() {
  inst("push rbp");
  inst("mov rbp, rsp");
}

void stack_frame_end() {
  inst("mov rsp, rbp");
  inst("pop rbp");
}
