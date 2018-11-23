#include "CodeMonkeys/Engine/Objects/SpringArm.h"

using CodeMonkeys::Engine::Objects::SpringArm;

mat4 SpringArm::get_transform()
{
    // mat4 transform = glm::lookAt(this->arm_connector_position, this->parent->get_position(), vec3(0.0f, 1.0f, 0.0f));
    mat4 transform;
    transform = glm::translate(transform, this->arm_connector_position );
    return transform;
}

void SpringArm::update(float dt)
{

    PhysicalObject3D* physical_parent = dynamic_cast<PhysicalObject3D*>(this->parent);
    if (physical_parent != NULL)
    {
        this->acceleration = physical_parent->get_acceleration();
        vec3 adjusted_velocity = physical_parent->get_velocity();
        adjusted_velocity.z = -100;
        vec3 arm_unstretched_position = -this->arm_length * glm::normalize(adjusted_velocity);
        // vec3 arm_unstretched_position = -this->arm_length * glm::normalize(physical_parent->get_velocity()) - (physical_parent->get_velocity() * 0.025f * this->arm_length);

        // f = m * a
        // f = k * x
        // m * a = k * x
        // m * a / k = x
        vec3 stretch = this->arm_connector_mass * this->acceleration / this->spring_constant;
        // printf("Acc: %f, %f, %f\n", this->acceleration.x, this->acceleration.y, this->acceleration.z);
        // printf("Arm: %f, %f, %f\n", arm_unstretched_position.x, arm_unstretched_position.y, arm_unstretched_position.z);
        this->arm_connector_position = arm_unstretched_position;
        this->arm_connector_position.y = 300;
        // this->arm_connector_position = arm_unstretched_position - stretch;
    }
}

SpringArm::SpringArm(float arm_length, float spring_constant, float arm_connector_mass) : PhysicalObject3D(NULL, "SpringArm")
{
    this->arm_length = arm_length;
    this->spring_constant = spring_constant;
    this->arm_connector_mass = arm_connector_mass;
}