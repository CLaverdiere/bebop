#include <iostream>

#include "types.h"
#include "util.h"
#include "symt_ops.h"

void typechk(bbtype_t t1, bbtype_t t2) {
  if (t1 != t2) {
    error("Type mismatch: %s and %s.",
          type_names[t1].c_str(), type_names[t2].c_str());
  }
}

void typechk_index(bbtype_t t1) {
  if (t1 != BBINT) {
    error("Arrays must be indexed by integer, not %s.",
        type_names[t1].c_str());
  }
}

void typechk_param(bbtype_t t1) {
  int arg_cnt = call_stack.top()->args_parsed;
  sym_t* fn_data = global_lookup(curr_fn_call);
  bbtype_t param_type = (*fn_data->args)[arg_cnt]->type;

  if (t1 != param_type) {
    error("Type mismatch: Parameter %d of %s should be of type %s, not %s.",
        arg_cnt+1, curr_fn_call.c_str(), type_names[param_type].c_str(),
        type_names[t1].c_str());
  }
}

void type_init(char* id) {
  std::string id_str(id);

  in_type = 1;
  curr_type_name = id_str;

  declare_type(id);
}

void type_start(char* id) {
  sym_t* st_entry = global_lookup(curr_type_name);
  st_entry->inner_scope = scope_hist.back();
  in_type_body = 1;
}

void type_end() {
  in_type = 0;
  in_type_body = 0;
}

std::string type_name(bbtype_t t1) {
  return user_type_strings[t1 - BB_TOTAL_PRIMS];
}
