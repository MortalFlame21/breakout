#include "Breakout.h"
#include "ResourceManager.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

Breakout::Breakout() {
    // shaders
    ResourceManager::loadShader("default", ShaderProgram{});  

    // textures
    Texture::setup();
    ResourceManager::loadTexture("ball", Texture{"resources/textures/ball.png"});
    ResourceManager::loadTexture("paddle", Texture{"resources/textures/paddle.png"});
    ResourceManager::loadTexture("background", Texture{"resources/textures/background.png"});
    for (int i{}; i < Texture::TILE_TEXTURE_SIZE; ++i) {
        const auto name{"tile" + std::to_string(i)};
        ResourceManager::loadTexture(name, Texture{"resources/textures/" + name + ".png"});
    }

    // game levels
    _levels.emplace_back("resources/levels/level1.lvl");
}

void Breakout::run() {
    float deltaTime{};
    float prevTime{};
    
    ResourceManager::getShader("default").use();
    ResourceManager::getShader("default").setUniformM("uProjection", 1, GL_FALSE, glm::ortho(0.f, 800.f, 800.f, 0.f, -1.f, 1.f));

    while (_window.running()) {
        auto currTime{static_cast<float>(glfwGetTime())};
        deltaTime = currTime - prevTime;
        prevTime = currTime;

        update(deltaTime);
        render(deltaTime);
        poll();
    }
}

void Breakout::update(float dt) {

}

void Breakout::render(float dt) {
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //_renderer.draw({{400.f, 400.f}, {32.f, 32.f}});
    _levels[_selectedLevel].draw(_renderer);
}

void Breakout::poll() {
    glfwSwapBuffers(_window.data());
    glfwPollEvents();
}