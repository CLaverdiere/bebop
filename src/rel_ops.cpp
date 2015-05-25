#include <string.h>

#include "rel_ops.h"
#include "asm_ops.h"
#include "util.h"

bbtype_t rel_cmp(bbtype_t a, bbtype_t b, const char* cmp) {
  char* fcmp = strdup(cmp);

  typechk(a, b);

  switch(a) {
    case BBFLOAT:
      // Rather than using jg and jl instructions for floats, we must use ja
      // and jb, due to the use of CF. This is a quick hack around that.
      if(fcmp[0] == 'g') fcmp[0] = 'a';
      else if(fcmp[0] == 'l') fcmp[0] = 'b';

      inst("xor rcx, rcx");
      inst("fld QWORD [rsp]");
      inst("fld QWORD [rsp+8]");
      inst("add rsp, 16");
      inst("fcomi st1");
      inst("set%s cl", fcmp);
      inst("push rcx");
      inst("fstp st0");
      inst("fstp st0");

      free(fcmp);
      break;
    case BBINT:
      inst("xor rcx, rcx");
      inst("pop rbx");
      inst("pop rax");
      inst("cmp rax, rbx");
      inst("set%s cl", cmp);
      inst("push rcx");
      break;
    default:
      error("Relational operators not supported for type %s",
          type_names[a].c_str());
  }

  return BBBOOL;
}
