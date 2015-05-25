Bebop 7 "February 2015" "CMSC 431" "User Manuals"

NAME
====

Bebop \- A classy language created for the compilers class at UMBC.

DESCRIPTION
===========

Bebop resembles a mix of Python and Ruby. Bebop is compiled to the x86_64
assembly language with the **bebop** compiler, from which an executable program
can be assembled and linked using **nasm(1)** and **gcc(1)** respectively.

This manual is ordered roughly by usefulness. There's an examples section at the
end if you just feel like skipping to that.

LANGUAGE
========

Language Grammar
----------------

The following statements are supported. Statements can have multiple newlines
between them.

type variable
:   Declare variable as the given type.

variable = expression
:   Assign the value of expression to variable. Variables must be declared before
    assigned.

say expression
:   Print the value of an expression with a newline. Non-newline version **write**
    also available.

Type System
-----------

Bebop supports types for integers, floating point numbers, booleans, and
strings. There is also a **none** type, similar to 'void' in other languages. This
keyword is reserved for function return types.

Keywords:
:   **bool, float, int, none, string**

Note that the *string* type is heavily restricted, and can only be passed to /
returned from functions, and printed out. All other operations using strings are
undefined.

Bebop only supports static typing. Currently, there is no support for type
promotion, and Bebop will laugh at you for mismatching types.

Boolean expressions and relations
---------------------------------

Boolean variables can be assigned expressions of **true** or **false.**
Internally, these are represented as 1s and 0s, and will be printed out as such.

Boolean expressions can currently compare integers and floats.

Boolean Comparison:
:   **value `<operator>` value**

Supported operators:
:   **==, !=, <, <=, >, >=**

To combine boolean relations, logical operators **not, and,** and **or** may be
used, in order of highest to lowest precedence.

Program Control
---------------

Both if and while control structures are supported. Each control block must be
closed with a **fin** keyword.

**If statements:**

    if boolean_expression
      statements
    fin

**While loops:**

    while boolean_expression
      statements
    fin

While loops may contain **next** and **leave** statements, analogous to **continue**
and **break** in other languages.

Arrays
------

Bebop supports basic arrays with bounds checking:

Array declaration:
:   type array_name[size]

Arrays cannot be declared with a variable size, but when referencing the array,
the index may be any valid integer expression.

Array assignment:
:   array_name[int_expr] = expr

Arrays cannot be of type string.

User defined types (structs)
----------------------------

Bebop supports custom types with primitive members (int, float, bool).

Type declaration (note: **type** is literally the word *"type"*.):

    type name
      primitive declarations
    fin

Instances of types must be declared like all other variables.

Declare instance (note: **type** is **not** literally the word *"type"*.):

    type instance_name

Types can have their members used in expressions and passed to functions.
Currently, types cannot be passed / returned directly from functions.

Member access:
:   instance.member

Functions
---------

Bebop currently supports functions with return values.

**Function declaration:**

    type function_name(type1 arg1, ..., typeN argN)
      declarations
      statements
      return expr
    fin

Functions may be declared type **none** when they don't return any value.

All local variables **must** be declared at the top of the function.

Note that **return** can be placed anywhere in the function body, to break out
of the function.

Functions are called the way one would expect:

**Function call:**
:   function_name(arg1, ..., argN)

The **number** and **type** of arguments are checked when the function is called.

Functions may be **recursively** called.

Scoping
-------

Bebop supports both **local** and **global** variables. All variables declared
outside of a function are global, and support lexical scoping rules.

Variables declared inside a function are local, and can use the same name as a
global variable without conflict. Lexical scoping is currently **not** supported
for local variables.

Printing Output
---------------

To print the value of an expression, use **say expression.** The variant
**write** excludes the newline from printing.

User Input
----------

The keywords **inp_int** and **inp_float** are reserved for user input. When
encountered, the compiler calls scanf internally and captures input as the
resulting expression.

Comments
--------

the '<>' symbol starts a comment, and discards the rest of the line. Comments
can be placed anywhere in the line, but do not span multiple lines.

Mathematical Operations
-----------------------

The following mathematical operations are supported in decreasing order of
precedence. Expressions may be constructed from signed 64 bit integers, or
other mathematical expressions.

**(expression)**
:   Parentheses. Override precedence of operators outside the parentheses.

**expression `**` expression**
:   Integer exponentiation. Returns 1 if exponent is less than 1.

**-expression**
:   Negation.

**expression * expression**
:   Multiplication. Same precedence as division and modulus.

**expression / expression**
:   Division. Same precedence as multiplication and modulus.

**expression % expression**
:   Modulus. Same precedence as multiplication and division.

**expression + expression**
:   Addition. Same precedence as subtraction.

**expression - expression**
:   Subtraction. Same precedence as addition.

Reserved Keywords
-----------------

Several keywords are used by the compiler and must not be used as variables.
It's probably a safe bet to stay away from any variable 3 letters or shorter,
though necessary ones like *i* are fine.

Reserved keywords:
:    all type keywords, input keywords, main, fmt, [cfs]{number}, intpow

EXAMPLES
========

Simple assignment / arithmetic:
-------------------------------

    int spike
    int faye

    spike = 7
    faye = 4

    <> This is a comment.
    say spike + faye

User input:
-----------

    float ein
    float ed

    ein = inp_float + 7.0
    ed = ein * inp_float ** inp_float / 4.0

    say ein - ed

Conditionals:
-------------

    int jet
    bool flag

    jet = 5
    flag = true

    if (jet != 5) and flag
      say "jet is not 5."
    fin

Functions:
----------

    int countdown(int n)
      say n

      if n == 0
        return n
      fin

      return countdown(n - 1)
    fin

    say "Counting down!"
    fun(20)

Lexical Scoping
---------------

    int var
    var = 1

    if var > 0
      float var
      var = 2.22

      if var != 2.22  <> You can (not) advance
        int var
        var = 3
        say var
      fin
    fin

Arrays
------

    int lotto_nums[7]

    lotto_nums[0] = 4
    lotto_nums[1] = 8
    ...
    lotto_nums[6] = 7

    say lotto_nums[7] <> Out of bounds error.

User defined types
------------------

    type car
      int num_homies
      float cost
      bool chick_magnet
    fin

    car my_car

    my_car.num_homies = 1
    my_car.cost = 1250.00
    my_car.chick_magnet = false

LIMITATIONS
===========

- A **newline** is required after each program statement. No brackets for you.

- Variables may not be named as reserved keywords.

- While booleans are represented as 1s and 0s, they cannot be mixed with
  integers.

AUTHOR
======

Chris Laverdiere <chlaver1@umbc.edu>
