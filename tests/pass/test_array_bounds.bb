<> This test does array bounds checking. If the array assignment isn't out of
<> bounds, then "HI THERE" should print.
float lookup(int x)
  float arr[100]
  float y

  y = 5.0
  arr[x] = y

  say "HI THERE"

  return arr[x]
fin

lookup(101)
