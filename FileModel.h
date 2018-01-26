#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include "Model.h"

class FileModel: public Model
{
public:
	FileModel(const GLchar* modelPath, const glm::vec3& v = glm::vec3());
	~FileModel();
	void generate();

private:
	const GLchar* modelPath;

};

