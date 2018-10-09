#include "CodeMonkeys/TheGauntlet/LaserCannon.h"
#include "NIE.h"

using CodeMonkeys::TheGauntlet::LaserCannon;

 LaserCannon::LaserCannon() : IFireable(2.5f, false)
 {

 }

void LaserCannon::on_fire()
{
    throw NotImplementedException("LaserCannon::on_fire");
}