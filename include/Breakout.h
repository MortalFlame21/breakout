#pragma once

#include <vector> // std::vector

#include "Window.h"
#include "Renderer.h"
#include "GameLevel.h"

class Breakout {
public:
	Breakout();

	void run();
	void update(float dt);
	void render(float dt);
	void poll();
private:
	enum class State { ACTIVE, MENU, WINNER };

	Window _window{"Breakout"};
	Renderer _renderer{};
	std::vector<GameLevel> _levels{};
	std::size_t _selectedLevel{};
};
