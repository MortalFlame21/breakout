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
    ResourceManager::getShader("default").setUniformM("uProjection", 1, GL_FALSE, 
	    glm::ortho(0.f, Window::WIDTH, Window::HEIGHT, 0.f, -1.f, 1.f));

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
    // input
    _player.input(dt, _window);
    if (glfwGetKey(_window.data(), GLFW_KEY_SPACE) == GLFW_PRESS)
        _ball.setStuck(false);

    // updates
    _ball.update(dt, _window, _player);

    wallCollisions();
    tileCollisions();
    paddleCollisions();
}

void Breakout::render(float dt) {
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    const static GameBackground bg{};
    _renderer.draw(bg);
    _levels [_selectedLevel].draw(_renderer);
    _renderer.draw(_player);
    _renderer.draw(_ball);
}

void Breakout::poll() {
    glfwSwapBuffers(_window.data());
    glfwPollEvents();
}

void Breakout::wallCollisions() {
	// not clean but idc no more, need to consume more knowledge, this project is delaying me 
    // ball-wall collision
    // left wall
    if (_ball.position().x - _ball.radius() <= 0.f) {
		_ball.velocity().x = -_ball.velocity().x;
        _ball.position().x = _ball.radius();
    }
    // right wall
    if (_ball.position().x + _ball.radius() >= Window::WIDTH) {
		_ball.velocity().x = -_ball.velocity().x;
        _ball.position().x = Window::WIDTH - _ball.radius();
    }
    // top wall
    if (_ball.position().y - _ball.radius() <= 0.f) {
		_ball.velocity().y = -_ball.velocity().y;
        _ball.position().y = _ball.radius();
    }
    // bottom wall
    if (_ball.position().y + _ball.radius() >= Window::HEIGHT) {
        //restart();
    }
    // paddle-wall collision 
    // left wall
    if (_player.position().x - (_player.size().x / 2) <= 0.f)
        _player.position().x = (_player.size().x / 2);
    // right wall
    if (_player.position().x + (_player.size().x / 2) >= Window::HEIGHT)
        _player.position().x = Window::WIDTH - (_player.size().x / 2);
}

void Breakout::tileCollisions() {
    if (_ball.stuck()) return;

    auto& level{_levels[_selectedLevel].tiles()};
    for (auto& tile : level) {
        if (!tile.alive())
            continue;
            
        auto collision{_ball.collides(tile)};
        if (!collision.collided)
            continue;

        // resolve collision
        using Dir = Interactable::CollisionInfo::Direction;
        if (collision.direction == Dir::LEFT || collision.direction == Dir::RIGHT) {
		    _ball.velocity().x = -_ball.velocity().x;
            auto ox{_ball.radius() - std::abs(collision.difference.x)};
            _ball.position().x += (collision.direction == Dir::LEFT ? -ox : ox);
        }
        else {
		    _ball.velocity().y = -_ball.velocity().y;
            auto oy{_ball.radius() - std::abs(collision.difference.y)};
            _ball.position().y += (collision.direction == Dir::UP ? -oy : oy);
        }

		tile.weaken();
		tile.setTexture(GameTile::strengthTexture(tile.strength()));
    }

    std::erase_if(level, [](auto& t) { return !t.alive(); });
}

void Breakout::paddleCollisions() {
    auto collisionBall{_ball.collides(_player)};
    if (!_ball.stuck() && collisionBall.collided) {
        auto distanceX{_ball.position().x - _player.position().x};
        auto damp{distanceX / (_player.size().x / 2)};
        constexpr auto bounceStrength{2.f};
        
        const auto oldV{_ball.velocity()};
        _ball.velocity().x = GameBall::startVelocity.x * damp * bounceStrength;
        _ball.velocity().y = -std::abs(_ball.velocity().y);
        _ball.setVelocity(glm::normalize(_ball.velocity()) * glm::length(oldV));
    }
}
