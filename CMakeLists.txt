cmake_minimum_required(VERSION 3.15.0)
project(breakout LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(breakout
				src/main.cpp
				src/glad.c
				src/Breakout.cpp
				src/Window.cpp 
				src/Renderer.cpp 
				src/Texture.cpp 
				src/stb_image.cpp 
				src/GameLevel.cpp) 

target_link_libraries(breakout ${GLFW3_LIBRARY} OpenGL::GL)

target_include_directories(breakout PRIVATE include vendor)
