#include "Environment.h"


Environment::Environment()
	:ambient_light(0.0f)
	,ambient_color(glm::vec3(1.0f, 1.0f, 1.0f))
{
}


Environment::~Environment()
{
}

void Environment::setAmbientLight(GLfloat value)
{
	ambient_light = value;
}

GLfloat Environment::getAmbientLight() const
{
	return ambient_light;
}

void Environment::setAmbientColor(const glm::vec3 & value)
{
	ambient_color = value;
}

glm::vec3 Environment::getAmbientColor() const
{
	return ambient_color;
}
