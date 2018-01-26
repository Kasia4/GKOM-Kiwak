#pragma once

#include <string>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShProgram.h"
#include "Light.h"
#include "Material.h"
#include "Environment.h"

class Renderer
{
public:
	Renderer(ShProgram& shader);
	~Renderer();

	void use(const GLuint& VAO, const glm::mat4& trans, const GLuint indices_count, const Material* mat);
	void setObjectMatrix(const glm::mat4& mtx);
	void setViewMatrix(const glm::mat4& mtx);
	void setProjectionMatrix(const glm::mat4& mtx);
	void setObjectMaterial(const Material* material);
	void setLight(const Light& light);
	void setEnvironment(const Environment& environment);

private:
	ShProgram & shader;
	GLuint transformLoc;
	GLuint viewLoc;
	GLuint projLoc;
};

