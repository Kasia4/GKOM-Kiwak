#pragma once
#include "Model.h"

#include <vector>

class LatheModel: public Model
{
public:
	LatheModel(const GLuint seg, const std::vector<glm::vec2>& line, const glm::vec3& = glm::vec3());
	~LatheModel();

	void generate();

private:
	std::vector<glm::vec2> side_line;
	GLuint segments;
};

