#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

class GameObject {
public:
	GameObject(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity)
		: _position{position}
		, _size{size}
		, _velocity{velocity}
	{ }

	glm::vec2 position() const { return _position; }

	glm::vec2 size() const { return _size; }

	glm::vec2 velocity() const { return _velocity; }
private:
	//Texture _texture{};
	glm::vec2 _position{};
	glm::vec2 _size{};
	glm::vec2 _velocity{};
};



