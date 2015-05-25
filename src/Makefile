# Source directory makefile.

# Default Compiler
CXX := g++

# Compiler options
# Using c++0x for compatability with grading server.
OPTS := -g --std=c++11
EOPTS := -Wall

# Libraries to link with executable calculator program
LDLIBS := -lfl

# Program to run instead of lex
LEX := flex

# Program to run instead of yacc
YACC := bison

# Flags to pass to YACC program
YFLAGS := -d -v

# C / C++ files and objects
cfiles := $(wildcard *.c)
cppfiles := $(wildcard *.cpp)
cobjs := $(cfiles:.c=.o)
cppobjs := $(cppfiles:.cpp=.o)

# Object files
objs := scanner.o parser.tab.o $(cobjs) $(cppobjs)

# Compile rest of C files
.c.o:
	$(CXX) $(OPTS) $(EOPTS) -c $< -o $@

# Compile rest of C++ files
.cpp.o:
	$(CXX) $(OPTS) $(EOPTS) -c $< -o $@

# Link objects and build executable
Compiler: $(objs)
	$(CXX) $(OPTS) $(EOPTS) $(objs) -o $@ $(LDLIBS)

# Compile scanner to object file
scanner.o: scanner.cc parser.tab.hh
	$(CXX) $(OPTS) -c $< -o $@

# Compile parser to object file
parser.tab.o: parser.tab.cc
	$(CXX) $(OPTS) -c $< -o $@

# Build scanner implementation from flex file
scanner.cc: scanner.l
	$(LEX) -o $@ $<

# Build *.tab.* files from bison file
parser.tab.hh parser.tab.cc: parser.yy
	$(YACC) $(YFLAGS) $<

# Remove compilation artifacts
.PHONY: clean
clean:
	-$(RM) *.o *.tab.* scanner.cc Calc
