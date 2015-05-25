<> This test uses both structs and arrays.

type game
  int levels
  float difficulty
  bool classic
fin

game fallout
fallout.difficulty = 3.4
fallout.classic = false

game final_fantasy_7
final_fantasy_7.difficulty = 3.1
fallout.classic = true

game dark_souls
dark_souls.difficulty = 8.5
fallout.classic = false

float score()
  float difficulties[3]

  difficulties[0] = final_fantasy_7.difficulty
  difficulties[1] = dark_souls.difficulty
  difficulties[2] = fallout.difficulty

  return difficulties[0] * difficulties[2] + difficulties[1]
fin

say score()
