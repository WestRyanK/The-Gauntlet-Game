#include "CodeMonkeys/TheGauntlet/LaserTurret.h"
#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"
#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/TheGauntlet/Projectile.h"
#include "CodeMonkeys/Engine/Collision/BoundingSphere.h"
#include "NIE.h"

using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::Engine::Collision;
using CodeMonkeys::TheGauntlet::LaserTurret;

LaserTurret::LaserTurret(ShaderProgram* shader, ParticleEmitter* projectile_emitter) : Weapon("laser_turret", shader, projectile_emitter, 150, 0.25f, true)
{
    Material* projectile_material = new ColorMaterial(shader, true, 10.0f, vec3(0.8f), vec3(0.9f, 0.0f, 0.9f));
    vector<Material*> projectile_materials;
    projectile_materials.push_back(projectile_material);
    mlModel* ml_model = new mlModel();
    LoadModel("Assets", "crayon.obj", *ml_model);
    Model3D* model = new Model3D(ml_model, projectile_materials);
    this->projectile_prototype = new Projectile(model, "laser_turret_particle", 5, projectile_emitter, 1);

    BoundingMultiSphere* bounding_multisphere = new BoundingMultiSphere(vec3(), vec3());
    bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, 0.0f), 5.0f));
    bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, 10.0f), 5.0f));
    bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, 5.0f), 5.0f));
    bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, -5.0f), 5.0f));
    bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, -10.0f), 5.0f));
    this->projectile_prototype->set_collision_region(bounding_multisphere);
}