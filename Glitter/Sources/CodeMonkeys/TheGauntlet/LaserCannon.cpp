#include "CodeMonkeys/TheGauntlet/LaserCannon.h"
#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"
#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/TheGauntlet/GravityProjectile.h"

using CodeMonkeys::TheGauntlet::LaserCannon;

LaserCannon::LaserCannon(ShaderProgram* shader, ParticleEmitter* projectile_emitter) : Weapon("laser_cannon", shader, projectile_emitter, 130, 2.5f, false)
{
    Material* projectile_material = new ColorMaterial(shader, true, 10.0f, vec3(0.8f), vec3(0.9f, 0.0f, 0.9f));
    vector<Material*> projectile_materials;
    projectile_materials.push_back(projectile_material);
    mlModel* ml_model = new mlModel();
    LoadModel("Assets", "crayon.obj", *ml_model);
    Model3D* model = new Model3D(ml_model, projectile_materials);
    this->projectile_prototype = new GravityProjectile(model, "laser_cannon_particle", 5, projectile_emitter, 5);

    BoundingMultiSphere* bounding_multisphere = new BoundingMultiSphere(vec3(), vec3());
    bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, 0.0f), 10.0f));
    this->projectile_prototype->set_collision_region(bounding_multisphere);
}