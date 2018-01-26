#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
class Environment
{
public:
	Environment();
	~Environment();

	void setAmbientLight(GLfloat value);
	GLfloat getAmbientLight() const;

	void setAmbientColor(const glm::vec3& value);
	glm::vec3 getAmbientColor() const;


private:
	GLfloat ambient_light;
	glm::vec3 ambient_color;
};

