#include "PyramidModel.h"

PyramidModel::PyramidModel(const ConvexShape& shape, const glm::vec3& v)
	: shape(shape)
{
	generate();
}

PyramidModel::~PyramidModel()
{
}



void PyramidModel::generate()
{
	GLuint sh_v = shape.getVerticesCount();
	GLuint v_count = 4 * sh_v + 1;
	GLuint i_count = 2 * sh_v;
	setVertices(v_count);
	setIndices(i_count);
	
	glm::vec2 center = shape.getCenter();
	glm::vec3 tip(center.x, 1.0f, center.y);
	glm::vec3 down(0.0f, -1.0f, 0.0f);

	GLfloat tex_pos = 0;
	GLfloat seg_len;
	GLfloat side_h;
	glm::vec3 normal;
	
	glm::vec3 curr = v2ToV3(shape.getVertex(0));
	glm::vec3 next = v2ToV3(shape.getVertex(1));
	for (GLuint i = 0; i < sh_v; ++i) {
		seg_len = glm::length(curr - next);
		side_h = glm::length(glm::cross(tip - curr, tip - next)) / seg_len;
		normal = glm::normalize(glm::cross(next - tip,curr-tip));
		
		setVertex(3 * i, curr, normal, glm::vec2(tex_pos, 0.0f));
		setVertex(3 * i + 1, next, normal, glm::vec2(tex_pos + seg_len, 0.0f));
		setVertex(3 * i + 2, tip, normal, glm::vec2(tex_pos + seg_len / 2, side_h));

		setVertex(3 * sh_v + i, curr, down, glm::vec2(curr.x, curr.z));

		setIndex(2 * i, glm::uvec3(3 * i, 3 * i + 1, 3 * i + 2));
		setIndex(2 * i + 1, glm::uvec3(3 * sh_v + i, 3 * sh_v + (i + 1) % sh_v, 4 * sh_v));
		
		tex_pos += seg_len;
		curr = next;
		next = v2ToV3(shape.getVertex((i + 2) % sh_v));
	}
	setVertex(4 * sh_v, v2ToV3(center), down, center);
	setBuffers();
}
