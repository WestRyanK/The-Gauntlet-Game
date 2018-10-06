#include "CodeMonkeys/Engine/Control/Controller.h"

using CodeMonkeys::Engine::Control::Controller;

Controller::Controller(IControllable* controllable)
{
    this->controllable = controllable;
}