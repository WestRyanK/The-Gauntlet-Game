#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Engine/Stopwatch.h"

using namespace CodeMonkeys::Engine::Engine;

namespace CodeMonkeys::TheGauntlet::Weapons
{
    /**
     * Provides an interface for firing weapons that need a recharge period.
     * The user can call pull_trigger() as often as they want, but the IFireable will only
     * ever call on_fire() (to actually shoot something) if at least 'recharge_delay'
     * amount of time has passed.
     * 
     * Also, some weapons don't allow automatic firing if the trigger is held down, so
     * it provides a mechanism for ensuring the user presses the button each time to shoot
     * instead of holding it down. If 'is_automatic_fire' is set to true.
     * 
     * When a controller senses a button is held down, it should call pull_trigger()
     * on the IFireable and when it senses it is released, it should call release_trigger()
     * so that automatic and non-automatic firing works.
     */
    class ITriggerable
    {
    private:
        // The amount of time it takes to recharge the weapon, measured in seconds. 
        // Even if the weapon doesn't "recharge", this should be set to some small
        // number so that the user doesn't fire a bajillion rounds per second.
        float recharge_delay;
        // If true, the user must release the button between shots instead of holding
        // it down to rapid fire. See class comments for how to implement.
        bool is_automatic_fire;
        // If the controller has indicated that the user released the fire button, this is true.
        bool was_trigger_held;
        // The amount of time that has elapsed since the last shot was fired.
        float recharge_time_elapsed;
        Stopwatch recharge_timer;
        void update_recharge_time();
    protected:
        // This is called when the weapon actually fires.
        // I think there is enough documentation in the rest
        // of the class to explain what it does.
        virtual void on_fire() = 0;
        // This is called when a call to pull_trigger() does not
        // generate a call to on_fire(). You probably don't need
        // to overload or do anything special with it unless you
        // want to play some 'gun click' type sound effect.
        virtual void on_misfire();


    public:
        ITriggerable(float recharge_delay, bool is_automatic_fire);
        // This method is called when the user presses the fire button.
        // However, nothing is actually fired unless 'recharge_delay' 
        // amount of time has passed and the conditions of 'is_automatic_fire'
        // are met. When conditions are met, on_fire() is called.
        void pull_trigger();
        // This method os called when the controller detects that the
        // fire button has been released. If the weapon is not an automatic
        // weapon, this must be called by the controller to work. If it
        // is an automatic weapon, you can ignore this.
        void release_trigger();
        // Returns the minimum amount of time that the user
        // must wait before a call to pull_trigger() generates
        // an on_fire() call.
        float get_recharge_delay();
        // Returns the amount of time remaining before a call
        // to pull_trigger() will generate an on_fire() call.
        // This is useful if we want to somehow display
        // a weapon loading/charging animation of some sort.
        float get_recharge_time_remaining();
    };
}