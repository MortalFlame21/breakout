#pragma once

#include <cstddef> // offsetof
#include <vector> // std::vector

#include <glad/glad.h>
#include <glm/glm.hpp>

struct Vertex {
	glm::vec2 position{};
	glm::vec2 tex_coords{};
};

// named objects: vao, vbo, ebo

class Vbo {
public:
	Vbo() {
		glGenBuffers(1, &_id);
		bind();
	}

	Vbo(const std::vector<Vertex>& vertices) : Vbo{} { bufferData(vertices); }

	Vbo(const Vbo& o) = delete;
    Vbo& operator=(const Vbo&) = delete;

	Vbo(Vbo&& o) noexcept : _id{o._id} { o._id = 0; }

	Vbo& operator=(Vbo&& o) noexcept {
		if (this != &o) {
			glDeleteBuffers(1, &_id);
			_id = o._id;
			o._id = 0;
		}
		return *this;
	}

	~Vbo() { glDeleteBuffers(1, &_id); }

	GLuint id() const { return _id; }

	void bufferData(const std::vector<Vertex>& vertices) const {
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	}

	void bind() const { glBindBuffer(GL_ARRAY_BUFFER, _id); }

	void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
private:
	GLuint _id{};
};

class Ebo {
public:
	Ebo() {
		glGenBuffers(1, &_id);
		bind();
	}

	Ebo(const Ebo& o) = delete;
	Ebo& operator=(const Ebo&) = delete;

	Ebo(Ebo&& o) noexcept : _id{ o._id } { o._id = 0; }

	Ebo& operator=(Ebo&& o) noexcept {
		if (this != &o) {
			glDeleteBuffers(1, &_id);
			_id = o._id;
			o._id = 0;
		}
		return *this;
	}

	Ebo(const std::vector<GLuint>& points) : Ebo{} { bufferData(points); }

	~Ebo() { glDeleteBuffers(1, &_id); }

	GLuint id() const { return _id; }

	void bufferData(const std::vector<GLuint>& points) const {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat) * points.size(), points.data(), GL_STATIC_DRAW);
	}

	void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id); }

	void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
private:
	GLuint _id{};
};

class Vao {
public:
	Vao() {
		glGenVertexArrays(1, &_id);
		bind();
	}

	Vao(const Vao& o) = delete;
	Vao& operator=(const Vao&) = delete;

	Vao(Vao&& o) noexcept : _id{o._id} { o._id = 0; }

	Vao& operator=(Vao&& o) noexcept {
		if (this != &o) {
			glDeleteVertexArrays(1, &_id);
			_id = o._id;
			o._id = 0;
		}
		return *this;
	}

	~Vao() { glDeleteVertexArrays(1, &_id); }

	void vertexAttribPointer(GLuint index, GLint size,
							GLenum type, GLboolean normalised,
							GLsizei stride, const GLvoid* offset_pointer) const
	{
		glVertexAttribPointer(index, size, type, normalised, stride, offset_pointer);
	}

	void enableVertexAttribArray(GLuint index) const {
		glEnableVertexAttribArray(index);
	}

	GLuint id() const { return _id; }

	void bind() const { glBindVertexArray(_id); }

	void unbind() const { glBindVertexArray(0); }
private:
	GLuint _id{};
};