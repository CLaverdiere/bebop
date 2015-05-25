int sum
int x
int y

x = 10
y = 0

while x > 0
  x = x - 1
  y = 0

  while y < 10
    y = y + 1

    if y > 6
      leave
    fin

    if y % 2 == 0
      next
    fin

    <> write x
    <> write " : "
    <> say y

    sum = sum + x + y
  fin

  if x <= 5
    leave
  fin
fin

say sum
