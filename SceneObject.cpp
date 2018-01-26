#include "SceneObject.h"

SceneObject::SceneObject(SceneObject * parent)
{
	setParent(parent);
	updateTrans();
}

SceneObject::~SceneObject()
{
}

void SceneObject::setPosition(const glm::vec3 & v)
{
	position = glm::translate(glm::mat4(), v);
	updateTrans();
}

glm::vec3 SceneObject::getPosition() const
{
	return (position * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
}

glm::mat4 SceneObject::getPositionMatrix() const
{
	return position;
}

void SceneObject::setOrientation(const glm::vec3& v)
{
	orientation = glm::eulerAngleYXZ(v.y, v.x, v.z);
	updateTrans();
}

glm::vec3 SceneObject::getOrientation() const
{

	return base_rotations;

}

glm::mat4 SceneObject::getOrientationMatrix() const
{
	return orientation;
}

void SceneObject::setScale(const glm::vec3 & v)
{
	scale = glm::scale(glm::mat4(), v);
	updateTrans();
}

glm::vec3 SceneObject::getScale() const
{
	return (scale * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)).xyz;
}

glm::mat4 SceneObject::getScaleMatrix() const
{
	return scale;
}

void SceneObject::translate(const glm::vec3 & v)
{
	position = glm::translate(position, v);
	updateTrans();
}

void SceneObject::rotateX(GLfloat angle)
{
	base_rotations.x += angle;
	rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f));
}

void SceneObject::rotateY(GLfloat angle)
{
	base_rotations.y += angle;
	rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
}

void SceneObject::rotateZ(GLfloat angle)
{
	base_rotations.z += angle;
	rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f));
}


void SceneObject::setRotationX(GLfloat angle)
{
	GLfloat rot = angle - base_rotations.x;
	angle = base_rotations.x;
	rotateX(rot);
}

void SceneObject::setRotationY(GLfloat angle)
{
	GLfloat rot = angle - base_rotations.y;
	angle = base_rotations.y;
	rotateY(rot);
}

void SceneObject::setRotationZ(GLfloat angle)
{
	GLfloat rot = angle - base_rotations.z;
	angle = base_rotations.z;
	rotateZ(rot);
}

glm::vec3 SceneObject::getRotation() const
{
	return base_rotations;
}

void SceneObject::rotate(GLfloat angle, glm::vec3 & axis)
{
	orientation = glm::rotate(orientation, angle, axis);
	updateTrans();
}

void SceneObject::rotate(GLfloat angle, glm::vec3 & axis, glm::vec3 & around)
{
	position = glm::translate(glm::mat4(), around + glm::rotate(getPosition() - around, angle, axis));
	orientation = glm::rotate(orientation, angle, axis);
	updateTrans();
}

void SceneObject::lookAt(glm::vec3 & eye, glm::vec3 & center, glm::vec3 & up)
{
	orientation = glm::lookAt(eye, center, up);
	updateTrans();
}

void SceneObject::setPivot(const glm::vec3 & pos)
{
	pivot = pos;
}

glm::vec3 SceneObject::getPivot() const
{
	return pivot;
}

void SceneObject::updateTrans()
{
	local_trans = glm::translate(position, pivot) * orientation * scale;
	global_trans = parent ? parent->global_trans * local_trans : local_trans;
	for (SceneObject* obj : children)
	{
		obj->updateTrans();
	}
}

void SceneObject::draw() const
{
}

void SceneObject::setLocalTrans(const glm::mat4 & trans)
{
	local_trans = trans;
	updateTrans();
}

glm::mat4 SceneObject::getGlobalTrans() const
{
	return global_trans;
}

void SceneObject::addChildren(SceneObject * child)
{
	if (std::find(children.begin(), children.end(), child) != children.end()) 
		return;
	child->parent = this;
	children.push_back(child);
	child->updateTrans();
}

void SceneObject::removeChildren(SceneObject * child)
{
	children.remove(child);
}

void SceneObject::setParent(SceneObject * par)
{
	if (parent == par)
		return;
	if(parent)
		parent->removeChildren(this);
	parent = par;
	if(parent)
		parent->addChildren(this);
	
}

void SceneObject::setAnimation(Animation animation)
{
	this->animation = animation;
}

Animation SceneObject::getAnimation() const
{
	return animation;
}

void SceneObject::update()
{
	if(animation)
		animation(this);
}

void SceneObject::setTimer(GLfloat * time)
{
	timer = time;
}

GLfloat SceneObject::getTime() const
{
	return *timer;
}

SceneObject * SceneObject::getParent() const
{
	return parent;
}
