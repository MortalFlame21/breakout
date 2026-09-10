#include "Window.h"

Window::Window(std::string_view title) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(_width, _height, title.data(), nullptr, nullptr);
	if (!_window) 
		throw std::runtime_error{"Error: (ctor) Window: Failed to open window!\n"};
	glfwMakeContextCurrent(_window);

	// window configurations
	glfwSetWindowUserPointer(_window, this);
	glfwSetFramebufferSizeCallback(_window, Window::framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error{"Error: (ctor) Window: Failed to load GLAD!\n"}; 
}

Window::~Window() {
	if (_window) glfwDestroyWindow(_window);
	glfwTerminate();
}

void Window::framebuffer_size_callback(GLFWwindow* window, int w, int h) {
	glViewport(0, 0, w, h);

	if (auto* self{static_cast<Window*>(glfwGetWindowUserPointer(window))}) {
		self->_width = w;
		self->_height = h;
	}
}
