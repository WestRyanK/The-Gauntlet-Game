#include "CodeMonkeys/TheGauntlet/Weapons/CrayonLauncher.h"
#include "CodeMonkeys/Engine/Assets/TextureMaterial.h"
#include "CodeMonkeys/Engine/Assets/AnimatedTexture.h"
#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/TheGauntlet/Weapons/GravityProjectile.h"
#include <stdlib.h>
#include <time.h>

using CodeMonkeys::TheGauntlet::Weapons::CrayonLauncher;

CrayonLauncher::CrayonLauncher(ShaderProgram* shader, ParticleEmitter* projectile_emitter) : Weapon("crayon_launcher", shader, projectile_emitter, 160, 0.1f, true)
{
        // TextureMaterial(ShaderProgram* shader, bool use_phong_highlight, float phong_exponent, vec3 phong_color, Texture* texture);
    Texture* crayon_texture = new Texture("Assets/Projectiles/CrayonLauncher/crayon_texture.png");
    this->crayon_material = new TextureMaterial(shader, false, 1.0f, vec3(1.0f), crayon_texture);
    vector<Material*> projectile_materials;
    projectile_materials.push_back(crayon_material);
    mlModel* ml_model = new mlModel();
    // LoadModel("Assets/Projectiles", "projectile_01.obj", *ml_model);
    LoadModel("Assets/Projectiles/CrayonLauncher", "crayon.obj", *ml_model);
    Model3D* model = new Model3D(ml_model, projectile_materials);
    this->projectile_prototype = new Projectile(model, NULL, "crayon_particle", 5, projectile_emitter, 1);

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

    srand (time(NULL));
}

void CrayonLauncher::on_fire()
{
    const int MIN = 50;
    const int MAX = 255;
    float r = (rand() % (MAX - MIN) + MIN) / (float)MAX;
    float g = (rand() % (MAX - MIN) + MIN) / (float)MAX;
    float b = (rand() % (MAX - MIN) + MIN) / (float)MAX;
    crayon_material->set_color(vec3(r, g, b));
    Weapon::on_fire();
}