// Local Headers
#define STB_IMAGE_IMPLEMENTATION
#include "glitter.hpp"
// #include "CodeMonkeys/Engine/Assets/ShaderHelpers.h"
// #include "CodeMonkeys/Engine/Assets/ModelLoader.h"
#include "CodeMonkeys/TheGauntlet/TheGauntletWindow.h"
#include "CodeMonkeys/TheGauntlet/TheGauntletEngine.h"
#include "CodeMonkeys/TheGauntlet/TheGauntletEngineSettings.h"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <set>
#include <string>

using namespace CodeMonkeys::TheGauntlet;
using namespace std;


TheGauntletEngineSettings* parse_settings(int argc, char * argv[])
{
    set<string> args;
    for (int i = 0; i < argc; i++)
    {
        string str(argv[i]);
        args.insert(str);
    }
    TheGauntletEngineSettings* settings = NULL;
    ShipSelection ship_selection = ShipSelection::SelectionJetFighter;
    RendererSelection renderer_selection = RendererSelection::SelectionFrameRenderer;
    RetinaDisplaySelection retina_display = RetinaDisplaySelection::NoRetinaDisplay;
    bool fullscreen = false;
    if (args.count("xwing") > 0)
        ship_selection = ShipSelection::SelectionXWingShip;
    else if (args.count("box") > 0)
        ship_selection = ShipSelection::SelectionCrayonBox;
    else
        ship_selection = ShipSelection::SelectionJetFighter;

    if (args.count("frame") > 0)
        renderer_selection = RendererSelection::SelectionFrameRenderer;
    else if (args.count("3d") > 0)
        renderer_selection = RendererSelection::Selection3DRenderer;
    else
        renderer_selection = RendererSelection::SelectionRenderer;

    if (args.count("retina") > 0)
        retina_display = RetinaDisplaySelection::RetinaDisplay;
    else
        retina_display = RetinaDisplaySelection::NoRetinaDisplay;

    if (args.count("fullscreen") > 0)
        fullscreen = true;

    settings = new TheGauntletEngineSettings(ship_selection, renderer_selection, retina_display, fullscreen);
    
    return settings;
}

int main(int argc, char * argv[]) {
    auto settings = parse_settings(argc, argv);

    const float virtual_reality_ratio = 0.375f;
    const float normal_ratio = 0.7;
    //const GLuint WIDTH = 1920;
    GLuint WIDTH = 1080;
    GLuint HEIGHT = 0;
    if (settings->get_renderer_selection() == RendererSelection::Selection3DRenderer)
        HEIGHT = (int)(WIDTH * virtual_reality_ratio);
    else
        HEIGHT = (int)(WIDTH * normal_ratio);

    if (settings->get_retina_display() == RetinaDisplaySelection::RetinaDisplay)
    {
        HEIGHT *= 2;
        WIDTH *= 2;
    }

    TheGauntletWindow gauntlet_window = TheGauntletWindow(WIDTH, HEIGHT, settings->get_fullscreen());
    TheGauntletEngine gauntlet_engine = TheGauntletEngine(gauntlet_window.get_window(), WIDTH, HEIGHT, settings);
    // TheGauntletEngine gauntlet_engine = TheGauntletEngine(gauntlet_window.get_window(), WIDTH, HEIGHT);

    gauntlet_engine.init();
    gauntlet_engine.run();
    return EXIT_SUCCESS;
}
