#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <list>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"
#include "Model.h"
#include "SceneObject.h"
#include "Material.h"


class RenderableObject : public SceneObject
{

private:
	
	const Model* model;
	const Material* material;
	Renderer& renderer;
	

public:

	RenderableObject(Renderer& renderer, SceneObject* parent = nullptr);
	RenderableObject(Renderer& renderer, Model* model, Material* material, SceneObject* parent = nullptr);

	~RenderableObject();

	void draw() const;
	void setModel(const Model* model);
	const Model* getModel() const;
	
	void setMaterial(const Material* mater);
	const Material* getMaterial() const;
};

