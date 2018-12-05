#pragma once

#include "CodeMonkeys/TheGauntlet/Weapons/Weapon.h"
#include "CodeMonkeys/Engine/Assets/TextureMaterial.h"

using namespace CodeMonkeys::Engine::Assets;

namespace CodeMonkeys::TheGauntlet::Weapons
{
    class CrayonLauncher : public Weapon
    {
    private:
        TextureMaterial* crayon_material = NULL;
    protected:
        virtual void on_fire();
    public:
        CrayonLauncher(ShaderProgram* shader, ParticleEmitter* projectile_emitter);
    };
}