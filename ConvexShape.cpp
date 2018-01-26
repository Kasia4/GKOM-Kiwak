#include "ConvexShape.h"


ConvexShape::ConvexShape()
{
}


ConvexShape::ConvexShape(const std::vector<glm::vec2>& vert_list)
	:vertices(vert_list)
{

}

ConvexShape::ConvexShape(GLuint vert_count)
{
	generateRegular(vert_count);
}

ConvexShape::~ConvexShape()
{
}

void ConvexShape::generateRegular(GLuint vert_count, GLfloat radius)
{
	vertices.clear();
	vertices.reserve(vert_count);
	GLfloat step_angle = 2 * M_PI / vert_count;
	for (GLuint i = 0; i < vert_count; ++i) {
		GLfloat x = cos(i*step_angle)*radius;
		GLfloat y = sin(i*step_angle)*radius;
		vertices.push_back(glm::vec2(x, y));
	}
}

glm::vec2 ConvexShape::getVertex(GLuint idx) const
{
	return vertices[idx];
}

const std::vector<glm::vec2>& ConvexShape::getVertices() const
{
	return vertices;
}

GLuint ConvexShape::getVerticesCount() const
{
	return vertices.size();
}

glm::vec2 ConvexShape::getCenter() const
{
	glm::vec2 center;
	for (auto curr : vertices) {
		center += curr;
	}
	center /= vertices.size();
	return center;
}