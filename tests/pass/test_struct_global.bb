<> This test defines two types, creates an instance of each, and assigns to all
<> fields. It also passes the type values to a function.

string ship_status(int health, int gun_ammo)
  if health < 50 and gun_ammo == 1
    return "Not doing so good!"
  fin

  if health < 50 and gun_ammo > 1
    return "Ya still got some fight in ya!"
  fin

  if health > 50 and gun_ammo > 1
    return "Good to go!"
  fin
fin

<> Type declarations
type ship
  float cost
  int health
  float damage
  int ammo
  bool exploded
  int crew
fin

type gun
  int ammo
  int model_num
fin

<> Instances of type declarations
gun pistol
ship swordfish_ii

<> Setting members
pistol.ammo = 8
pistol.model_num = 1911

swordfish_ii.exploded = false
swordfish_ii.cost = 402132.43
swordfish_ii.damage = 999.99
swordfish_ii.ammo = 35000
swordfish_ii.health = 30
swordfish_ii.crew = 5

<> Printing members
write "Cost: "
say swordfish_ii.cost

write "Ammo: "
say swordfish_ii.ammo

write "Damage: "
say swordfish_ii.damage

write "Crew: "
say swordfish_ii.crew

write "Health: "
say swordfish_ii.health

write "Exploded: "
say swordfish_ii.exploded

write "Pistol ammo: "
say pistol.ammo

write "Pistol model number: "
say pistol.model_num

say ship_status(swordfish_ii.health, pistol.ammo)
