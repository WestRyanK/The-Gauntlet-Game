#pragma once

#include <set>
#include <GLFW/glfw3.h>
#include "glitter.hpp"
#include "CodeMonkeys/Engine/Assets/Model3D.h"

using namespace std;
using namespace glm;
using namespace CodeMonkeys::Engine::Assets;

namespace CodeMonkeys::Engine::Objects
{
    class Object3D
    {
    protected:
        Assets::Model3D* model;
        vec3 position;
        vec3 rotation;
        vec3 scale;
        set<Object3D*> children;
        Object3D* parent;
    public:
        Object3D(Model3D* model);

        vec3 get_position();
        void set_position(vec3 position);
        vec3 get_rotation();
        void set_rotation(vec3 rotation);
        vec3 get_scale();
        void set_scale(vec3 scale);
        void set_scale(float scale);
        mat4 get_transform();
        set<Object3D*> get_children();
        void add_child(Object3D* child);
        void remove_child(Object3D* child);
        Object3D* get_parent();
        void set_parent(Object3D* parent);

        virtual void update(float dt);
        virtual void draw(mat4 total_transform);
    };
}