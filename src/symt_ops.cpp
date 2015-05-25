#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

#include "asm_ops.h"
#include "fun_gen.h"
#include "rt_checks.h"
#include "symt_ops.h"
#include "util.h"

// TODO [Refactor]: There is code duplication with "push" and "pop" instructions. A
// much cleaner approach would be to create an addressing function for each
// type, and create push and pop wrapper functions around those.
//
// Add local cases to each as well.

void add_symt_entry(std::string key, sym_t* val, int scope) {
  symbol_table* scoped_tbl = sym_tbls[scope];
  (*scoped_tbl)[key] = val;
}

void assign(char* id, bbtype_t type) {
  std::string id_str(id);

  sym_t* st_entry = lookup_valid(id_str);

  int id_scope = st_entry->scope;
  bbtype_t id_type = st_entry->type;
  typechk(id_type, type);

  if(st_entry->local) {
    int offset = st_entry->stack_offset * 8 + 8;
    inst("pop QWORD [r12 - %d]", offset);
  } else {
    inst("pop QWORD [%s_%d]", id, id_scope);
  }
}

void assign_arr(char* id, bbtype_t type, bbtype_t index_type) {
  std::string id_str(id);

  typechk_index(index_type);

  sym_t* st_entry = lookup_valid(id_str);

  bbtype_t id_type = st_entry->type;
  typechk(id_type, type);

  inst("mov rbx, [rsp + 8]");
  array_bounds_check(st_entry);

  if (st_entry->local) {
    int offset = st_entry->stack_offset * 8 + 8;
    inst("neg rbx");
    inst("pop QWORD [r12 + rbx * 8 - %d]", offset);

  } else {
    inst("pop QWORD [%s_%d + rbx * 8]", id, st_entry->scope);
  }

  inst("add rsp, 8");
}

void assign_type(char* id, char* member, bbtype_t type) {
  std::string id_str(id);
  std::string member_str(member);

  sym_t* record = lookup_valid(id);
  sym_t* member_record = lookup_member(id_str, member_str);
  typechk(type, member_record->type);

  if (record->local) {
    int stack_offset = record->stack_offset;
    inst("pop QWORD [r12 - %d]",
        (member_record->type_offset + stack_offset) * 8 + 8);

  } else {
    inst("pop QWORD [%s_%d + %d]", id, record->scope,
        member_record->type_offset * 8);
  }
}

void declare(bbtype_t type, kind_t kind, char* id, int length) {
  int curr_scope = scope_hist.back();
  std::string id_str(id);

  sym_t* st_entry = lookup(id_str);

  if (st_entry) {
    if (st_entry->scope == curr_scope) {
      if(st_entry->type != type) {
        error("Conflicting types for variable %s.", id);
      } else {
        error("Redeclaration of %s with same type.", id);
      }
    }
  }

  st_entry = (sym_t*) malloc(sizeof(sym_t));
  st_entry->type = type;
  st_entry->scope = curr_scope;
  st_entry->inner_scope = 0;
  st_entry->kind = kind;
  st_entry->length = length;
  st_entry->local = in_function;
  st_entry->stack_offset = 0;
  st_entry->type_offset = 0;
  st_entry->args = new std::deque<sym_t*>();

  if (in_type_body) {
    st_entry->type_offset = global_lookup(curr_type_name)->type_offset++;
  }

  switch(kind) {

    case FUN:
    case MEMBER:
      break;

    // Array / Struct declaration.
    case STRUCT:
      if (in_type) {
        break;
      }

      st_entry->inner_scope =
        global_lookup(type_name(st_entry->type))->inner_scope;

      // The lack of 'break' is intentional. This is meant to fall through into
      // ARRAY.

    case ARRAY:
      st_entry->length = length;
      if (st_entry->local) {
        inst("sub rsp, %d", st_entry->length * 8);
        st_entry->stack_offset = global_lookup(curr_fn_name)->stack_offset;
        global_lookup(curr_fn_name)->stack_offset += st_entry->length;

      } else {
        label(S_DATA, "%s_%d: times %d db 0", id, curr_scope, st_entry->length * 8);
      }

      break;

    case VAR:
    case PARAM:
    default:
      // variable allocation using the stack.
      if (st_entry->local) {
        st_entry->stack_offset = global_lookup(curr_fn_name)->stack_offset++;

        if (in_function_body) {
          inst("push QWORD 0");
        }

        break;
      } else {
        // Global variable allocation using labels.
        switch(type) {
          case BBFLOAT:
            label(S_DATA, "%s_%d: dq 0.0", id, curr_scope);
            break;
          case BBINT:
          case BBSTR:
          case BBBOOL:
            label(S_DATA, "%s_%d: dq 0", id, curr_scope);
            break;
          default:
            yyerror("Invalid type in declaration.");
        }
      }
  }

  add_symt_entry(id_str, st_entry, curr_scope);
}

void declare_var(bbtype_t type, char* id) {
  if (in_type) {
    declare(type, MEMBER, id, 1);
  } else {
    declare(type, VAR, id, 1);
  }
}

void declare_arr(bbtype_t type, char* id, int size) {
  declare(type, ARRAY, id, size);
}

void declare_type(char* type) {
  std::string type_str = type;
  bbtype_t new_type_val = (bbtype_t) total_user_types++;

  user_types[type_str] = new_type_val;
  user_type_strings.push_back(type_str);

  declare(new_type_val, STRUCT, type, 0);
}

void declare_type_instance(char* type, char* id) {
  std::string type_str = type;
  auto type_val = user_types.find(type_str);

  if (type_val == user_types.end()) {
    error("No such type %s exists.", type);
  }

  sym_t* type_data = global_lookup(type_str);
  int size = sym_tbls[type_data->inner_scope]->size();

  declare(type_val->second, STRUCT, id, size);
}

sym_t* lookup(std::string id_val) {
  int scope_offset = scope_hist.size() - 1;
  int parent_scope;
  symbol_table* table_cand;

  while (scope_offset >= 0) {
    table_cand = sym_tbls[scope_hist[scope_offset]];
    auto lookup = table_cand->find(id_val);

    if (lookup == table_cand->end()) {
      if (scope_offset == 0) { break; }

      parent_scope = scope_hist[--scope_offset];
      table_cand = sym_tbls[parent_scope];

    } else {
      return lookup->second;
    }
  }

  return NULL;
}

sym_t* lookup_member(std::string id, std::string member) {
  sym_t* record = lookup_valid(id);
  symbol_table* inner_record = sym_tbls[record->inner_scope];

  auto member_record_it = inner_record->find(member);
  if (member_record_it == inner_record->end()) {
    error("No member %s exists for type %s.", member.c_str(), id.c_str());
  }

  return member_record_it->second;
}

sym_t* lookup_valid(std::string id_str) {
  sym_t* st_entry = lookup(id_str);
  if(!st_entry) {
    error("%s is not declared.", id_str.c_str());
  }
  return st_entry;
}

void new_scope() {
  scope_hist.push_back(total_scopes++);
  symbol_table* sym_tbl = new symbol_table;
  sym_tbls.push_back(sym_tbl);
}

void end_scope() {
  scope_hist.pop_back();
}

sym_t* global_lookup(std::string fn_name) {
  return (*sym_tbls[0])[fn_name];
}
