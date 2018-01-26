#include "ArcModel.h"


ArcModel::ArcModel()
{
}

ArcModel::ArcModel(GLfloat radius1, GLfloat radius2, GLfloat height, GLfloat angle, GLuint segments, const glm::vec3& v)
	: Model(v)
	, inner_radius(radius1)
	, outer_radius(radius2)
	, angle(angle)
	, height(height)
	, segments(segments)
{
	generate();
}


ArcModel::~ArcModel()
{
}

void ArcModel::generate()
{
	GLuint v_count = 8 * segments + 16;
	GLuint i_count = 8 * segments + 4;
	setVertices(v_count);
	setIndices(i_count);
	GLfloat seg_angle = angle / segments;
	glm::vec2 *base_vertices = new glm::vec2[2 * segments + 2];
	for (GLuint i = 0; i <= segments; ++i)
	{
		glm::vec2 norm_vec = glm::vec2(cos(i*seg_angle), sin(i*seg_angle));
		base_vertices[2 * i] = norm_vec * inner_radius;
		base_vertices[2 * i + 1] = norm_vec * outer_radius;;
	}

	glm::vec3 down(0.0f, -1.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	GLfloat in_seg_len = glm::length(base_vertices[0] - base_vertices[2]);
	GLfloat out_seg_len = glm::length(base_vertices[1] - base_vertices[3]);
	for (GLuint i = 0; i <= segments; ++i)
	{
		glm::vec3 normal = glm::normalize(v2ToV3(base_vertices[2 * i]));
		glm::vec3 neg_normal = glm::vec3(0, 0, 0) - normal;
		setVertex(8 * i,	 v2ToV3(base_vertices[2 * i]),				neg_normal, glm::vec2(in_seg_len*i, 0.0f));
		setVertex(8 * i + 1, v2ToV3(base_vertices[2 * i], height),		neg_normal, glm::vec2(in_seg_len*i, height));
		setVertex(8 * i + 2, v2ToV3(base_vertices[2 * i + 1]),			normal,		glm::vec2(out_seg_len*i, 0.0f));
		setVertex(8 * i + 3, v2ToV3(base_vertices[2 * i + 1], height),	normal,		glm::vec2(out_seg_len*i, height));
		setVertex(8 * i + 4, v2ToV3(base_vertices[2 * i], height),		up,			base_vertices[2 * i]);
		setVertex(8 * i + 5, v2ToV3(base_vertices[2 * i + 1], height),	up,			base_vertices[2 * i + 1]);
		setVertex(8 * i + 6, v2ToV3(base_vertices[2 * i]),				down,		base_vertices[2 * i]);
		setVertex(8 * i + 7, v2ToV3(base_vertices[2 * i + 1]),			down,		base_vertices[2 * i + 1]);
	}
	for (GLuint i = 0; i < segments; ++i)
	{
		setIndex(8 * i,		glm::uvec3(8 * i,	  8 * i + 1,		8 * (i + 1) + 1));
		setIndex(8 * i + 1, glm::uvec3(8 * i,	  8 * (i + 1),		8 * (i + 1) + 1));
		setIndex(8 * i + 2, glm::uvec3(8 * i + 2, 8 * i + 3,		8 * (i + 1) + 3));
		setIndex(8 * i + 3, glm::uvec3(8 * i + 2, 8 * (i + 1) + 2,	8 * (i + 1) + 3));
		setIndex(8 * i + 4, glm::uvec3(8 * i + 4, 8 * i + 5,		8 * (i + 1) + 5));
		setIndex(8 * i + 5, glm::uvec3(8 * i + 4, 8 * (i + 1) + 4,	8 * (i + 1) + 5));
		setIndex(8 * i + 6, glm::uvec3(8 * i + 6, 8 * i + 7,		8 * (i + 1) + 7));
		setIndex(8 * i + 7, glm::uvec3(8 * i + 6, 8 * (i + 1) + 6,	8 * (i + 1) + 7));
	}
	glm::vec3 normal1 = glm::normalize(glm::cross(v2ToV3(base_vertices[1] - base_vertices[0]), up));
	glm::vec3 normal2 = glm::normalize(glm::cross(v2ToV3(base_vertices[2 * segments + 1] - base_vertices[2 * segments]), up));
	GLfloat seg_depth = outer_radius - inner_radius;
	
	setVertex(8 * segments + 8, v2ToV3(base_vertices[0]), normal1, glm::vec2(0, 0));
	setVertex(8 * segments + 9, v2ToV3(base_vertices[1]), normal1, glm::vec2(seg_depth, 0));
	setVertex(8 * segments + 10, v2ToV3(base_vertices[0], height), normal1, glm::vec2(0, 1));
	setVertex(8 * segments + 11, v2ToV3(base_vertices[1], height), normal1, glm::vec2(seg_depth, 1));
	setVertex(8 * segments + 12, v2ToV3(base_vertices[2 * segments]), normal2, glm::vec2(0, 0));
	setVertex(8 * segments + 13, v2ToV3(base_vertices[2 * segments + 1]), normal2, glm::vec2(seg_depth, 0));
	setVertex(8 * segments + 14, v2ToV3(base_vertices[2 * segments], height), normal2, glm::vec2(0, 1));
	setVertex(8 * segments + 15, v2ToV3(base_vertices[2 * segments + 1], height), normal2, glm::vec2(seg_depth, 1));
	
	setIndex(8 * segments, glm::uvec3(8 * segments + 8, 8 * segments + 9, 8 * segments + 10));
	setIndex(8 * segments+1, glm::uvec3(8 * segments + 9, 8 * segments + 10, 8 * segments + 11));

	setIndex(8 * segments+2, glm::uvec3(8 * segments + 12, 8 * segments + 13, 8 * segments + 14));
	setIndex(8 * segments+3, glm::uvec3(8 * segments + 13, 8 * segments + 14, 8 * segments + 15));

	setBuffers();
	
}
