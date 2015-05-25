<> Stress test for quoted strings and input.

<> Mixing of float inputs with variables and expressions
float tempc

say "Let's convert Fahrenheit to Celsius. Enter F in float form: "
tempc = (inp_float - 32.0) * (5.0 / 9.0)
say tempc

<> Multiple int inputs in single expression
int rnum

say "Enter 10 integers separated by newlines to get a randomish number:"
int rand1
rand1 = inp_int * (52 - 4 + inp_int * (inp_int ** 4) % inp_int - ((-(inp_int))))
int rand2
tempc = 5.4 ** 3.7  <> Distraction!
rand2 = 42 * (1 - inp_int * inp_int / (inp_int ** 3 - 1) + inp_int / inp_int)
rand2 = rand1 + rand2
say rand2
