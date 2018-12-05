#include "CodeMonkeys/TheGauntlet/Healthbar.h"

using CodeMonkeys::TheGauntlet::Healthbar;

Healthbar::Healthbar(IDamageable* measured_damageable, float x, float y, float width, float height) : Quad(x, y, width, height)
{
    this->measured_damageable = measured_damageable;
    this->healthbar_texture = new AnimatedTexture("Assets/Healthbar/healthbar", "png", 13);
    this->set_texture(this->healthbar_texture->get_texture_id());
}

void Healthbar::update(float dt)
{
    float percent_health = this->measured_damageable->get_health() / (float)this->measured_damageable->get_max_health();
    int frame = this->healthbar_texture->get_frame_count() - (percent_health * this->healthbar_texture->get_frame_count());
    this->healthbar_texture->set_current_frame(frame);
    this->set_texture(this->healthbar_texture->get_texture_id());
}