#pragma once

#include "ConvexShape.h"
#include "Model.h"

class ConvexShapeModel: public Model
{
public:
	ConvexShapeModel(const ConvexShape& shape, const glm::vec3& v = glm::vec3());
	~ConvexShapeModel();

	void generate();

private:
	const ConvexShape& shape;
};

