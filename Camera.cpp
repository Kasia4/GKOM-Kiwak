#include "Camera.h"

Camera::Camera(SceneObject* parent)
	:SceneObject(parent)
{
}


Camera::~Camera()
{
}

void Camera::setProjection(const glm::mat4 & mtx)
{
	projection = mtx;
}

glm::mat4 Camera::getProjection() const
{
	return projection;
}

