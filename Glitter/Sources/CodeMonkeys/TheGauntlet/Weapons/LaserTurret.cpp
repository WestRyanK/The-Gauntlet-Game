#include <SFML/Audio.hpp>
#include "CodeMonkeys/TheGauntlet/Weapons/LaserTurret.h"
#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"
#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/TheGauntlet/Weapons/Projectile.h"
#include "CodeMonkeys/Engine/Collision/BoundingSphere.h"
#include "NIE.h"

using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::Engine::Collision;
using CodeMonkeys::TheGauntlet::Weapons::LaserTurret;

LaserTurret::LaserTurret(ShaderProgram* shader, ParticleEmitter* projectile_emitter) : AlternatingWeapon("laser_turret", shader, projectile_emitter, 190, 0.35f, true)
{
    Material* projectile_material = new ColorMaterial(shader, true, 10.0f, vec3(0.8f), vec3(1.0f, 1.0f, 1.0f));
    vector<Material*> projectile_materials;
    projectile_materials.push_back(projectile_material);
    mlModel* ml_model = new mlModel();
    LoadModel("Assets/Projectiles/LaserTurret", "laser_turret.obj", *ml_model);
    Model3D* model = new Model3D(ml_model, projectile_materials);
    Texture* projectile_texture = new Texture("Assets/Projectiles/LaserTurret/glow.png");
    Billboard* projectile_billboard = new Billboard("projectile_glow", projectile_texture, 15, 15);
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


   
    this->sound_buffer = new sf::SoundBuffer();
    if (!this->sound_buffer->loadFromFile("Assets/Projectiles/LaserTurret/laser_turret.wav"))
        printf("Could not load 'laser_turret.wav' file!\n");
    this->sound->setBuffer(*this->sound_buffer);
}