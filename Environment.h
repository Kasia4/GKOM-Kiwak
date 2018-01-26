#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
class Environment
{
private:

	GLfloat ambient_light;
	glm::vec3 ambient_color;
public:
	void setAmbientLight(GLfloat value);
	GLfloat getAmbientLight() const;

	void setAmbientColor(const glm::vec3& value);
	glm::vec3 getAmbientColor() const;
	Environment();
	~Environment();
};

