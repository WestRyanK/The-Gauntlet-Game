#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Objects/ILight3D.h"
#include "CodeMonkeys/Engine/Objects/Camera3D.h"
#include "CodeMonkeys/Engine/Objects/Skybox.h"
#include "CodeMonkeys/Engine/Engine/DrawObjectsIterator.h"
#include "CodeMonkeys/Engine/Assets/ShaderProgram.h"

using namespace glm;

namespace CodeMonkeys::Engine::Engine
{
    class Renderer
    {
    private:
        DrawObjectsIterator draw_objects_iterator;
    protected:
        void clear();
        void set_lighting(set<ShaderProgram*> shaders, set<ILight3D*> lights);
        void set_camera(set<ShaderProgram*> shaders, Camera3D* camera);
        void draw_objects(Object3D* world_root);

        GLFWwindow* window;

    public:
        Renderer(GLFWwindow* window);
        void render(set<ShaderProgram*> shaders, set<ILight3D*> lights, Camera3D* camera, Object3D* world_root, Skybox* skybox);
    };
}