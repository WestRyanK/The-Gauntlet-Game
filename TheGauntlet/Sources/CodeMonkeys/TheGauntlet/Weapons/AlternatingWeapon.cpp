#include "CodeMonkeys/TheGauntlet/Weapons/AlternatingWeapon.h"
#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"
#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/TheGauntlet/Weapons/Projectile.h"
#include "CodeMonkeys/Engine/Collision/BoundingSphere.h"
#include "NIE.h"

using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::Engine::Collision;
using CodeMonkeys::TheGauntlet::Weapons::AlternatingWeapon;

AlternatingWeapon::AlternatingWeapon(string name, ShaderProgram* shader, ParticleEmitter* projectile_emitter, float initial_velocity, float recharge_delay, bool is_automatic_fire)
    : Weapon(name, shader, projectile_emitter, initial_velocity, recharge_delay, is_automatic_fire)
{
}

void AlternatingWeapon::on_fire()
{
    vec3 new_position = this->get_position();
    new_position.x = -new_position.x;
    this->set_position(new_position);
    Weapon::on_fire();
}