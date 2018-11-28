#include "CodeMonkeys/TheGauntlet/LaserCannon.h"
#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"
#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/TheGauntlet/Projectile.h"

using CodeMonkeys::TheGauntlet::LaserCannon;

LaserCannon::LaserCannon(ShaderProgram* shader, ParticleEmitter* projectile_emitter) : Weapon("laser_cannon", shader, projectile_emitter, 20, 2.5f, false)
{
    Material* projectile_material = new ColorMaterial(shader, true, 10.0f, vec3(0.8f), vec3(0.9f, 0.0f, 0.9f));
    vector<Material*> projectile_materials;
    projectile_materials.push_back(projectile_material);
    mlModel* ml_model = new mlModel();
    LoadModel("Assets", "crayon.obj", *ml_model);
    Model3D* model = new Model3D(ml_model, projectile_materials);
    this->projectile_prototype = new Projectile(model, "laser_turret_particle", 5, projectile_emitter, 5);
}