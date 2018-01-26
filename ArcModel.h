#pragma once
#include "Model.h"
class ArcModel: public Model
{
public:
	ArcModel();
	ArcModel(GLfloat radius1, GLfloat radius2, GLfloat height, GLfloat angle, GLuint segments, const glm::vec3& v = glm::vec3());
	~ArcModel();

	void generate();

private:
	GLfloat outer_radius;
	GLfloat inner_radius;
	GLfloat angle;
	GLfloat height;
	GLuint segments;
};

