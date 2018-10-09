#include "CodeMonkeys/TheGauntlet/LaserTurret.h"
#include "NIE.h"

using CodeMonkeys::TheGauntlet::LaserTurret;

LaserTurret::LaserTurret() : IFireable(0.25f, true)
{

}

void LaserTurret::on_fire()
{
    throw NotImplementedException("LaserTurret::on_fire");
}