#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Objects/Object3D.h"
#include "CodeMonkeys/Engine/Control/IControllable.h"

using namespace CodeMonkeys::Engine::Control;
using namespace glm;

namespace CodeMonkeys::Engine::Objects
{
    class Camera3D : public Object3D, public IControllable
    {
    private:
        vec3 look_at;
        vec3 up = vec4(0.0f, 1.0f, 0.0f, 1.0f);
        mat4 perspective_projection;

    public:
        Camera3D();
        vec3 get_look_at();
        void set_look_at(vec3 look_at);
        vec3 get_up();
        void set_up(vec3 up);

        void update_shader_with_camera(ShaderProgram* shader);

        void control(std::string control_name, float value, float dt);
        void control(std::string control_name, int value, float dt);
    };
}