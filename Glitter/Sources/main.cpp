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

    TheGauntletWindow gauntlet_window = TheGauntletWindow(640, 480);
    TheGauntletEngine gauntlet_engine = TheGauntletEngine(gauntlet_window.get_window());

    gauntlet_engine.init();
    gauntlet_engine.run();

    // unsigned int VAO;
    // glGenVertexArrays(1, &VAO);
    // glBindVertexArray(VAO);

    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f,
    //      0.5f, -0.5f, 0.0f,
    //      0.0f,  0.5f, 0.0f
    // };

    // unsigned int VBO;
    // glGenBuffers(1, &VBO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
    // glBindVertexArray(0);

	// // **************************************
	// // Setup Vertex arrays here
	// // **************************************
	// // **************************************

    // CodeMonkeys::Engine::Assets::test1();
    // GLuint myShader = CodeMonkeys::Engine::Assets::LoadShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
	
    // // Rendering Loop
    // while (glfwWindowShouldClose(gauntlet_window.get_window()) == false) {
    //     if (glfwGetKey(gauntlet_window.get_window(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    //         glfwSetWindowShouldClose(mWindow, true);

    //     // Background Fill Color
    //     glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    //     glClear(GL_COLOR_BUFFER_BIT);

    //     glUseProgram(myShader);
    //     glBindVertexArray(VAO);
    //     glDrawArrays(GL_TRIANGLES, 0, 3);
        
	// 	// **********************************
	// 	// Add rendering code here

	// 	// **********************************

    //     // Flip Buffers and Draw
    //     glfwSwapBuffers(mWindow);
    //     glfwPollEvents();
    // }   
    // glfwTerminate();

    return EXIT_SUCCESS;
}
