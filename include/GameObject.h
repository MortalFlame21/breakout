#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/common.hpp>

#include "Texture.h"
#include "ResourceManager.h"
#include "Window.h"

// generic game object
class GameObject {
public:
	GameObject() = default;

	GameObject(const glm::vec2& position, const glm::vec2& size)
		: _position{position}, _size{size} { }

	glm::vec2& position() { return _position; }
	glm::vec2 position() const { return _position; }
	GameObject& setPosition(const glm::vec2& position) { 
		_position = position;
		return *this;
	}

	glm::vec2 size() const { return _size; }
	GameObject& setSize(const glm::vec2& size) { 
		_size = size; 
		return *this;
	}

	glm::vec3 color() const { return _color; }
	GameObject& setColor(const glm::vec3& color) { 
		_color = color; 
		return *this;
	}

	Texture& texture() const { return ResourceManager::getTexture(_texture); }
	GameObject& setTexture(const std::string& texture) {
		_texture = texture;
		return *this;
	}

	ShaderProgram& shader() const { return ResourceManager::getShader(_shader); }
	GameObject& setShader(const std::string& shader) {
		_shader = shader;
		return *this;
	}
protected:
	glm::vec2 _position{};
	glm::vec2 _size{};
	glm::vec3 _color{1.f};
	std::string _texture{};
	std::string _shader{};
};

// class that can move
class Moveable {
public:
	Moveable(const glm::vec2& velocity)
		: _velocity{velocity} { }

	glm::vec2& velocity() { return _velocity; }
	glm::vec2 velocity() const { return _velocity; }
	void setVelocity(const glm::vec2& velocity) { _velocity = velocity; }
protected:
	glm::vec2 _velocity{};
};

// class that interacts with other classes
class Interactable {
public:
	struct CollisionInfo {
		enum class Direction { UP, DOWN, LEFT, RIGHT };
		bool collided{};
		Direction direction{};
		glm::vec2 difference{};
	};

	virtual CollisionInfo collides(GameObject& o) { return {}; };

	static CollisionInfo::Direction direction(const glm::vec2& v) {
		const glm::vec2 dirs[]{
			glm::vec2{0.f, 1.f},  // up
			glm::vec2{0.f, -1.f}, // down
			glm::vec2{-1.f, 0.f}, // left
			glm::vec2{1.f, 0.f},  // right
		};
		float max{};
		CollisionInfo::Direction bestMatch{};

		for (std::size_t i{}; const auto& d : dirs) {
			if (auto dp{glm::dot(glm::normalize(v), d)}; dp > max) {
				max = dp;
				bestMatch = static_cast<CollisionInfo::Direction>(i);
			}
			++i;
		}
		return bestMatch;
	}
};

class GameBackground : public GameObject {
public:
	GameBackground() : GameObject{{ Window::WIDTH / 2, Window::HEIGHT / 2 }, { Window::WIDTH, Window::HEIGHT }}
	{
		_texture = "background";
	}
};

class GameTile 
	: public GameObject
	, public Interactable
{
public:
	// invariant strength < 0, if == 0 we destruct -- boom.

	static constexpr auto strengthMin{1};
	static constexpr auto strengthMax{5};

	GameTile(const glm::vec2& position, const glm::vec2& size, int strength) 
		: GameObject{position, size}, _strength{strength}
	{
		_texture = strengthTexture(_strength);
	}

	static std::string strengthTexture(int strength) {
		return "tile" + std::to_string(std::clamp(strength, strengthMin, strengthMax) - 1);
	}

	void weaken() { --_strength; }
	bool alive() const { return _strength > 0; }
	int strength() const { return _strength; }
private:
	int _strength{};
};

class GamePaddle
	: public GameObject
	, public Moveable
	, public Interactable
{
public:
	GamePaddle()
		: GameObject{{Window::WIDTH / 2, Window::HEIGHT - 40.f}, {200.f, 40.f}}
		, Moveable{{250.f, 0.f}}
	{
		_texture = "paddle";
	}

	void input(float dt, Window& window) {
		const auto pressed{ [&](int k) { return glfwGetKey(window.data(), k) == GLFW_PRESS; } };

		if (pressed(GLFW_KEY_A) || pressed(GLFW_KEY_LEFT)) {
			_position += dt * -_velocity;
		}
		if (pressed(GLFW_KEY_D) || pressed(GLFW_KEY_RIGHT)) {
			_position += dt * _velocity;
		}
	}
};

class GameBall
	: public GameObject
	, public Moveable
	, public Interactable
{
public:
	static inline const glm::vec2 startVelocity{ 500.f, -300.f };

	GameBall()
		: GameObject{ {Window::WIDTH / 2, Window::HEIGHT / 2}, {25.f, 25.f} }
		, Moveable{ startVelocity }
	{
		_texture = "ball";
	}

	glm::vec2 move(float dt) {
		_position += dt * _velocity;
		return _position;
	}

	bool stuck() const { return _stuck; }
	GameBall& setStuck(bool stuck) {
		_stuck = stuck;
		return *this;
	}

	float radius() const { return size().x / 2; }

	void update(float dt, Window& window, GamePaddle& player) {
		if (!_stuck)
			move(dt);
		else
			setPosition(player.position() - glm::vec2{ 0.f, player.size().y });
	}
	
	virtual CollisionInfo collides(GameObject& o) override {
		const glm::vec2 aabbHalfLengths{o.size().x / 2, o.size().y / 2}; 
		const glm::vec2 aabbCenter{o.position()}; 
		const auto posDiff{_position - aabbCenter};
		const auto clamped{glm::clamp(posDiff, -aabbHalfLengths, aabbHalfLengths)};
		const auto closest{aabbCenter + clamped};
		const auto diff{closest - position()};
		if (glm::length(diff) < radius()) 
			return {true, Interactable::direction(diff), diff}; 
		return {false, CollisionInfo::Direction::UP, {}};
	}
private:
	bool _stuck{ true };
};
