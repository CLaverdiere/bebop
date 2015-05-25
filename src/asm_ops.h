// This file contains functions for managing assembly output.

#ifndef  ASMOPS_H
#define  ASMOPS_H

#include <iostream>
#include <sstream>

// Section enum for refering to section of the assembly file. Mostly used to
// switch on stringstreams.
typedef enum {
  S_DATA,
  S_PROC,
  S_TEXT
} section_t;

// Throughout the life of the parser, data is collected into separate
// stringstreams, rather having instructions output sequentially. This gives us
// more control over the ordering of the final assembly file. Note that
// text_out only contains the main procedure instructions.
extern std::stringstream data_out;
extern std::stringstream proc_out;
extern std::stringstream text_out;

// Writes an instruction string with an optional printf like format to the text
// string stream. Also includes a tab between the instruction and its
// arguments. The "label" variant excludes the tab at the start of the line,
// and allows specification of a section for the label to go in. As
// instructions only appear in the text section, no choice of section is given.
void inst(section_t, const char* fmt, ...);
void inst(const char* fmt, ...);
void label(section_t section, const char* fmt, ...);

// After the parser has read all input, the compiler outputs all data collected
// from each stringstream into the final assembly file.
void write_asm();

#endif
