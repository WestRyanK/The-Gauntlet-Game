#pragma once


namespace CodeMonkeys::TheGauntlet
{
    enum ShipSelection
    {
        SelectionXWingShip,
        SelectionJetFighter,
        SelectionCrayonBox
    };
    enum RendererSelection
    {
        SelectionFrameRenderer,
        Selection3DRenderer,
        SelectionRenderer
    };
    enum RetinaDisplaySelection
    {
        RetinaDisplay,
        NoRetinaDisplay
    };

    class TheGauntletEngineSettings
    {
    public:
        TheGauntletEngineSettings(ShipSelection ship_selection, RendererSelection renderer_selection, RetinaDisplaySelection retina_display);
        ShipSelection get_ship_selection();
        RendererSelection get_renderer_selection();
        RetinaDisplaySelection get_retina_display();
    private:
        ShipSelection ship_selection;
        RendererSelection renderer_selection;
        RetinaDisplaySelection retina_display;
    };
}