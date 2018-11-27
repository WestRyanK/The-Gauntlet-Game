#pragma once

#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h";
namespace CodeMonkeys::Engine::Objects { class Particle; }


namespace CodeMonkeys::Engine::Objects
{
    class ParticleEmitter : public PhysicalObject3D
    {
    private:
        bool is_emitting = false;
        void emit(Particle* particle_to_emit);
        Particle* particle_prototype;
    public:
        ParticleEmitter(string name, Particle* particle_prototype);
        void start();
        void stop();
        void cancel();
        void kill_particle(Particle* particle);
        void update(float dt);
        virtual void emit(float dt);
    };
}