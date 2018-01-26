#pragma once

#include <vector>
#include <cmath>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define M_PI 3.1415926

class ConvexShape
{
public:
	ConvexShape();
	ConvexShape(const std::vector<glm::vec2>& vert_list);
	ConvexShape(GLuint vert_count);
	
	~ConvexShape();
	void generateRegular(GLuint vert_count, GLfloat radius = 1.0f);

	glm::vec2 getVertex(GLuint idx) const;
	const std::vector<glm::vec2>& getVertices() const;
	GLuint getVerticesCount() const;
	glm::vec2 getCenter() const;

private:
	std::vector<glm::vec2> vertices;
};


