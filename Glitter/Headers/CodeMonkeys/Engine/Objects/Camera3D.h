#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Objects/Object3D.h"

using namespace glm;

namespace CodeMonkeys::Engine::Objects
{
    class Camera3D : public Object3D
    {
    private:
        vec4 look_at;
        vec4 up = vec4(0.0f, 1.0f, 0.0f, 1.0f);

    public:
        Camera3D();
        vec4 get_look_at();
        void set_look_at(vec4 look_at);
        vec4 get_up();
        void set_up(vec4 up);

        void update_shader_with_camera(ShaderProgram shader);
    };
}