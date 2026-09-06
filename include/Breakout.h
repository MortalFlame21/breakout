#pragma once

#include "Window.h"
#include "Renderer.h"

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
};
