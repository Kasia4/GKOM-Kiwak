#pragma once

#include <map>
#include <GL/glew.h>

#include "SceneObject.h"

typedef void(*ObjectBehaviourFunc)(SceneObject*);

struct ObjectBehaviour {
	ObjectBehaviour();
	ObjectBehaviour(SceneObject* obj, ObjectBehaviourFunc fun);
	SceneObject* object;
	ObjectBehaviourFunc func;
};

class InputManager
{
public:
	InputManager();
	~InputManager();

	void bind(GLuint key_code, SceneObject* object, ObjectBehaviourFunc func);
	void unbind(GLuint key_code);
	void behave(GLuint key_code);

private:
	std::map<GLuint, ObjectBehaviour> bindings;
};

