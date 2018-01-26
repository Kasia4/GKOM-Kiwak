#include "Scene.h"

Scene::Scene(Renderer& renderer)
	:renderer(renderer)
	, time(0)
{

}


Scene::~Scene()
{
}

RenderableObject * Scene::addObject(RenderableObject * parent)
{
	RenderableObject* new_object = new RenderableObject(renderer, parent);
	objects.push_back(new_object);
	new_object->setTimer(&time);
	return new_object;
}

RenderableObject * Scene::addObject(Model * model, Material * material, RenderableObject * parent)
{
	RenderableObject* new_object = new RenderableObject(renderer, model, material, parent);
	objects.push_back(new_object);
	new_object->setTimer(&time);
	return new_object;
}

void Scene::removeObject(SceneObject * object)
{
}

void Scene::draw()
{
	time += time_scale;
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera.update();
	renderer.setViewMatrix(camera.getOrientationMatrix());
	renderer.setProjectionMatrix(camera.getProjection());
	renderer.setLight(light);
	renderer.setEnvironment(environment);
	for (RenderableObject* obj : objects) {
		obj->update();
		obj->draw();
	}
	light.update();
	camera.update();
	
	
}

Camera & Scene::getCamera()
{
	return camera;
}

Light & Scene::getLight()
{
	return light;
}

Environment & Scene::getEnvironment()
{
	return environment;
}

void Scene::setTimeScale(GLfloat scale)
{
	time_scale = scale;
}

