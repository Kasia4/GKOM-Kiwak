#pragma once

#include <list>
#include <map>
#include <iostream>
#include "Renderer.h"
#include "RenderableObject.h"
#include "Camera.h"
#include "Light.h"
#include "Environment.h"

class Scene
{
public:
	Scene(Renderer& renderer);
	~Scene();

	RenderableObject* addObject(RenderableObject* parent = nullptr);
	RenderableObject* addObject(Model* model, Material* material, RenderableObject* parent = nullptr);
	void removeObject(SceneObject* object);
	void draw();

	

	Camera& getCamera();
	Light& getLight();
	Environment& getEnvironment();

	void setTimeScale(GLfloat scale);

private:
	std::list<RenderableObject*> objects;

	Renderer& renderer;
	Camera camera;
	Light light;
	Environment environment;
	GLfloat time;
	GLfloat time_scale;
};

