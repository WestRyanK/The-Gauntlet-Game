#pragma once

#include "CodeMonkeys/TheGauntlet/GameObjects/Asteroid.h"
#include "CodeMonkeys/Engine/Assets/Texture.h"
#include <stdlib.h>
#include <vector>

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class AsteroidFactory
    {
    private:
        static float ratio_asteroids_large;
        static float ratio_asteroids_medium;
        static float ratio_asteroids_small;
        static vector<Material*> asteroid_materials;

        static float rand_centered(float center, float spread_radius);
        static float rand_min_max(float min, float max);
        static mlModel* load_asteroid_model(float scale);
        static void add_noise_to_model(mlModel* ml_model, int asteroid_size, int noise_iterations, bool is_jagged);
        static Model3D* create_asteroid_model(mlModel* ml_model);
    public:
        // Seed the random generator so that we can replay game.
        // Seed with 0 to use clock as seed.
        // Also load shaders and textures for asteroids.
        static void init_asteroid_factory(unsigned int seed, ShaderProgram* shader);
        static Asteroid* create_asteroid(int size);
        static Asteroid* create_asteroid_random_size();

        static void set_large_asteroids_ratio(float ratio);
        static void set_medium_asteroids_ratio(float ratio);
        static void set_small_asteroids_ratio(float ratio);
    };
}