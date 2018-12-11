cmake_minimum_required(VERSION 3.0)
project(TheGauntlet)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -w")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -w")

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(TheGauntlet/Vendor/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(TheGauntlet/Vendor/assimp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(TheGauntlet/Headers/
                    TheGauntlet/Headers/CodeMonkeys/Engine/Assets/
                    TheGauntlet/Headers/CodeMonkeys/Engine/Collision/
                    TheGauntlet/Headers/CodeMonkeys/Engine/Control/
                    TheGauntlet/Headers/CodeMonkeys/Engine/Engine/
                    TheGauntlet/Headers/CodeMonkeys/Engine/Events/
                    TheGauntlet/Headers/CodeMonkeys/Engine/Objects/
                    TheGauntlet/Headers/CodeMonkeys/Engine/UI/
                    TheGauntlet/Headers/CodeMonkeys/TheGauntlet/
                    TheGauntlet/Headers/CodeMonkeys/TheGauntlet/Control/
                    TheGauntlet/Headers/CodeMonkeys/TheGauntlet/GameObjects/
                    TheGauntlet/Headers/CodeMonkeys/TheGauntlet/Weapons/
                    TheGauntlet/Headers/CodeMonkeys/TheGauntlet/UI/
                    TheGauntlet/Headers/CodeMonkeys/TheGauntlet/Collision/
                    TheGauntlet/Vendor/assimp/include/
                    TheGauntlet/Vendor/glad/include/
                    TheGauntlet/Vendor/glfw/include/
                    TheGauntlet/Vendor/glm/
                    TheGauntlet/Vendor/stb/)

file(GLOB VENDORS_SOURCES TheGauntlet/Vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS TheGauntlet/Headers/*.hpp
                          TheGauntlet/Headers/*.h
                          TheGauntlet/Headers/CodeMonkeys/Engine/Assets/*.h
                          TheGauntlet/Headers/CodeMonkeys/Engine/Collision/*.h
                          TheGauntlet/Headers/CodeMonkeys/Engine/Control/*.h
                          TheGauntlet/Headers/CodeMonkeys/Engine/Engine/*.h
                          TheGauntlet/Headers/CodeMonkeys/Engine/Events/*.h
                          TheGauntlet/Headers/CodeMonkeys/Engine/Objects/*.h
                          TheGauntlet/Headers/CodeMonkeys/Engine/UI/*.h
                          TheGauntlet/Headers/CodeMonkeys/TheGauntlet/*.h
                          TheGauntlet/Headers/CodeMonkeys/TheGauntlet/Control/*.h
                          TheGauntlet/Headers/CodeMonkeys/TheGauntlet/GameObjects/*.h
                          TheGauntlet/Headers/CodeMonkeys/TheGauntlet/Weapons/*.h
                          TheGauntlet/Headers/CodeMonkeys/TheGauntlet/UI/*.h
                          TheGauntlet/Headers/CodeMonkeys/TheGauntlet/Collision/*.h
                          )
file(GLOB PROJECT_SOURCES TheGauntlet/Sources/*.cpp
                          TheGauntlet/Sources/CodeMonkeys/Engine/Assets/*.cpp
                          TheGauntlet/Sources/CodeMonkeys/Engine/Collision/*.cpp
                          TheGauntlet/Sources/CodeMonkeys/Engine/Control/*.cpp
                          TheGauntlet/Sources/CodeMonkeys/Engine/Engine/*.cpp
                          TheGauntlet/Sources/CodeMonkeys/Engine/Events/*.cpp
                          TheGauntlet/Sources/CodeMonkeys/Engine/Objects/*.cpp
                          TheGauntlet/Sources/CodeMonkeys/Engine/UI/*.cpp
                          TheGauntlet/Sources/CodeMonkeys/TheGauntlet/*.cpp
                          TheGauntlet/Sources/CodeMonkeys/TheGauntlet/Control/*.cpp
                          TheGauntlet/Sources/CodeMonkeys/TheGauntlet/GameObjects/*.cpp
                          TheGauntlet/Sources/CodeMonkeys/TheGauntlet/Weapons/*.cpp
                          TheGauntlet/Sources/CodeMonkeys/TheGauntlet/UI/*.cpp
                          TheGauntlet/Sources/CodeMonkeys/TheGauntlet/Collision/*.cpp
)
file(GLOB PROJECT_SHADERS TheGauntlet/Assets/Shaders/*.comp
                          TheGauntlet/Assets/Shaders/*.frag
                          TheGauntlet/Assets/Shaders/*.geom
                          TheGauntlet/Assets/Shaders/*.vert)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/TheGauntlet" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED audio)
  include_directories(${SFML_INCLUDE_DIR})



add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES} )
target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
                       
add_custom_command(TARGET TheGauntlet PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/TheGauntlet/Assets $<TARGET_FILE_DIR:TheGauntlet>/Assets)