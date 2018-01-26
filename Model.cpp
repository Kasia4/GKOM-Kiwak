#include "Model.h"

const glm::vec3 Model::up = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 Model::down = glm::vec3(0.0f, -1.0f, 0.0f);

void Model::generateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void Model::setBuffers()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, VERTEX_SIZE * vertices_count * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDEX_SIZE * indices_count * sizeof(GLuint), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Model::setVertices(GLuint v_count)
{
	vertices_count = v_count;
	vertices = new GLfloat[v_count * VERTEX_SIZE];
}

void Model::setIndices(GLuint i_count)
{
	indices_count = i_count;
	indices = new GLuint[i_count * INDEX_SIZE];

}

void Model::setTranslation(const glm::vec3 & v)
{
	translation = v;
}

glm::vec3 Model::getTranslation() const
{
	return translation;
}

void Model::printVertices() const
{
	for (GLuint i = 0; i < vertices_count; ++i)
	{
		std::cout << vertices[VERTEX_SIZE * i] << ", " << vertices[VERTEX_SIZE * i + 1] << ", " << vertices[VERTEX_SIZE * i] << "\n";
	}
}


void Model::setVertex(GLuint n, const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& tex)
{
	glm::vec3 position = pos - translation;
	if (n >= vertices_count)
		return;
	vertices[VERTEX_SIZE * n    ] = position.x;
	vertices[VERTEX_SIZE * n + 1] = position.y;
	vertices[VERTEX_SIZE * n + 2] = position.z;
	vertices[VERTEX_SIZE * n + 3] = normal.x;
	vertices[VERTEX_SIZE * n + 4] = normal.y;
	vertices[VERTEX_SIZE * n + 5] = normal.z;
	vertices[VERTEX_SIZE * n + 6] = tex.x;
	vertices[VERTEX_SIZE * n + 7] = tex.y;

}

void Model::setIndex(GLuint n, const glm::uvec3& triangle)
{
	if (n >= indices_count)
		return;
	indices[INDEX_SIZE * n] = triangle.x;
	indices[INDEX_SIZE * n + 1] = triangle.y;
	indices[INDEX_SIZE * n + 2] = triangle.z;
}

Model::Model(const glm::vec3& v)
	:translation(v)
{
	generateBuffers();
}


Model::~Model()
{
	delete[] vertices;
	delete[] indices;
}

GLuint Model::getVAO() const
{
	return VAO;
}

GLuint Model::getEBO() const
{
	return EBO;
}

GLuint Model::getVBO() const
{
	return EBO;
}

GLuint Model::getIndicesCount() const
{
	return indices_count;
}

glm::vec3 v2ToV3(const glm::vec2& v, GLfloat y) {
	return glm::vec3(v.x, y, v.y);
}

glm::vec3 normal(const glm::vec3 & v, const glm::vec3 & w)
{
	return glm::normalize(glm::cross(v, w));
}

glm::vec3 cylindrical(GLfloat ro, GLfloat z, GLfloat fi)
{
	return glm::vec3(cos(fi)*ro, z, sin(fi)*ro);
}



