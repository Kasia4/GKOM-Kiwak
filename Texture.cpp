#include "Texture.h"


Texture::Texture()
{
}

Texture::Texture(const char * path)
{
	load(path);
}


Texture::~Texture()
{
}

GLuint Texture::load(const char * path)
{
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw std::exception("Failed to load texture file");
	std::cout << "w: " << width << "h: " << height << std::endl;
	glGenTextures(1, &id);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return id;


}

GLuint Texture::getId() const
{
	return id;
}
