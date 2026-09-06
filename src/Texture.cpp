#include "Texture.h"

Texture::Texture() {
	glGenTextures(1, &_id); // generate and bind
	glBindTexture(GL_TEXTURE_2D, _id);

	// default settings
	setParam(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set up texture wrapping for s
	setParam(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // set up texture wrapping for t
	setParam(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // level of filtering for MINimising
	setParam(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // level of filtering for MAXimising
}

Texture::Texture(std::string_view path) : Texture{} {
	load(path);
	unbind();
}

Texture::Texture(Texture&& o) noexcept
	: _id{ o._id }
	, _width{ o._width }
	, _height{ o._height }
	, _numColorChannels{ o._numColorChannels }
{
	o._id = 0;
	o._width = 0;
	o._height = 0;
	o._numColorChannels = 0;
}

Texture& Texture::operator=(Texture&& o) noexcept {
	if (this != &o) {
		release();

		_id = o._id;
		_width = o._width;
		_height = o._height;
		_numColorChannels = o._numColorChannels;

		o._id = 0;
		o._width = 0;
		o._height = 0;
		o._numColorChannels = 0;
	}
	return *this;
}

Texture::~Texture() { release(); }

void Texture::setup() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    stbi_set_flip_vertically_on_load(true);
}

void Texture::load(std::string_view path) {
	auto* data{stbi_load(path.data(), &_width, &_height, &_numColorChannels, STBI_rgb_alpha)};
	if (!data) throw std::runtime_error{ "Error: Texture: Failed to load texture data" };
	// load texture on gpu
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	// generate mipmap of current texture
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

void Texture::setParam(GLenum target, GLenum name, GLint parameter) {
	glTexParameteri(target, name, parameter);
}

void Texture::bind(GLuint slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}


