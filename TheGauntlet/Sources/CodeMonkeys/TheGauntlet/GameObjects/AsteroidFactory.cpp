#include "CodeMonkeys/TheGauntlet/GameObjects/AsteroidFactory.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Asteroid.h"
#include "CodeMonkeys/Engine/Assets/LoopSubdivider.h"
#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"
#include <time.h>
#include <iostream>
#include <stdlib.h>

using CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory;
using namespace CodeMonkeys::TheGauntlet::GameObjects;

float AsteroidFactory::ratio_asteroids_large = 1;
float AsteroidFactory::ratio_asteroids_medium = 1;
float AsteroidFactory::ratio_asteroids_small = 1;
vector<Material*>* AsteroidFactory::asteroid_materials = new vector<Material*>();
IScoreKeeper* AsteroidFactory::score_keeper = NULL;

Asteroid* AsteroidFactory::create_asteroid(int size_class)
{
    unsigned int health = 0;
    unsigned int inflict_amount = 0;
    float points = 0;
    if (size_class == Asteroid::SMALL)
    {
        health = Asteroid::SMALL_HEALTH;
        inflict_amount = Asteroid::SMALL_INFLICT;
        points = Asteroid::SMALL_POINTS;
    } else if (size_class == Asteroid::MEDIUM)
    {
        health = Asteroid::MEDIUM_HEALTH;
        inflict_amount = Asteroid::MEDIUM_INFLICT;
        points = Asteroid::MEDIUM_POINTS;
    } 
    else if (size_class == Asteroid::LARGE)
    {
        health = Asteroid::LARGE_HEALTH;
        inflict_amount = Asteroid::LARGE_INFLICT;
        points = Asteroid::LARGE_POINTS;
    }

    const int SCALE = 4;
    mlModel* ml_model = AsteroidFactory::load_asteroid_model(size_class  * SCALE);
    AsteroidFactory::add_noise_to_model(ml_model, size_class * SCALE, 1, true);
    Model3D* model = AsteroidFactory::create_asteroid_model(ml_model);

    Asteroid* asteroid = new Asteroid(model, size_class, health, size_class * SCALE, inflict_amount, points, AsteroidFactory::score_keeper);

    return asteroid;
}

mlModel* AsteroidFactory::load_asteroid_model(float scale)
{
    float one_over_sqrt_2 = 1/sqrt(2.0);

    // Geometric definition of cube
    mlMesh* mesh = new mlMesh();
    vector<mlVertex> vertices;
    mlVertex a;
    a.position = vec3(-scale, -scale, -scale);
    vertices.push_back(a);
    mlVertex b;
    b.position = vec3(scale, -scale, -scale);
    vertices.push_back(b);
    mlVertex c;
    c.position = vec3(scale, -scale, scale);
    vertices.push_back(c);
    mlVertex d;
    d.position = vec3(-scale, -scale, scale);
    vertices.push_back(d);
    mlVertex e;
    e.position = vec3(-scale, scale, -scale);
    vertices.push_back(e);
    mlVertex f;
    f.position = vec3(scale, scale, -scale);
    vertices.push_back(f);
    mlVertex g;
    g.position = vec3(scale, scale, scale);
    vertices.push_back(g);
    mlVertex h;
    h.position = vec3(-scale, scale, scale);
    vertices.push_back(h);
    vector<unsigned int> indices = { 0, 1, 3, 1, 2, 3, 4, 5, 7, 5, 6, 7, 0, 1, 4, 1, 5, 4, 1, 2, 5, 2, 6, 5, 2, 3, 6, 3, 7, 6, 3, 0, 7, 0, 4, 7 };

    mesh->vertices = vertices;
    mesh->indices = indices;

    mlModel* model = new mlModel();
    model->meshes.push_back(mesh);
    return model;
}

