#include "CodeMonkeys/TheGauntlet/TheGauntletEngine.h"
#include "CodeMonkeys/TheGauntlet/Control/KeyboardController.h"
#include "CodeMonkeys/TheGauntlet/Control/MouseController.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/ShipFactory.h"

using CodeMonkeys::TheGauntlet::TheGauntletEngine;

TheGauntletEngine::TheGauntletEngine(GLFWwindow* window) : GameEngine(window)
{
}

void TheGauntletEngine::update_frame(float dt)
{
    this->handle_controllers(dt);
    this->update_objects(dt);
    this->handle_collisions(dt);
    this->draw();
}

void TheGauntletEngine::init()
{
    auto ship = CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::create_x_wing_ship();
    auto keyboard_controller = new CodeMonkeys::TheGauntlet::Control::KeyboardController(ship, this->get_window());
    auto mouse_controller = new CodeMonkeys::TheGauntlet::Control::MouseController(ship, this->get_window());
    this->world_root->add_child(ship);
}