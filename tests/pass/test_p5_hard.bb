<> This hard test pulls from:
<> https://projecteuler.net/problem=3
<> https://projecteuler.net/problem=21
<> It sums the results.

<> This test demonstrates local and global scope pretty heavily. See medium and
<> easy tests for recursion.

int total
int sum
int lsum
sum = 0
lsum = 0

<> Largest prime factor
int largestpf(int n)
  int largest
  int i
  i = 0

  while i < n
    i = i + 1
    if n % i == 0
      n = n / i

      if largest < i
        largest = i
      fin
    fin
  fin

  <> say largest
  sum = largest
  return largest
fin

<> Sum of proper divisors
int sumdivs(int n)
  int sum
  int i

  sum = 0
  i = 0

  while i <= (n / 2)
    i = i + 1
    if n % i == 0
      <> Note that this sum is local.
      sum = sum + i
    fin
  fin

  lsum = sum
  return lsum
fin

<> Amicable numbers
int amicable(int x, int y)
  int xs
  int ys

  xs = sumdivs(x)
  ys = sumdivs(y)

  sum = 0
  if xs == y and ys == x
    <> say " are amicable!"
    return x + y
  fin

  <> say " are not amicable."
fin

<> Should be 29 + 504 = 533
<> I can't believe this actually works holy shit!
say largestpf(13195) + amicable(220, 284)
