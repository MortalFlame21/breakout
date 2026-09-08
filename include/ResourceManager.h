#pragma once

#include <unordered_map>
#include <string>

#include <glad/glad.h>

#include "Shader.h"
#include "Texture.h"

class ResourceManager {
public:
	static void loadShader(const std::string& name, ShaderProgram&& shader) {
		_shaders[name] = std::move(shader);
	}

	static ShaderProgram& getShader(const std::string& name) {
		return _shaders.at(name);
	}

	static void loadTexture(const std::string& name, Texture&& texture) {
		_textures[name] = std::move(texture);
	}

	static Texture& getTexture(const std::string& name) {
		return _textures.at(name);
	}
private:
	static inline std::unordered_map<std::string, ShaderProgram> _shaders{};
	static inline std::unordered_map<std::string, Texture> _textures{};
};