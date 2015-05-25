<> This test should fail because faye is referenced at the same level, but
<> inside of a different block.

float spike
spike = 4.5

if spike > 3.0
  int faye
  faye = 4
fin

if spike < 3.0
  say faye
fin
