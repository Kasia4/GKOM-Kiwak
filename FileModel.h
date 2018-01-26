#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include "Model.h"

class FileModel :
	public Model
{
private:
	const GLchar* modelPath;

public:
	FileModel(const GLchar* modelPath, const glm::vec3& v = glm::vec3());
	~FileModel();
	void generate();

};

