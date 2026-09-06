#pragma once

#include <string_view> // std::string_view
#include <stdexcept> // std::runtime_error

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
	static inline constexpr int WIDTH{800};
	static inline constexpr int HEIGHT{800};

	explicit Window(std::string_view title);

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;

	~Window();

	bool running() const { return !glfwWindowShouldClose(_window); }

	GLFWwindow* data() const { return _window; }

	int width() const { return _width; }

	int height() const { return _height; }
private:
	static void framebuffer_size_callback(GLFWwindow* window, int w, int h);

	GLFWwindow* _window{};
	int _width{WIDTH};
	int _height{HEIGHT};
};