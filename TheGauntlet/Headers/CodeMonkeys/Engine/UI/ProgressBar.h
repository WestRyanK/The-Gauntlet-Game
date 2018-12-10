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
        ProgressBar(AnimatedTexture* texture, vec2 position, vec2 size);
        virtual void update(float dt);
    };
}