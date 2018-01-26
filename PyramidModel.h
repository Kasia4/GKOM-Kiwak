#pragma once
#include <cmath>

#include "Model.h"
#include "ConvexShape.h"

class PyramidModel: public Model
{
public:
	PyramidModel(const ConvexShape& shape, const glm::vec3& v = glm::vec3());
	~PyramidModel();	

	void generate();

private:
	const ConvexShape& shape;

};

