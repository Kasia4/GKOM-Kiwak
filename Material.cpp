#include "Material.h"

Material::Material()
	:texture_scale(glm::vec2(1.0f, 1.0f))
	, specular_level(0.0f)
	, glossiness(1)
	, color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{

}

Material::~Material()
{
}


void Material::setTexture(const Texture * tex)
{
	texture = tex;
}

void Material::setTextureScale(const glm::vec2 & scale)
{
	texture_scale = scale;
}

void Material::setSpecularLevel(GLfloat value)
{
	specular_level = glm::clamp(value, 0.0f, 1.0f);
}

void Material::setGlossiness(GLfloat value)
{
	glossiness = glm::clamp(value, 0.0f, 100.0f);
}

void Material::setColor(glm::vec4 color)
{
	this->color = color;
}

const Texture * Material::getTexture() const
{
	return texture;
}

glm::vec2 Material::getTextureScale() const
{
	return texture_scale;
}

GLfloat Material::getSpecularLevel() const
{
	return specular_level;
}

GLfloat Material::getGlossiness() const
{
	return glossiness;
}

glm::vec4 Material::getColor() const
{
	return color;
}

