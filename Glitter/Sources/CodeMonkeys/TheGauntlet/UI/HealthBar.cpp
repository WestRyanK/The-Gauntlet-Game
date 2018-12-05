#include "CodeMonkeys/TheGauntlet/UI/HealthBar.h"

using CodeMonkeys::TheGauntlet::HealthBar;

HealthBar::HealthBar(IDamageable* measured_damageable, float x, float y, float width, float height) 
    : ProgressBar(new AnimatedTexture("Assets/UI/HealthBar/health_bar2", "png", 13),x, y, width, height)
{
    this->measured_damageable = measured_damageable;
}

void HealthBar::update(float dt)
{
    ProgressBar::update(this->measured_damageable->get_health(), this->measured_damageable->get_max_health(), true);
}