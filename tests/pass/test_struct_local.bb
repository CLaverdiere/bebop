<> This test creates types inside of a function, and returns computations of
<> member values.

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

int gun_shop(int red_herring, float blue_herring)
  gun order
  order.model_num = 500
  order.ammo = 6

  return order.ammo * order.model_num
fin

int ship_shop(bool useless)
  ship new_ride
  new_ride.health = 50000
  new_ride.exploded = false
  new_ride.ammo = 12500

  return new_ride.health + new_ride.ammo
fin

say ship_shop(false) + gun_shop(1, 1.0)
