cmake_minimum_required(VERSION 3.0)
project(Glitter)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -w")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -w")

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(Glitter/Vendor/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(Glitter/Vendor/assimp)

option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
add_subdirectory(Glitter/Vendor/bullet)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(Glitter/Headers/
                    Glitter/Headers/CodeMonkeys/Engine/Assets/
                    Glitter/Headers/CodeMonkeys/Engine/Collision/
                    Glitter/Headers/CodeMonkeys/Engine/Control/
                    Glitter/Headers/CodeMonkeys/Engine/Engine/
                    Glitter/Headers/CodeMonkeys/Engine/Objects/
                    Glitter/Headers/CodeMonkeys/TheGauntlet/
                    Glitter/Headers/CodeMonkeys/TheGauntlet/Control/
                    Glitter/Headers/CodeMonkeys/TheGauntlet/GameObjects/
                    Glitter/Headers/CodeMonkeys/TheGauntlet/Weapons/
                    Glitter/Headers/CodeMonkeys/TheGauntlet/Collision/
                    Glitter/Vendor/assimp/include/
                    Glitter/Vendor/bullet/src/
                    Glitter/Vendor/glad/include/
                    Glitter/Vendor/glfw/include/
                    Glitter/Vendor/glm/
                    Glitter/Vendor/stb/)

file(GLOB VENDORS_SOURCES Glitter/Vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS Glitter/Headers/*.hpp
                          Glitter/Headers/*.h
                          Glitter/Headers/CodeMonkeys/Engine/Assets/*.h
                          Glitter/Headers/CodeMonkeys/Engine/Collision/*.h
                          Glitter/Headers/CodeMonkeys/Engine/Control/*.h
                          Glitter/Headers/CodeMonkeys/Engine/Engine/*.h
                          Glitter/Headers/CodeMonkeys/Engine/Objects/*.h
                          Glitter/Headers/CodeMonkeys/TheGauntlet/*.h
                          Glitter/Headers/CodeMonkeys/TheGauntlet/Control/*.h
                          Glitter/Headers/CodeMonkeys/TheGauntlet/GameObjects/*.h
                          Glitter/Headers/CodeMonkeys/TheGauntlet/Weapons/*.h
                          Glitter/Headers/CodeMonkeys/TheGauntlet/Collision/*.h
                          )
file(GLOB PROJECT_SOURCES Glitter/Sources/*.cpp
                          Glitter/Sources/CodeMonkeys/Engine/Assets/*.cpp
                          Glitter/Sources/CodeMonkeys/Engine/Collision/*.cpp
                          Glitter/Sources/CodeMonkeys/Engine/Control/*.cpp
                          Glitter/Sources/CodeMonkeys/Engine/Engine/*.cpp
                          Glitter/Sources/CodeMonkeys/Engine/Objects/*.cpp
                          Glitter/Sources/CodeMonkeys/TheGauntlet/*.cpp
                          Glitter/Sources/CodeMonkeys/TheGauntlet/Control/*.cpp
                          Glitter/Sources/CodeMonkeys/TheGauntlet/GameObjects/*.cpp
                          Glitter/Sources/CodeMonkeys/TheGauntlet/Weapons/*.cpp
                          Glitter/Sources/CodeMonkeys/TheGauntlet/Collision/*.cpp
)
file(GLOB PROJECT_SHADERS Glitter/Assets/Shaders/*.comp
                          Glitter/Assets/Shaders/*.frag
                          Glitter/Assets/Shaders/*.geom
                          Glitter/Assets/Shaders/*.vert)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES} )
target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      BulletDynamics BulletCollision LinearMath)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
                       
add_custom_command(TARGET Glitter PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Glitter/Assets $<TARGET_FILE_DIR:Glitter>/Assets)