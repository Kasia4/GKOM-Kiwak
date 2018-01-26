#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Texture.h"

#define M_PI 3.1415926
#define VERTEX_SIZE 8
#define INDEX_SIZE 3

class Model
{
public:
	static const glm::vec3 up;
	static const glm::vec3 down;

	Model(const glm::vec3& v = glm::vec3());
	~Model();
	virtual void generate() = 0;
	GLuint getVAO() const;
	GLuint getEBO() const;
	GLuint getVBO() const;
	GLuint getIndicesCount() const;
	void setTranslation(const glm::vec3& v);
	glm::vec3 getTranslation() const;

	void printVertices() const;

protected:
	void generateBuffers();
	void setBuffers();
	void setVertices(GLuint v_count);
	void setIndices(GLuint i_count);
	void setVertex(GLuint n, const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& tex);
	void setIndex(GLuint n, const glm::uvec3& triangle);

private:
	GLfloat * vertices;
	GLuint* indices;
	GLuint vertices_count;
	GLuint indices_count;
	GLuint VBO;
	GLuint EBO;
	GLuint VAO;
	glm::vec3 translation;

};

glm::vec3 v2ToV3(const glm::vec2& v, GLfloat y = 0.0f);
glm::vec3 normal(const glm::vec3& v,const glm::vec3& w);
glm::vec3 cylindrical(GLfloat ro, GLfloat z, GLfloat fi);

