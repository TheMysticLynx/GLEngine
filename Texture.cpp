#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Depend/stb/stb_image.h"
#include <glad/glad.h>

Texture::Texture(const std::string path, int format)
{
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::Bind(int activeTexture)
{
	glActiveTexture(GL_TEXTURE0 + activeTexture);
	glBindTexture(GL_TEXTURE_2D, id);
}
