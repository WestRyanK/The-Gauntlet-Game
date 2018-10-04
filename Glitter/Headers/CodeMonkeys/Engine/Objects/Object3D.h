#pragma once

#include <set>
#include <GLFW/glfw3.h>
#include "glitter.hpp"
#include "Model3D.h"

using namespace glm;
using namespace std;
namespace CodeMonkeys::TheGauntlet::Engine::Objects
{
    class Object3D
    {
    private:
        Model3D* model;
        vec3: position;
        vec3: rotation;
        vec3: scale;
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
        // Gets the transform matrix combining Object3D's position, rotation, and scale.
        mat4 get_own_transform();
        // Gets the transform matrix inherited from its parents.
        mat4 get_parent_transform();
        set<Object3D*> get_children();
        void add_child(Object3D* child);
        void remove_child(Object3D* child);
        Object3D* get_parent();
        void set_parent(Object3D* parent);

        virtual void update();
        virtual void draw();
    };
}