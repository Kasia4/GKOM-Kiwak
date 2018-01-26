#pragma once
#include "SceneObject.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Light :
	public SceneObject
{
	GLfloat power;
	glm::vec3 color;

public:
	void setPower(GLfloat value);
	void setColor(const glm::vec3& col);
	GLfloat getPower() const;
	glm::vec3 getColor() const;

	Light();
	~Light();
};

