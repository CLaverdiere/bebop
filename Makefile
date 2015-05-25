# Top level makefile.

# Need bash for fancy file redirection.
SHELL := /bin/bash
CC := g++
PYTHON = python2

# Compiler name and extension (using .bb for now).
COMPILER := bebop
EXT := bb

# Directory structure
ASM_DIR := asm
BIN_DIR := bin
DOC_DIR := doc
SRC_DIR := src
TEST_DIR := tests

# Find test files expected to pass in tests/pass and remove the paths.
TEST_FILES := $(notdir $(wildcard $(TEST_DIR)/pass/*.$(EXT)))
TEST_EXECS := $(TEST_FILES:.$(EXT)=.out)

# Find test files expected to fail in tests/fail and remove the paths.
FAIL_FILES := $(notdir $(wildcard $(TEST_DIR)/fail/*.$(EXT)))

# Make just builds the compiler by default.
.PHONY: all
all:
	make $(COMPILER)

.PHONY: $(COMPILER)
$(COMPILER):
	cd $(SRC_DIR); make
	mv $(SRC_DIR)/Compiler ./$(COMPILER)

%.out: %.o
	$(CC) -g -o $@ $< -lm
	mkdir -p $(BIN_DIR)
	mv $< $(BIN_DIR)

%.o: %.asm
	nasm -f elf64 $< -o $@ -g
	mkdir -p $(ASM_DIR)
	mv $< $(ASM_DIR)

%.asm: %.$(EXT) $(COMPILER)
	./$(COMPILER) < $< > $@

# Copies test files to the top level, builds them, and moves executables /
# logfiles into the tests/ directory.
.PHONY: tests
tests:
	cp $(TEST_DIR)/pass/test* .
	make $(TEST_EXECS)
	make fails
	rm -f *.$(EXT)
	mv *.out $(TEST_DIR)/pass
	cd $(TEST_DIR); $(PYTHON) run_tests.py

# Note: Requires pandoc as dependency.
# Vim hax for the header.
.PHONY: doc
doc:
	pandoc -s -t man $(DOC_DIR)/lang.md -o $(DOC_DIR)/lang.man
	vim -c 'norm WDjddkJZZ' $(DOC_DIR)/lang.man

# Some tests are intentionally designed to fail. These are separate from
# passing tests, as make shouldn't attempt to assemble them.
# TODO may be a cleaner way of doing this.
.PHONY: fails
fails:
	cp $(TEST_DIR)/fail/fail* .
	$(foreach ff, $(FAIL_FILES), ./$(COMPILER) < $(ff) 2> $(ff).log ||: ;)
	mv *.log $(TEST_DIR)/fail

.PHONY: clean
clean:
	rm -f core $(TEST_DIR)/pass/core $(TEST_DIR)/core $(SRC_DIR)/core
	rm -rf $(ASM_DIR) $(BIN_DIR)
	rm -f $(COMPILER) *.{log,out,$(EXT)} core
	rm -f $(TEST_DIR)/pass/*.out $(TEST_DIR)/fail/*.log
	cd $(SRC_DIR); make clean
