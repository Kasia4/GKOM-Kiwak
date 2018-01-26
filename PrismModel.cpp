#include "PrismModel.h"



PrismModel::PrismModel(const ConvexShape& shape, GLfloat radius1, GLfloat radius2, GLfloat height, const glm::vec3& v)
	: Model(v)
	, shape(shape)
	, radius1(radius1)
	, radius2(radius2)
	, height(height)
{
	generate();
}

PrismModel::PrismModel(const ConvexShape & shape, GLfloat radius1, GLfloat radius2, GLfloat height, glm::vec2 b_trans, const glm::vec3& v)
	: Model(v)
	, shape(shape)
	, radius1(radius1)
	, radius2(radius2)
	, height(height)
{
	base_translation = glm::vec3(b_trans.x, 0.0f, b_trans.y);
	generate();
}

PrismModel::~PrismModel()
{
}

void PrismModel::generate()
{
	GLuint sh_v = shape.getVerticesCount();
	GLuint v_count = 6 * sh_v + 2;
	GLuint i_count = 4 * sh_v;
	setVertices(v_count);
	setIndices(i_count);
	
	glm::vec2 center = shape.getCenter() * radius1;
	glm::vec2 center_u = shape.getCenter() * radius2;
	glm::vec3 down(0.0f, -1.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::vec3 normal;
	
	GLfloat tex_pos = 0;
	GLfloat seg_len;
	glm::vec3 curr = v2ToV3(shape.getVertex(0) * radius1) ;
	glm::vec3 curr_u = v2ToV3(shape.getVertex(0) * radius2, height) + base_translation;
	glm::vec3 next = v2ToV3(shape.getVertex(1) * radius1) ;
	glm::vec3 next_u = v2ToV3(shape.getVertex(1) * radius2, height)  + base_translation;

	for (GLuint i = 0; i < sh_v; ++i)
	{
		seg_len = glm::length(curr - next);
		normal = glm::normalize(glm::cross(curr_u - curr, next-curr));
		setVertex(4 * i, curr, normal, glm::vec2(tex_pos, 0.0f));
		setVertex(4 * i + 1, curr_u, normal, glm::vec2(tex_pos, height));
		setVertex(4 * i + 2, next, normal, glm::vec2(tex_pos + seg_len, 0.0f));
		setVertex(4 * i + 3, next_u, normal, glm::vec2(tex_pos + seg_len, height));

		setVertex(4 * sh_v + i, curr, down, glm::vec2(curr.x, curr.z));
		setVertex(5 * sh_v + i, curr_u, up, glm::vec2(curr_u.x, curr_u.z));

		setIndex(2 * i, glm::uvec3(4 * i, 4 * i + 1, 4 * i + 2));
		setIndex(2 * i + 1, glm::uvec3(4 * i + 1, 4 * i + 2, 4 * i + 3));
		setIndex(2 * sh_v + i, glm::uvec3(4 * sh_v + i, 4 * sh_v + (i + 1) % sh_v, 6 * sh_v));
		setIndex(3 * sh_v + i, glm::uvec3(5 * sh_v + i, 5 * sh_v + (i + 1) % sh_v, 6 * sh_v + 1));
		tex_pos += seg_len;
		curr = next;
		curr_u = next_u;
		next = v2ToV3(shape.getVertex((i + 2) % sh_v) * radius1);
		next_u = v2ToV3(shape.getVertex((i + 2) % sh_v) * radius2, height) + base_translation;
	}

	setVertex(6 * sh_v, v2ToV3(center), down, center);
	setVertex(6 * sh_v + 1, v2ToV3(center_u, height) + base_translation, up, center_u+glm::vec2(base_translation.x, base_translation.z));
	
	setBuffers();
}
