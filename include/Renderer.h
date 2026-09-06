#pragma once

#include <array>

#include "NamedObjects.h"
#include "Shader.h"
#include "GameObject.h"

class Renderer {
public:
	Renderer();
	void draw(const GameObject& o) const;
private:
	Vao _vao{};
	Vbo _vbo{{
		{{-1.f,  1.f}, {0.f, 0.f}},
		{{ 1.f,  1.f}, {1.f, 0.f}},
		{{ 1.f, -1.f}, {1.f, 1.f}},
		{{-1.f, -1.f}, {0.f, 1.f}},
	}};
	Ebo _ebo{{0, 1, 2, 0, 3, 2}};
};