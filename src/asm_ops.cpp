#include <stdarg.h>

#include "asm_ops.h"
#include "util.h"

// Uses a variable length list to create a string to be passed to into the text
// stringstream. Pretty slick.
void inst(const char* fmt, ...) {
  char* pstr;
  va_list args;

  va_start(args, fmt);
  vasprintf(&pstr, fmt, args);
  va_end(args);

  // Find the first space (separation between instruction and arguments) and
  // replace it with a tab.
  int c = 0;
  while(pstr[c] != ' ' && pstr[c] != '\0') {
    c++;
  };

  if(pstr[c] != '\0') { pstr[c] = '\t'; };

  switch(active_section) {
    case S_PROC:
      proc_out << "\t" << pstr << std::endl;
      break;
    case S_TEXT:
    default:
      text_out << "\t" << pstr << std::endl;
  }

  free(pstr);
}

void label(section_t section, const char* fmt, ...) {
  char* pstr;
  va_list args;

  va_start(args, fmt);
  vasprintf(&pstr, fmt, args);
  va_end(args);

  switch(section) {
    case S_DATA:
      data_out << pstr << std::endl;
      break;
    case S_PROC:
      proc_out << pstr << std::endl;
      break;
    case S_TEXT:
      text_out << pstr << std::endl;
      break;
    default:
      yyerror("Invalid section ID given to label call.");
  }

  free(pstr);
}

// TODO maybe read files into buffers instead to remove file dependency once
// compiled.
void write_asm() {

  // Any code that goes at the top of the file.
  print_file(SBP_FILENAME);

  // Extern function declarations at the top of the file.
  print_file(EXTERNS_FILENAME);

  // .data section
  std::cout << "\n\tSECTION .data\n" << std::endl;

  // Formatting string declarations.
  print_file(STRINGS_FILENAME);
  std::cout << std::endl;

  // Write the entire .data section block.
  std::cout << data_out.str();

  // .text section
  std::cout << "\n\tglobal main\n" << std::endl;
  std::cout << "\tSECTION .text\n" << std::endl;

  // Include any procedures.
  print_file(PROC_FILENAME);
  std::cout << std::endl;
  std::cout << proc_out.str();

  // Setup main stack frame.
  std::cout << "main:" << std::endl;
  std::cout << "\tpush\trbp" << std::endl;
  std::cout << "\tmov\trbp, rsp" << std::endl;

  // Write the entire .text section block.
  std::cout << text_out.str();

  // Any code that goes at the end of the file.
  print_file(EBP_FILENAME);
}
