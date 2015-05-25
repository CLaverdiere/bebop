<> This medium test solves the digit factorials problem:
<> Not all that hard, but a good demonstration of recursion.
<> https://projecteuler.net/problem=34

int fact(int n)
  if n <= 1
    return 1
  fin

  return n * fact(n-1)
fin

int sum_fact_digits(int n)
  if n <= 0
    return 0
  fin
  return fact(n % 10) + sum_fact_digits(n / 10)
fin

int i
int sum
int lim

i = 3
lim = 41000

while i < lim
  i = i + 1
  if i == sum_fact_digits(i)
    sum = sum + i
  fin
fin

say sum
