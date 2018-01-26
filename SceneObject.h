#pragma once

#include <list>

#include <GL/glew.h>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/rotate_vector.hpp>

class SceneObject;

typedef void(*Animation)(SceneObject*);

class SceneObject
{
public:
	SceneObject(SceneObject* parent = nullptr);
	~SceneObject();

	void setPosition(const glm::vec3& v);
	glm::vec3 getPosition() const;
	glm::mat4 getPositionMatrix() const;

	
	//glm::vec3 getOrientation() const;
	void setOrientation(const glm::vec3& v);
	//void setOrientation(const glm::vec3 & n, const glm::vec3 & up);
	glm::vec3 getOrientation() const;
	glm::mat4 getOrientationMatrix() const;

	void setScale(const glm::vec3& v);
	glm::vec3 getScale() const;
	glm::mat4 getScaleMatrix() const;

	void translate(const glm::vec3& v);
	void rotate(GLfloat angle, glm::vec3& axis);
	void rotateX(GLfloat angle);
	void rotateY(GLfloat angle);
	void rotateZ(GLfloat angle);
	void setRotationX(GLfloat angle);
	void setRotationY(GLfloat angle);
	void setRotationZ(GLfloat angle);
	glm::vec3 getRotation() const;
	void lookAt(glm::vec3& eye, glm::vec3& center, glm::vec3& up);

	void setPivot(const glm::vec3& pos);
	glm::vec3 getPivot() const;
	void draw() const;

	void setLocalTrans(const glm::mat4& trans);
	glm::mat4 getGlobalTrans() const;
	
	void addChildren(SceneObject* child);
	void removeChildren(SceneObject* child);

	void setParent(SceneObject* par);

	void setAnimation(Animation animation);
	Animation getAnimation() const;
	void update();
	
	void setTimer(GLfloat *timer);
	GLfloat getTime() const;

	SceneObject* getParent() const;

private:

	glm::mat4 position;
	glm::mat4 orientation;
	glm::vec3 base_rotations;
	glm::mat4 scale;

	glm::mat4 local_trans;
	glm::mat4 global_trans;

	glm::vec3 pivot;

	SceneObject* parent;
	std::list<SceneObject*> children;

	Animation animation;
	GLfloat *timer;

	void updateTrans();

	void rotate(GLfloat angle, glm::vec3 & axis, glm::vec3 & around);
};