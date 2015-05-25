#include "rt_checks.h"
#include "util.h"

// Two range checks occur: one for less than 0, and one for greater than the
// size of the array.
// rbx holds the given index, and rdx the size of the array.
void array_bounds_check(sym_t* st_entry) {
  inst("mov rdx, %d", st_entry->length);
  inst("mov rsi, rbx");

  inst("cmp rbx, 0");
  inst("jge .bcg%d", total_bounds_checks);
  inst("call array_oob_error");

  label(active_section, ".bcg%d:", total_bounds_checks++);
  inst("cmp rbx, rdx");
  inst("jl .bce%d", total_bounds_checks);
  inst("call array_oob_error");

  label(active_section, ".bce%d:", total_bounds_checks++);
}
