<> This test should fail because faye is declared at a deeper level than when
<> it is referenced.

bool spike
spike = true

if spike
  if not spike
    int faye
    faye = 4
  fin
  say faye
fin
