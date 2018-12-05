#pragma once

#include "CodeMonkeys/Engine/Engine/Quad.h"
#include "CodeMonkeys/Engine/Assets/AnimatedTexture.h"

using namespace CodeMonkeys::Engine::Engine;
using namespace CodeMonkeys::Engine::Assets;

namespace CodeMonkeys::Engine::UI
{
    class ProgressBar : public Quad
    {
    protected:
        AnimatedTexture* texture = NULL;
        void update(float current_value, float total, bool reverse);
    public:
        ProgressBar(AnimatedTexture* texture, float x, float y, float width, float height);
        virtual void update(float dt);
    };
}