cmake_minimum_required(VERSION 3.20)

project(murph)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(murph
    src/main.cpp
    src/Application.cpp
    src/Renderer.cpp
    src/Shader.cpp
)

target_link_libraries(murph PRIVATE glfw glad::glad OpenGL::GL)