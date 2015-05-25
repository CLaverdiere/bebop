<> This test attempts to find the sum of the first n prime numbers.

int cand
int factor
int lim
int count
int sum
bool fail

sum = 0
count = 0
cand = 2
lim = 100

while count < lim
  factor = 2
  fail = false
  while (factor ** 2 <= cand) and (not fail)
    if cand % factor == 0
      fail = true
    fin
    factor = factor + 1
  fin

  if not fail
    <> write cand
    <> write ", "
    count = count + 1
    sum = sum + cand
  fin

  cand = cand + 1
fin

<> say "and done."
say sum
