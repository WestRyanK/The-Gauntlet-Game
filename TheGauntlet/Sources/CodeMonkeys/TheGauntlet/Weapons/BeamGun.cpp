#include "CodeMonkeys/TheGauntlet/Weapons/BeamGun.h"
#include "CodeMonkeys/TheGauntlet/Weapons/AlternatingWeapon.h"
#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"
#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/TheGauntlet/Weapons/Projectile.h"
#include "CodeMonkeys/Engine/Collision/BoundingSphere.h"
#include "NIE.h"

using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::Engine::Collision;
using CodeMonkeys::TheGauntlet::Weapons::BeamGun;

BeamGun::BeamGun(ShaderProgram* shader, ParticleEmitter* projectile_emitter) : AlternatingWeapon("beam_gun", shader, projectile_emitter, 400, 0.2f, true)
{
    Material* projectile_material = new ColorMaterial(shader, true, 10.0f, vec3(0.8f), vec3(1.0f, 1.0f, 1.0f));
    vector<Material*> projectile_materials;
    projectile_materials.push_back(projectile_material);
    mlModel* ml_model = new mlModel();
    LoadModel("Assets/Projectiles/BeamGun", "beam_gun.obj", *ml_model);
    Model3D* model = new Model3D(ml_model, projectile_materials);
    Texture* projectile_texture = new Texture("Assets/Projectiles/BeamGun/glow.png");
    Billboard* projectile_billboard = new Billboard("projectile_glow", projectile_texture, 15, 15);
    this->projectile_prototype = new Projectile(model, projectile_billboard, "beam_gun_particle", 5, projectile_emitter, 2);

    BoundingMultiSphere* bounding_multisphere = new BoundingMultiSphere(vec3(), vec3());
    float r = 8;
    for(int i = -5; i < 10; i++)
    {
        bounding_multisphere->add_sphere(new BoundingSphere(vec3(0, 0, i * -5.0f), r));
    }
    this->projectile_prototype->set_collision_region(bounding_multisphere);

    this->sound_buffer = new sf::SoundBuffer();
    if (!this->sound_buffer->loadFromFile("Assets/Projectiles/BeamGun/beam_gun.wav"))
        printf("Could not load 'beam_gun.wav' file!\n");
    this->sound->setBuffer(*this->sound_buffer);
}