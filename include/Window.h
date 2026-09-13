#pragma once

#include <string_view> // std::string_view
#include <stdexcept> // std::runtime_error

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
	static inline constexpr float WIDTH{800.f};
	static inline constexpr float HEIGHT{800.f};

	explicit Window(std::string_view title);

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;

	~Window();

	bool running() const { return !glfwWindowShouldClose(_window); }

	GLFWwindow* data() const { return _window; }

	float width() const { return static_cast<float>(_width); }

	float height() const { return static_cast<float>(_height); }
private:
	static void framebuffer_size_callback(GLFWwindow* window, int w, int h);

	GLFWwindow* _window{};
	int _width{static_cast<int>(WIDTH)};
	int _height{static_cast<int>(HEIGHT)};
};