#include "ConvexShapeModel.h"

ConvexShapeModel::ConvexShapeModel(const ConvexShape& shape, const glm::vec3& v)
	:Model(v)
	,shape(shape)
{
	generate();
}

ConvexShapeModel::~ConvexShapeModel()
{
}

void ConvexShapeModel::generate()
{
	GLuint ov_size = shape.getVerticesCount();
	if (ov_size<3)
		return;
	GLuint v_count = ov_size + 1;
	GLuint i_count = ov_size;
	setVertices(v_count);
	setIndices(i_count);
	int i = 0;
	for (auto curr : shape.getVertices())
	{
		setVertex(i, glm::vec3(curr.x, 0.0f, curr.y), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(curr.x, curr.y));
		setIndex(i, glm::uvec3(i, (i + 1) % ov_size, ov_size));
		++i;
	}
	glm::vec2 center = shape.getCenter();
	setVertex(ov_size, glm::vec3(center.x, 0.0f, center.y), glm::vec3(0.0f, 1.0f, 0.0f), center);
	setBuffers();

}