void AsteroidFactory::add_noise_to_model(mlModel* ml_model, int asteroid_size, int noise_iterations, bool is_jagged)
{
    float max_noise;
    if (is_jagged)
        max_noise = asteroid_size * 0.25f;
    else
        max_noise = asteroid_size * 0.75f;

    for (int i = 0; i < noise_iterations; i++)
    {
        for (int mesh_index = 0; mesh_index < ml_model->meshes.size(); mesh_index++)
        {

            if (is_jagged)
            {
                mlMesh* mesh = CodeMonkeys::Engine::Assets::LoopSubdivider::subdivide_mesh(ml_model->meshes[mesh_index], 1);
                free(ml_model->meshes[mesh_index]);
                ml_model->meshes[mesh_index] = mesh;
            }

            // Mutate along axis.
            for (int axis = 0; axis < 3; axis++)
            {

                // Add noise
                for (int vertex_index = 0; vertex_index < ml_model->meshes[mesh_index]->vertices.size(); vertex_index++)
                {
                    float position = ml_model->meshes[mesh_index]->vertices[vertex_index].position[axis];
                    float noise_offset = AsteroidFactory::rand_centered(0.0f, max_noise);
                    position += noise_offset;
                    ml_model->meshes[mesh_index]->vertices[vertex_index].position[axis] = position;
                }
            }
            if (!is_jagged)
            {
                mlMesh* mesh = CodeMonkeys::Engine::Assets::LoopSubdivider::subdivide_mesh(ml_model->meshes[mesh_index], 1);
                free(ml_model->meshes[mesh_index]);
                ml_model->meshes[mesh_index] = mesh;
            }
        }
        max_noise = max_noise * 0.750f;
    }
}

float AsteroidFactory::rand_centered(float center, float spread_radius)
{
    return AsteroidFactory::rand_min_max(center - spread_radius, center + spread_radius);
}

float AsteroidFactory::rand_min_max(float min, float max)
{
    int RESOLUTION = 1000;
    int range = max - min;

    float random_value = (rand() % RESOLUTION) / (float)RESOLUTION;
    random_value *= range;
    random_value += min;

    return random_value;
}

Model3D* AsteroidFactory::create_asteroid_model(mlModel* ml_model)
{
    int color_index = rand() % AsteroidFactory::asteroid_materials->size();
    Material* mat = (*AsteroidFactory::asteroid_materials)[color_index];
    vector<Material*>* new_materials = new vector<Material*>();
    new_materials->push_back(mat);
    Model3D* model = new Model3D(ml_model, *new_materials);
    return model;
}

Asteroid* AsteroidFactory::create_asteroid_random_size()
{
    float cumulative_sum_small = AsteroidFactory::ratio_asteroids_small;
    float cumulative_sum_medium = AsteroidFactory::ratio_asteroids_medium + cumulative_sum_small;
    float cumulative_sum_large = AsteroidFactory::ratio_asteroids_large + cumulative_sum_medium;

    float random_value = rand() % (int)cumulative_sum_large;

    unsigned int size = 0;
    if (random_value < cumulative_sum_small) 
    {
        size = Asteroid::SMALL;
    } else if (random_value < cumulative_sum_medium)
    {
        size = Asteroid::MEDIUM;
    } else
    {
        size = Asteroid::LARGE;
    }

    return AsteroidFactory::create_asteroid(size);
}

void AsteroidFactory::init_asteroid_factory(unsigned int seed, ShaderProgram* shader, IScoreKeeper* score_keeper)
{
    if (seed == 0)
    {
        srand(time(NULL));
    }
    else
    {
        srand(seed);
    }
    vector<vec3> asteroid_colors;
    asteroid_colors.push_back(vec3(0.4f));
    asteroid_colors.push_back(vec3(0.5f));
    asteroid_colors.push_back(vec3(0.4f, 0.3f, 0.25f));
    asteroid_colors.push_back(vec3(0.4f, 0.35f, 0.3f));

    vector<Material*>* asteroid_materials = new vector<Material*>();
    for (int i = 0; i < asteroid_colors.size(); i++)
    {
        Material* asteroid_material = new ColorMaterial(shader, false, 1.0f, vec3(1.0f), asteroid_colors[i]);
        asteroid_materials->push_back(asteroid_material);
    }

    AsteroidFactory::asteroid_materials = asteroid_materials;
    // AsteroidFactory::asteroid_materials = materials;

    AsteroidFactory::score_keeper = score_keeper;
}