#pragma once

#include "CodeMonkeys/TheGauntlet/ITriggerable.h"
#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"
#include "CodeMonkeys/TheGauntlet/Projectile.h"
#include <string>

using namespace std;
using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::TheGauntlet
{
    class Weapon : public ITriggerable, public PhysicalObject3D
    {
    protected:
        virtual void on_fire();
        Projectile* projectile_prototype = NULL;
        ParticleEmitter* projectile_emitter = NULL;
        float initial_velocity = 0;
        ShaderProgram* shader;
    
    public:
        Weapon(string name, ShaderProgram* shader, ParticleEmitter* projectile_emitter, float initial_velocity, float recharge_delay, bool is_automatic_fire);
    };
}