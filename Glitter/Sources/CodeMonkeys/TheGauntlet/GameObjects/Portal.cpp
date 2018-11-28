#include "CodeMonkeys/TheGauntlet/GameObjects/Portal.h"
#include <string>
#include <Portal.h>
#include "NIE.h"

using CodeMonkeys::TheGauntlet::GameObjects::Portal;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::TheGauntlet::GameObjects;

Portal::Portal(Model3D* model) : PhysicalObject3D(model, "portal")
{
    this->set_scale(3.0f);
}