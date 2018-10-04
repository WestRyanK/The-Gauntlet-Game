#pragma once


namespace CodeMonkeys::TheGauntlet::Engine::Objects
{
    class ILight3D
    {
    public:
        virtual void add_light_to_shader(ShaderProgram shader_program) = 0;
    };
}
