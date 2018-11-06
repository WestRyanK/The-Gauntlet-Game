#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Objects/ILight3D.h"
#include "CodeMonkeys/Engine/Objects/Camera3D.h"
#include "CodeMonkeys/Engine/Objects/Skybox.h"
#include "CodeMonkeys/Engine/Engine/DrawObjectsIterator.h"
#include "CodeMonkeys/Engine/Assets/ShaderProgram.h"

#include "CodeMonkeys/Engine/Assets/Texture.h"

using namespace glm;

namespace CodeMonkeys::Engine::Engine
{
    class Renderer
    {
    private:
        DrawObjectsIterator draw_objects_iterator;
        GLuint width;
        GLuint height;
        GLFWwindow* window;

    protected:
        GLuint get_width();
        GLuint get_height();
        // void set_width(GLuint width);
        // void set_height(GLuint height);
        GLFWwindow* get_window();


        void clear();
        void set_lighting(ShaderProgram* shader, set<ILight3D*> lights);
        void set_camera(ShaderProgram* shader, Camera3D* camera);
        void draw_objects(Object3D* world_root, ShaderProgram* shader);

    public:
        Renderer(GLFWwindow* window, GLuint width, GLuint height);
        virtual void render(set<ShaderProgram*> shaders, set<ILight3D*> lights, Camera3D* camera, Object3D* world_root, Skybox* skybox);
    };
}