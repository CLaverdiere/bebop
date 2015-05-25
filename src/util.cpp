#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <stdarg.h>
#include "util.h"

// Boilerplate paths are relative to src/boilerplate.
const char* SBP_FILENAME = "src/boilerplate/start_bp.asm";
const char* EBP_FILENAME = "src/boilerplate/end_bp.asm";

// Other boilerpate paths.
const char* EXTERNS_FILENAME = "src/boilerplate/externs.asm";
const char* STRINGS_FILENAME = "src/boilerplate/strings.asm";
const char* PROC_FILENAME = "src/boilerplate/procedures.asm";

std::vector<std::string> insults =
{
  "*applause*",
  "are you even trying?",
  "are you sure you want to be a programmer?",
  "bravo!",
  "come on now.",
  "give me a break.",
  "good job!",
  "how pathetic.",
  "http://www.codecademy.com/",
  "lol.",
  "nice try though!",
  "nice.",
  "oh boy.",
  "ouch.",
  "please.",
  "stahp",
  "that hurts you know!",
  "you'll shoot your eye out kid!",
  "zzz...",
};

std::string insult() {
  srand(time(NULL));
  return insults[rand() % insults.size()];
}

void print_file(const char* filename) {
  char* line;
  size_t size = 0;
  FILE *fp = fopen(filename, "r");
  if(fp == NULL) {
    printf("Can't open file: %s\n", filename);
    exit(EXIT_FAILURE);
  }
  while(getline(&line, &size, fp) != EOF) {
    printf("%s", line);
  };
}

void error(const char* fmt, ...)
{
  va_list args;

  fprintf(stderr, "Parser error (line %d): ", line_num);

  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);

  fprintf(stderr, " %s\n", insult().c_str());

  exit(EXIT_FAILURE);
}

// TODO Code duplication with error.
// TODO Warn about unused variables. That would be cool.
void warning(const char* fmt, ...) {
  va_list args;

  fprintf(stderr, "Parser warning (line %d): ", line_num);

  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);

  fprintf(stderr, "\n");

  exit(EXIT_FAILURE);
}
