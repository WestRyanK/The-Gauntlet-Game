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

LaserTurret::LaserTurret(ShaderProgram* shader, ParticleEmitter* projectile_emitter) : Weapon("laser_turret", shader, projectile_emitter, 190, 0.35f, true)
{
    Material* projectile_material = new ColorMaterial(shader, true, 10.0f, vec3(0.8f), vec3(1.0f, 1.0f, 1.0f));
    vector<Material*> projectile_materials;
    projectile_materials.push_back(projectile_material);
    mlModel* ml_model = new mlModel();
    LoadModel("Assets/Projectiles", "projectile_01.obj", *ml_model);
    Model3D* model = new Model3D(ml_model, projectile_materials);
    Texture* projectile_texture = new Texture("Assets/Textures/Projectiles/flare.png");
    Billboard* projectile_billboard = new Billboard("projectile_flare", projectile_texture, 15, 15);
    this->projectile_prototype = new Projectile(model, projectile_billboard, "laser_turret_particle", 5, projectile_emitter, 1);

    BoundingMultiSphere* bounding_multisphere = new BoundingMultiSphere(vec3(), vec3());
    float r = 6;
    bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, 0.0f), r));
    bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, -5.0f), r));
    bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, -10.0f), r));
    bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, 15.0f), r));
    bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, 20.0f), r));
    bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, -15.0f), r));
    bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, -20.0f), r));
    bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, 5.0f), r));
    this->projectile_prototype->set_collision_region(bounding_multisphere);
}

void LaserTurret::on_fire()
{
    vec3 new_position = this->get_position();
    new_position.x = -new_position.x;
    this->set_position(new_position);
    Weapon::on_fire();
}