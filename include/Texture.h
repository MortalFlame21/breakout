#pragma once 
#include <string_view> // std::string_view
#include <stdexcept> // std::runtime_error

#include <glad/glad.h>
#include <stb/stb_image.h>

class Texture {
public:
	static constexpr inline auto BLOCK_TEXTURE_SIZE{5};

	Texture();
	explicit Texture(std::string_view path);

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
	Texture(Texture&& o) noexcept;
	Texture& operator=(Texture&& o) noexcept;
	~Texture();

	static void setup();

	void setParam(GLenum target, GLenum name, GLint parameter);
	void load(std::string_view path);

	void bind(GLuint slot = 0) const;
	void unbind() const;

	GLuint id() const { return _id; }

	int width() const { return _width; }

	int height() const { return _height; }
private:
	GLuint _id{};
	int _width{};
	int _height{};
	int _numColorChannels{};

	void release() const { glDeleteTextures(1, &_id); }
};