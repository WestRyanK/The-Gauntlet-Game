#include "CodeMonkeys/TheGauntlet/GameObjects/AsteroidFactory.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Asteroid.h"
#include <time.h>
#include <stdlib.h>

using CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory;
using namespace CodeMonkeys::TheGauntlet::GameObjects;

float AsteroidFactory::ratio_asteroids_large = 1;
float AsteroidFactory::ratio_asteroids_medium = 1;
float AsteroidFactory::ratio_asteroids_small = 1;
vector<Texture*> AsteroidFactory::textures = vector<Texture*>();
vector<ShaderProgram> AsteroidFactory::shaders = vector<ShaderProgram>();

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

    mlModel* ml_model = AsteroidFactory::load_asteroid_model();
    AsteroidFactory::add_noise_to_model(ml_model);
    Model3D* model = AsteroidFactory::create_asteroid_model(ml_model);

    Asteroid* asteroid = new Asteroid(model, size, health);
}

mlModel* AsteroidFactory::load_asteroid_model()
{
    mlModel* ml_model = new mlModel();
    LoadModel("Assets", "Asteroid.ob", *ml_model);

    return ml_model;
}

void AsteroidFactory::add_noise_to_model(mlModel* ml_model)
{
    float MAX_STRETCH = 0.25f;
    float MAX_NOISE = 0.5f;

    for (mlMesh asteroid_mesh : ml_model->meshes)
    {
        // Mutate along axis.
        for (int axis = 0; axis < 3; axis++)
        {
            float stretch_factor = AsteroidFactory::rand_centered(1.0f, MAX_STRETCH);

            for (mlVertex asteroid_vertex : asteroid_mesh.vertices)
            {
                float position = asteroid_vertex.position[axis];
                position *= stretch_factor;
                position += AsteroidFactory::rand_centered(0.0f, MAX_NOISE);
            }
        }
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

    float random_value = (rand() % RESOLUTION) / RESOLUTION;
    random_value *= range;
    random_value += min;

    return random_value;
}

Model3D* AsteroidFactory::create_asteroid_model(mlModel* ml_model)
{
    Model3D* model = new Model3D(ml_model, AsteroidFactory::textures, AsteroidFactory::shaders);
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

void AsteroidFactory::init_asteroid_factory(unsigned int seed)
{
    if (seed == 0)
    {
        srand(time(NULL));
    }
    else
    {
        srand(seed);
    }
}