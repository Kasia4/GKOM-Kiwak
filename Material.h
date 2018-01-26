#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

class Material
{

private:
	const Texture* texture;
	glm::vec2 texture_scale;
	GLfloat specular_level;
	GLfloat glossiness;
	glm::vec4 color;

public:
	void setTexture(const Texture* tex);
	void setTextureScale(const glm::vec2& scale);
	void setSpecularLevel(GLfloat value);
	void setGlossiness(GLfloat value);
	void setColor(glm::vec4 color);


	const Texture* getTexture() const;
	glm::vec2 getTextureScale() const;
	GLfloat getSpecularLevel() const;
	GLfloat getGlossiness() const;
	glm::vec4 getColor() const;


	Material();
	~Material();
};

