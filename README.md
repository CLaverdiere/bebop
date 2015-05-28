Building
========

Dependencies: bison, flex, nasm

Build the compiler:

```sh
make
```

Build executable from source file source.bb:

```sh
make source.out
```

Directory Structure
===================

asm/   : Generated assembly

bin/   : Binary / Object files

doc/   : Documentation

src/   : Source files

tests/ : Tests

Documentation
=============

See doc/lang.man for extensive documentation about programming in Bebop.

Testing
=======

To run all tests, placing executables in the tests/ directory, objects in bin/
and assembly in asm/:

```sh
make tests
```

Coding style:
=============

This compiler is a hybrid of C and C++. It started out as mostly C, but I
brought in some C++ as it went along, to keep the code complexity down.

---

Chris Laverdiere, 2015
