#include "Light.h"



void Light::setPower(GLfloat value)
{
	power = value;
}

void Light::setColor(const glm::vec3 & col)
{
	color = col;
}

GLfloat Light::getPower() const
{
	return power;
}

glm::vec3 Light::getColor() const
{
	return color;
}

Light::Light()
	:color(glm::vec3(1.0f, 1.0f, 1.0f))
	,power(1.0f)
{	
}


Light::~Light()
{
}
