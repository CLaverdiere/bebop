<> This tests integer comparisons, nested if / while statements.

<> Get an integer n from the user, and return whether the collatz sequence for
<> n terminates in less than lim iterations.

int n
int oldn
int count
int lim

write "Enter a number to test collatz termination on: "
n = inp_int

write n

count = 0
lim = 10

while n != 1
  oldn = n

  if oldn % 2 == 0
    n = n / 2
  fin

  if oldn % 2 == 1
    n = (3 * n) + 1
  fin

  count = count + 1

  write " -> "
  write n
fin

say " and done"

if count >= lim
  write "Sequence doesn't converge in under "
  write lim
  say " iterations."
fin

if count < lim
  write "Sequence does converge in under "
  write lim
  say " iterations!"
fin
