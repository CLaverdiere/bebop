<> This easy test demonstrates basic recursion, and int, float parameters.

<> Euclidean algorithm for GCD.
int gcd(int n, int m)
  if m == 0
    return n
  fin
  return gcd(m, n % m)
fin

float mulf(float x, float y)
  float z
  z = x * y
  return z
fin

say gcd(34, 85)
say mulf(2.6, 4.7)
