#pragma once

#include "CodeMonkeys/Engine/Objects/Billboard.h"
#include "CodeMonkeys/Engine/Objects/Camera3D.h"

using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::TheGauntlet::Weapons
{
    class Crosshairs : public Billboard
    {
    private:
        float distance = 40;
        float speed = 2;
        vec2 boundary = vec2(15);
        Camera3D* camera = NULL;
        void update_crosshairs();
    public:
        Crosshairs(Texture* texture);
        void set_speed(float speed);
        void set_distance(float distance);
        void set_boundary(vec2 boundary);
        float get_speed();
        float get_distance();
        vec2 get_boundary();
        void set_camera(Camera3D* camera);
        
        void set_crosshairs_x(float aim_x);
        void set_crosshairs_y(float aim_y);
        void move_crosshairs_x(float delta_x);
        void move_crosshairs_y(float delta_y);

        vec3 get_aim_vector();
    };
}