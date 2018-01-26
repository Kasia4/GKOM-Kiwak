#pragma once

#include <iostream>
#include <GL/glew.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Texture
{
public:
	Texture();
	Texture(const char* path);
	~Texture();

	GLuint load(const char* path);
	GLuint getId() const;

private:
	GLuint id;
};

