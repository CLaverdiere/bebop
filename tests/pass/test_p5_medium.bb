<> This medium test demonstrates:
<>   lexical scoping (spike)
<>   multiple procedure calls (fib, fibh, goodbye)
<>   parameter passing (single and multiple)
<>   recursion (fibh -> fibh)

<> Fib helper.
int fibh(int x, int y, int n)
  int spike
  spike = y - x

  if n <= 0
    return spike
  fin

  return fibh(y, x + y, n - 1)
fin

<> Fib start.
int fib(int n)
  return fibh(1, 1, n)
fin

none goodbye(bool nice)
  if nice
    say "Have a nice day!"
  fin

  if not nice
    say "Now get out."
  fin
fin

int spike
spike = 10

say fib(spike)
goodbye(false)
