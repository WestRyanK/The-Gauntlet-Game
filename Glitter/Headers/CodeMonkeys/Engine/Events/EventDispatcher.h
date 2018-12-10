#pragma once

#include <map>
#include <queue>
#include <string>
#include <functional>

namespace CodeMonkeys::Engine::Events
{
    // EventDispatcher is a general purpose globally available singleton
    class EventDispatcher
    {
    private:
        std::map<std::string, std::function<void()>> event_handlers;
        std::queue<std::string> event_queue;

        EventDispatcher() = default;

    public:
        static EventDispatcher& get_instance()
        {
            static EventDispatcher instance;
            return instance;
        }

        // delete these methods to prevent copies of the singleton from appearing
        EventDispatcher(EventDispatcher const&) = delete;
        void operator=(EventDispatcher const&) = delete;

        void register_event(std::string, std::function<void()>);
        void report_event(std::string);
        void dispatch();
    };
}