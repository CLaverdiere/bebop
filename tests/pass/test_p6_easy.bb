<> This "easy" test demonstrates function return values for all types.
<> It also demonstrates arbitrary function nesting.
<> For type checking tests, see the fail case folder.

<> Of course we're going to do factorial.
int fact(int n)
  if n == 1
    return 1
  fin

  return n * fact(n-1)
fin

<> Lack of type promotion requires a float version of factorial.
float factf(float n)
  if n <= 1.0
    return 1.0
  fin

  return n * factf(n - 1.0)
fin

<> sin (in radians) using Taylor series expansion.
<> prec gives the precision, ie: the amount of expansion terms.
float sin(float x, int prec)
  float denom
  float result
  float coef

  denom = 1.0
  coef = 1.0

  while prec > 0
    result = result + coef * ((x ** denom) / factf(denom))
    denom = denom + 2.0
    coef = -coef
    prec = prec - 1
  fin

  return result
fin

bool xor(bool a, bool b)
  return not (a and b) and (a or b)
fin

<> Note that:
<>   fact(3) = 3 * 2 = 6
<>   fact(6) = 120 * 5 = 720
<> and
<>   sin(2.3) is roughly .7457

if xor(xor(true, true), xor(xor(false, false), true))
  say sin(factf(2.0) + 0.3, 8) + factf(factf(3.0))
fin
