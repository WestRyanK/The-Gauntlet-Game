#include "CodeMonkeys/TheGauntlet/TheGauntletEngine.h"

using CodeMonkeys::TheGauntlet::TheGauntletEngineSettings;
using namespace CodeMonkeys::TheGauntlet;

TheGauntletEngineSettings::TheGauntletEngineSettings(ShipSelection ship_selection, RendererSelection renderer_selection, RetinaDisplaySelection retina_display)
{
    this->ship_selection = ship_selection;
    this->renderer_selection = renderer_selection;
    this->retina_display = retina_display;
}

ShipSelection TheGauntletEngineSettings::get_ship_selection()
{
    return this->ship_selection;
}

RendererSelection TheGauntletEngineSettings::get_renderer_selection()
{
    return this->renderer_selection;
}

RetinaDisplaySelection TheGauntletEngineSettings::get_retina_display()
{
    return this->retina_display;
}