#include "CodeMonkeys/Engine/Collision/ICollisionResponse.h"

using CodeMonkeys::Engine::Collision::ICollisionResponse;

ICollisionResponse::ICollisionResponse(CodeMonkeys::Engine::Engine::GameEngine* engine)
{
    this->engine = engine;
}