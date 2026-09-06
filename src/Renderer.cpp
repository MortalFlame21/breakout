#include "Renderer.h"
#include "ResourceManager.h"

#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer() {
	_vao.bind();
	_vbo.bind();
	_ebo.bind();

	_vao.vertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	_vao.enableVertexAttribArray(0);

	_vao.vertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tex_coords)));
	_vao.enableVertexAttribArray(1);
}

void Renderer::draw(const GameObject& o) const {
	ResourceManager::getShader("default").use();

	auto model{glm::translate(glm::mat4{1.f}, {o.position(), 0.f})};
	model = glm::scale(model, {o.size(), 0.f});

    ResourceManager::getShader("default").setUniformM("uModel", 1, GL_FALSE, model);
    ResourceManager::getShader("default").setUniformV("uTexture", 0);
	_vao.bind();
	ResourceManager::getTexture("ball").bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
