#include "fun_gen.h"
#include "stack_ops.h"
#include "symt_ops.h"
#include "types.h"
#include "util.h"

void fun_call_init(char* fn_name) {
  std::string fn_str = fn_name;
  sym_t* st_entry = lookup(fn_str);

  curr_fn_call = fn_str;

  if(!st_entry) {
    error("%s is not a declared function.", fn_name);
  } else if (st_entry->kind != FUN) {
    error("%s is a %s, not a function.", fn_name,
        kind_names[st_entry->kind].c_str());
  }

  // Local variables need to reference rbp before the call, so we can't just
  // write over rbp with rsp's value immediately. We want to wait until our
  // local variables are pushed onto the stack to do that. Since pushing
  // variables changes rsp, we store rsp in a callee-save register r12, and can
  // then update rbp right before the call later.
  inst("push rbp");
  inst("mov r12, rbp");
  inst("mov rbp, rsp");

  call_t *new_call = new call_t();
  new_call->args_parsed = 0;
  new_call->fn_name = fn_str;
  call_stack.push(new_call);
}

void fun_call(char* fn_name) {
  std::string fn_str = fn_name;

  int arg_cnt = call_stack.top()->args_parsed;
  int num_fn_params = (*global_lookup(fn_str)->args).size();

  if (arg_cnt != num_fn_params) {
    error("Function %s called with %d arguments when it requires %d.",
        fn_name, arg_cnt, num_fn_params);
  }

  call_stack.pop();
  if (!call_stack.empty()) {
    curr_fn_call = call_stack.top()->fn_name;
  }

  inst("mov r12, rbp");
  inst("call %s", fn_name);
  stack_frame_end();
  inst("mov r12, rbp");
}

void fun_call_new_arg(bbtype_t type) {
  int arg_cnt = call_stack.top()->args_parsed;
  int num_fn_params = (*global_lookup(curr_fn_call)->args).size();

  if (arg_cnt+1 > num_fn_params) {
    error("Function %s called with too many arguments (only requires %d).",
        curr_fn_call.c_str(), num_fn_params);
  }

  typechk_param(type);
  call_stack.top()->args_parsed++;
}

void fun_init(char* fn_name, bbtype_t type) {
  std::string fn_str = fn_name;

  in_function = 1;
  curr_fn_name = fn_str;

  declare(type, FUN, fn_name, 0);
}

void fun_new_param(char* param_name) {
  std::string param_str = param_name;

  sym_t* fn_data = global_lookup(curr_fn_name);
  sym_t* param_data = lookup(param_name);

  fn_data->args->push_back(param_data);
}

void fun_ret(bbtype_t type) {
  // Fail on global level.
  if (!in_function) {
    error("Return statement used outside of function.");
  }

  sym_t* st_entry = global_lookup(curr_fn_name);

  if (st_entry->type == BBNONE && st_entry->type != type) {
    error("Function %s declared none but tried to return a %s.",
        curr_fn_name.c_str(), type_names[type].c_str());
  }

  typechk(type, st_entry->type);

  if (st_entry->type != BBNONE) {
    inst("pop rax");
  }

  inst("jmp .ef%d", total_functions);
}

void fun_start(char* fn_name) {
  in_function_body = 1;
  active_section = S_PROC;
  label(active_section, "%s:", fn_name);

  global_lookup(curr_fn_name)->stack_offset++;
}

void fun_end() {
  int curr_scope = scope_hist.back();
  int num_vars = (*sym_tbls[curr_scope]).size();
  int num_params = global_lookup(curr_fn_name)->args->size();
  int num_local_vars = num_vars - num_params;

  label(active_section, ".ef%d:", total_functions++);

  if (num_local_vars > 0) {
    inst("mov rsp, rbp", 8 * num_local_vars);
    inst("sub rsp, %d", 8 * (num_params + 1));
  }

  inst("ret");
  label(active_section, "");

  in_function = 0;
  in_function_body = 0;
  active_section = S_TEXT;
}
