#pragma once

#include <vector> // std::vector
#include <string_view> // std::string_view

#include "GameObject.h"
#include "Renderer.h"

class GameLevel {
public:
	explicit GameLevel(std::string_view file);
	void draw(Renderer& renderer) const;
private:
	std::vector<GameObject> _tiles{};
};