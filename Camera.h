#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SceneObject.h"

class Camera: public SceneObject
{

public:
	Camera(SceneObject* parent = nullptr);
	~Camera();

	void setProjection(const glm::mat4& mtx);
	glm::mat4 getProjection() const;

private:
	glm::mat4 projection;

	glm::mat4 camRot;
	glm::vec3 camPos;

};

