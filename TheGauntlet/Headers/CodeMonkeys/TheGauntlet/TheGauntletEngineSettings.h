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
    enum DifficultyLevel
    {
        EasyDifficulty,
        MediumDifficulty,
        HardDifficulty
    };

    class TheGauntletEngineSettings
    {
    public:
        TheGauntletEngineSettings(ShipSelection ship_selection,
                                  RendererSelection renderer_selection,
                                  RetinaDisplaySelection retina_display,
                                  bool fullscreen,
                                  DifficultyLevel difficulty);
        ShipSelection get_ship_selection();
        RendererSelection get_renderer_selection();
        RetinaDisplaySelection get_retina_display();
        bool get_fullscreen();
        DifficultyLevel get_difficulty();
    private:
        ShipSelection ship_selection;
        RendererSelection renderer_selection;
        RetinaDisplaySelection retina_display;
        bool fullscreen;
        DifficultyLevel difficulty;
    };
}