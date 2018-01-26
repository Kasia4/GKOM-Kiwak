#pragma once

#include "ConvexShape.h"
#include "Model.h"

class ConvexShapeModel :
	public Model
{
private:
	const ConvexShape& shape;
public:
	ConvexShapeModel(const ConvexShape& shape, const glm::vec3& v = glm::vec3());
	~ConvexShapeModel();

	void generate();
};

