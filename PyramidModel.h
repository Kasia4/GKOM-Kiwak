#pragma once
#include <cmath>

#include "Model.h"
#include "ConvexShape.h"

class PyramidModel :
	public Model
{
private:
	const ConvexShape& shape;
public:
	PyramidModel(const ConvexShape& shape, const glm::vec3& v = glm::vec3());
	~PyramidModel();	

	void generate();


};

