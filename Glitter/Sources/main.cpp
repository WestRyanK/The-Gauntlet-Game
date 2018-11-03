// Local Headers
#define STB_IMAGE_IMPLEMENTATION
#include "glitter.hpp"
// #include "CodeMonkeys/Engine/Assets/ShaderHelpers.h"
// #include "CodeMonkeys/Engine/Assets/ModelLoader.h"
#include "CodeMonkeys/TheGauntlet/TheGauntletWindow.h"
#include "CodeMonkeys/TheGauntlet/TheGauntletEngine.h"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

using namespace CodeMonkeys::TheGauntlet;

int main(int argc, char * argv[]) {

    const GLuint WIDTH = 1920;
    const GLuint HEIGHT = 720;
    TheGauntletWindow gauntlet_window = TheGauntletWindow(WIDTH, HEIGHT);
    TheGauntletEngine gauntlet_engine = TheGauntletEngine(gauntlet_window.get_window(), WIDTH, HEIGHT);

    gauntlet_engine.init();
    gauntlet_engine.run();
    return EXIT_SUCCESS;
}
