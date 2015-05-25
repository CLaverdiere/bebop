float i_tell_ya_hwhat(int idx, float fl)
  float bobby[5]

  bobby[idx] = fl

  if idx > 5
    say "Dangit Bobby!"
    return 0.0
  fin

  say "That boy ain't right."
  return bobby[idx]
fin

float result
result = i_tell_ya_hwhat(4, 2.4)
say result
