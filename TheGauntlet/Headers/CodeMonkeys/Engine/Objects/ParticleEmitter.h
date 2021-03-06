#pragma once

#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
namespace CodeMonkeys::Engine::Objects { class Particle; }


namespace CodeMonkeys::Engine::Objects
{
    class ParticleEmitter : public PhysicalObject3D
    {
    private:
        bool is_emitting = false;
        Particle* particle_prototype;
    public:
        ParticleEmitter(string name);
        void start();
        void stop();
        void cancel();
        void kill_particle(Particle* particle);
        void update(float dt);
        virtual void emit(float dt);
        void emit(Particle* particle_to_emit);
        void set_particle(Particle* particle_prototype);
    };
}