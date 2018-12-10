#pragma once

#include <chrono>

namespace CodeMonkeys::Engine::Engine
{
    class Stopwatch
    {
    private:
        std::chrono::high_resolution_clock::time_point t1;
    public:
        float get_seconds_from_last_measurement();
    };
}