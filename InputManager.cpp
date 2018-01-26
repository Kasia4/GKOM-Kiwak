#include "InputManager.h"

ObjectBehaviour::ObjectBehaviour() {}

ObjectBehaviour::ObjectBehaviour(SceneObject* obj, ObjectBehaviourFunc fun)
	:object(obj)
	,func(fun)
{

}

void InputManager::bind(GLuint key_code, SceneObject* object, ObjectBehaviourFunc func)
{
	bindings.insert(std::pair<GLuint, ObjectBehaviour>(key_code, ObjectBehaviour(object, func)));
}

void InputManager::unbind(GLuint key_code)
{
	bindings.erase(key_code);
}

void InputManager::behave(GLuint key_code)
{
	if (!bindings.count(key_code))return;
	bindings[key_code].func(bindings[key_code].object);
}

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}
