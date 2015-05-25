<> This tests the following for basic functionality.
<>   all integer / float comparisons
<>   and / or / not logical operators
<>   nested if statements / while loops with simple conditions.
<> A string is produced with results of each computation.

bool no
bool yes

int x
int y
int count

float z
float w

yes = true
no = false

x = 3
y = x

z = 7.1423
w = 7.1432

<> say "Not truth table:"
write not yes
write not no

<> say "And truth table:"
write (no and no)
write (no and yes)
write (yes and no)
write (yes and yes)

<> say "Or truth table:"
write (no or no)
write (no or yes)
write (yes or no)
write (yes or yes)

<> say "Relational operators: (int)"
write x == y
write x != y
write x >  y
write x >= y
write x <  y
write x <= y

<> say "Relational operators: (float)"
write z == w
write z != w
write z >  w
write z >= w
write z <  w
write z <= w

<> say "Nested if statements:"
if x == 3
  x = 4
  if y == 7
    y = 11
  fin
fin
write x
write y

<> say "Nested while loops:"
x = 0
y = 0
while x < 5
  write x
  x = x + 1
  while y < 5
    write y
    y = y + 1
  fin
  y = x
fin
