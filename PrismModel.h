#pragma once
#include "Model.h"
#include "ConvexShape.h"
class PrismModel :
	public Model
{

	GLfloat radius1;
	GLfloat radius2;
	GLfloat height;

	glm::vec3 base_translation;
	const ConvexShape& shape;
public:
	PrismModel(const ConvexShape& shape, GLfloat radius1, GLfloat radius2, GLfloat height, const glm::vec3& v = glm::vec3());
	PrismModel(const ConvexShape& shape, GLfloat radius1, GLfloat radius2, GLfloat height, glm::vec2 b_trans, const glm::vec3& v = glm::vec3());
	~PrismModel();

	void generate();
};