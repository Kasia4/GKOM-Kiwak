#include "RenderableObject.h"

using namespace std;


RenderableObject::RenderableObject(Renderer& renderer, SceneObject* parent)
	:SceneObject(parent)
	,renderer(renderer)
	,material(nullptr)
{

}

RenderableObject::RenderableObject(Renderer & renderer, Model * model, Material * material, SceneObject * parent)
	:SceneObject(parent)
	,renderer(renderer)
	,model(model)
	,material(material)
{

}


RenderableObject::~RenderableObject()
{
}

void RenderableObject::draw() const
{
	if (!model || !material) return;
	renderer.use(model->getVAO(), getGlobalTrans(), model->getIndicesCount()*INDEX_SIZE, material);
}

void RenderableObject::setModel(const Model * model)
{
	this->model = model;
}

const Model * RenderableObject::getModel() const
{
	return model;
}

void RenderableObject::setMaterial(const Material * mater)
{
	material = mater;
}

const Material * RenderableObject::getMaterial() const
{
	return material;
}

