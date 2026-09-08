#pragma once

#include <glm/glm.hpp>

#include "Texture.h"
#include "ResourceManager.h"

class GameObject {
public:
	GameObject() = default;

	GameObject(const glm::vec2& position, const glm::vec2& size)
		: _position{position}, _size{size} { }

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

	Texture& texture() const { return ResourceManager::getTexture(_texture); }
	GameObject& setTexture(const std::string& texture) {
		_texture = texture;
		return *this;
	}
protected:
	glm::vec2 _position{};
	glm::vec2 _size{};
	std::string _texture{};
};

class GameTile : public GameObject {
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
private:
	int _strength{};
};

class GameObjectMoveable : public GameObject {
public:
	GameObjectMoveable() = default;

	GameObjectMoveable(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity)
		: GameObject{position, size}, _velocity{velocity} { }

	glm::vec2 velocity() const { return _velocity; }
	GameObjectMoveable& setVelocity(const glm::vec2& velocity) { 
		_velocity = velocity;
		return *this;
	}
private:
	glm::vec2 _velocity{};
};

class GameBall : public GameObjectMoveable {
public:
	GameBall() = default;

	GameBall(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity)
		: GameObjectMoveable{position, size, velocity} {
		_texture = "ball";
	}
};

class GamePaddle : public GameObjectMoveable {
public:
	GamePaddle() = default;

	GamePaddle(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity)
		: GameObjectMoveable{position, size, velocity} {
		_texture = "paddle";
	}
};

