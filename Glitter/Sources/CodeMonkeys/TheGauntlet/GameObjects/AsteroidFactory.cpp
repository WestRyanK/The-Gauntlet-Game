#include "CodeMonkeys/TheGauntlet/GameObjects/AsteroidFactory.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Asteroid.h"
#include "CodeMonkeys/Engine/Assets/LoopSubdivider.h"
#include <time.h>
#include <iostream>
#include <stdlib.h>

using CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory;
using namespace CodeMonkeys::TheGauntlet::GameObjects;

float AsteroidFactory::ratio_asteroids_large = 1;
float AsteroidFactory::ratio_asteroids_medium = 1;
float AsteroidFactory::ratio_asteroids_small = 1;
vector<Texture*> AsteroidFactory::asteroid_textures = vector<Texture*>();
vector<ShaderProgram> AsteroidFactory::asteroid_shaders = vector<ShaderProgram>();

Asteroid* AsteroidFactory::create_asteroid(int size)
{
    unsigned int health = 0;
    if (size == Asteroid::SMALL)
    {
        health = Asteroid::SMALL_HEALTH;
    } else if (size == Asteroid::MEDIUM)
    {
        health = Asteroid::MEDIUM_HEALTH;
    } 
    else 
    {
        health = Asteroid::SMALL_HEALTH;
    }

    mlModel* ml_model = AsteroidFactory::load_asteroid_model(size);
    AsteroidFactory::add_noise_to_model(ml_model, size , 2, true);
    Model3D* model = AsteroidFactory::create_asteroid_model(ml_model);

    Asteroid* asteroid = new Asteroid(model, size, health);

    return asteroid;
}

mlModel* AsteroidFactory::load_asteroid_model(float scale)
{
    float one_over_sqrt_2 = 1/sqrt(2.0);

    // Geometric definition of a tetrahedron.
    // mlMesh* mesh = new mlMesh();
    // vector<mlVertex> vertices;
    // mlVertex a;
    // a.position = vec3(scale * 1.0f, 0.0f, scale * -one_over_sqrt_2);
    // vertices.push_back(a);
    // mlVertex b;
    // b.position = vec3(scale * -1.0f, 0.0f, scale * -one_over_sqrt_2);
    // vertices.push_back(b);
    // mlVertex c;
    // c.position = vec3(0.0f, scale * 1.0f, scale * one_over_sqrt_2);
    // vertices.push_back(c);
    // mlVertex d;
    // d.position = vec3(0.0f, scale * -1.0f, scale * one_over_sqrt_2);
    // vertices.push_back(d);
    // vector<unsigned int> indices = { 0, 1, 2, 1, 2, 3, 0, 2, 3, 0, 1, 3 };
    // mesh->vertices = vertices;
    // mesh->indices = indices;


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
                // float stretch_factor = AsteroidFactory::rand_min_max(0.75, 1.25f);

                // Add noise
                for (int vertex_index = 0; vertex_index < ml_model->meshes[mesh_index]->vertices.size(); vertex_index++)
                {
                    float position = ml_model->meshes[mesh_index]->vertices[vertex_index].position[axis];
                    // position *= stretch_factor;
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
    Model3D* model = new Model3D(ml_model, AsteroidFactory::asteroid_textures, AsteroidFactory::asteroid_shaders);
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

void AsteroidFactory::init_asteroid_factory(unsigned int seed, vector<ShaderProgram> asteroid_shaders, vector<Texture*> asteroid_textures)
{
    if (seed == 0)
    {
        srand(time(NULL));
    }
    else
    {
        srand(seed);
    }

    AsteroidFactory::asteroid_shaders = asteroid_shaders;
    AsteroidFactory::asteroid_textures = asteroid_textures;
}