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
	GamePaddle _player{{Window::WIDTH / 2, Window::HEIGHT - Window::HEIGHT / 25}, 
					   {Window::WIDTH / 5, Window::HEIGHT / 25}, 
					   {}};
	GameBall _ball{{Window::WIDTH / 2, Window::HEIGHT / 2}, {25.f, 25.f}, {}};
	std::size_t _selectedLevel{};
};
