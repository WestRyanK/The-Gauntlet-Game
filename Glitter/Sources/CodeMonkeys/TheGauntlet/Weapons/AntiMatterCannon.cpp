#include "CodeMonkeys/TheGauntlet/Weapons/AntiMatterCannon.h"
#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"
#include "CodeMonkeys/Engine/Assets/AnimatedTexture.h"
#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/TheGauntlet/Weapons/GravityProjectile.h"

using CodeMonkeys::TheGauntlet::Weapons::AntiMatterCannon;

AntiMatterCannon::AntiMatterCannon(ShaderProgram* shader, ParticleEmitter* projectile_emitter) : Weapon("antimatter_cannon", shader, projectile_emitter, 380, 2.5f, false)
{
    Material* projectile_material = new ColorMaterial(shader, true, 10.0f, vec3(0.8f), vec3(0.9f, 0.0f, 0.9f));
    vector<Material*> projectile_materials;
    projectile_materials.push_back(projectile_material);
    AnimatedTexture* projectile_animation = new AnimatedTexture("Assets/Projectiles/AntiMatterCannon/anti_matter_cannon", "png", 16);
    Billboard* projectile_billboard = new Billboard("billboard_antimatter", projectile_animation, 15, 15);
    this->projectile_prototype = new GravityProjectile(NULL, projectile_billboard, "antimatter_cannon_particle", 5, projectile_emitter, 5);


    BoundingMultiSphere* bounding_multisphere = new BoundingMultiSphere(vec3(), vec3());

    float r = 10;
    for(int i = 0; i < 3; i++)
    {
        bounding_multisphere->add_sphere(new BoundingSphere(vec3(0, 0, i * -5.0f), r));
    }
    this->projectile_prototype->set_collision_region(bounding_multisphere);

    this->sound_buffer = new sf::SoundBuffer();
    if (!this->sound_buffer->loadFromFile("Assets/Projectiles/AntiMatterCannon/anti_matter_cannon.wav"))
        printf("Could not load 'anti_matter_cannon.wav' file!\n");
    this->sound->setVolume(65.0f);
    this->sound->setBuffer(*this->sound_buffer);
}