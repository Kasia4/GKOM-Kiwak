#pragma once
#include "Model.h"

#include <vector>

class LoatheModel :
	public Model
{
private:
	std::vector<glm::vec2> side_line;
	GLuint segments;
public:
	LoatheModel(const GLuint seg, const std::vector<glm::vec2>& line, const glm::vec3& = glm::vec3());
	~LoatheModel();

	void generate();
};

