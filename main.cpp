#define GLEW_STATIC
#include <GL/glew.h>
#include "ShProgram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
//using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Scene.h"
#include "Renderer.h"
#include "RenderableObject.h"
#include "FileModel.h"
#include "ConvexShape.h"
#include "ConvexShapeModel.h"
#include "Material.h"
#include "InputManager.h"

#include "PyramidModel.h"
#include "PrismModel.h"
#include "ArcModel.h"
#include "LatheModel.h"

const GLuint WIDTH = 800, HEIGHT = 600;
InputManager inputManager;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	inputManager.behave(key);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	if (glfwInit() != GL_TRUE) {
		std::cout << "GLFW initialization failed" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	

	try {
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - Kiwak", nullptr, nullptr);
		if (window == nullptr)
			throw std::exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw std::exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);
		glEnable(GL_DEPTH_TEST);

		ShProgram shaderProgram("kiwak.vert", "kiwak.frag");
		Renderer renderer(shaderProgram);
		Scene scene(renderer);

		scene.setTimeScale(0.001f);

		Environment& env = scene.getEnvironment();
		env.setAmbientLight(0.3f);




		Light& light = scene.getLight();
		light.setPosition(glm::vec3(-3.5f, 4.0f, 0.0f));
		light.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
		light.setPower(1.0f);

		Camera& camera = scene.getCamera();

		camera.setPosition(glm::vec3(-7.0f, 5.0f, 3.0f));
		camera.lookAt(glm::vec3(-7.0f, 5.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		camera.setProjection(glm::perspective(glm::radians(60.0f), (GLfloat)WIDTH/ (GLfloat)HEIGHT, 0.1f, 100.0f));


		// Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Texture metal_tex, sand_tex, metal2_tex;
		metal_tex.load("Textures/metal.png");
		sand_tex.load("Textures/sand.png");
		metal2_tex.load("Textures/metal3.png");

		Material sand;
		sand.setTexture(&sand_tex);
		sand.setTextureScale(glm::vec2(10.0f, 10.0f));
		sand.setSpecularLevel(0);

		Material metal;
		metal.setTexture(&metal_tex);
		metal.setSpecularLevel(0.8f);
		metal.setGlossiness(30);
		
		Material metal2;
		metal2.setTexture(&metal2_tex);
		metal2.setTextureScale(glm::vec2(0.5f, 0.5f));
		metal2.setSpecularLevel(0.6f);
		metal2.setGlossiness(10);



		RenderableObject* pumpjack = scene.addObject();
		pumpjack->translate(glm::vec3(0.0f, 0.0f, -1.0f));

		ConvexShape square(6);
		PrismModel strutModel(square, 0.65f, 0.1f, 2.25f);

		LatheModel drumModel(30, std::vector<glm::vec2>({

			glm::vec2(0.3f, 0.05f), glm::vec2(0.3f, 0.0f),
			glm::vec2(0.42f, 0.0f), glm::vec2(0.42f, 0.05f),
			glm::vec2(0.4f, 0.05f), glm::vec2(0.4f, 0.15f),
			glm::vec2(0.42f, 0.15f), glm::vec2(0.42f, 0.2f),
			glm::vec2(0.4f, 0.2f), glm::vec2(0.4f, 0.6f),
			glm::vec2(0.42f, 0.6f), glm::vec2(0.42f, 0.65f),
			glm::vec2(0.4f, 0.65f), glm::vec2(0.4f, 0.75f),
			glm::vec2(0.42f, 0.75f), glm::vec2(0.42f, 0.8f),
			glm::vec2(0.3f, 0.8f), glm::vec2(0.3f, 0.75f)
		}));


		ArcModel counterWeightModel(0.39f, 0.6f, 0.1f, glm::radians(360.0f), 20);

		ConvexShape baseBase(std::vector<glm::vec2>({
			glm::vec2(-1.5f, -1.5f), glm::vec2(-0.75f, -1.5f), glm::vec2(-0.5f, -1.75f), glm::vec2(0.5f, -1.75f),
			glm::vec2(0.75f, -1.5f), glm::vec2(1.5f, -1.5f), glm::vec2(1.5f, -0.75f), glm::vec2(1.25f, -0.5f),
			glm::vec2(1.25f, 0.5f), glm::vec2(1.5f, 0.75f), glm::vec2(1.5f, 1.5f), glm::vec2(0.75f, 1.5f),
			glm::vec2(0.5f, 1.75f), glm::vec2(-0.5f, 1.75f), glm::vec2(-0.75f, 1.5f), glm::vec2(-1.5f, 1.5f),
			glm::vec2(-1.5f, 0.75f), glm::vec2(-1.25f, 0.5f), glm::vec2(-1.25f, -0.5f), glm::vec2(-1.5f, -0.75f)}));
		PrismModel baseModel(baseBase, 2.0f, 2.0f, 0.1f);

		LatheModel armJointModel(15, std::vector<glm::vec2>({
			glm::vec2(0.01f, -0.2f), glm::vec2(0.05f, 0.04f),
			glm::vec2(0.07f, 0.04f), glm::vec2(0.07f, 0.0f),
			glm::vec2(0.1f, 0.0f), glm::vec2(0.1f, 0.25f),
			glm::vec2(0.07f, 0.25f), glm::vec2(0.07f, 0.21f),
			glm::vec2(0.05f, 0.21f), glm::vec2(0.01f, 0.45f)
		}));
		ConvexShape armBeamShape(15);
		PrismModel armBeamModel(armBeamShape, 0.15f, 0.15f, 4.5f, glm::vec3(0.0f, 2.25f, 0.0f));

		ConvexShape horseheadShape(std::vector<glm::vec2>({
			glm::vec2(3, -1) / 6.0f, glm::vec2(3, 1) / 6.0f, glm::vec2(2, 3) / 6.0f,
			glm::vec2(1, 4) / 6.0f, glm::vec2(-1, 5) / 6.0f, glm::vec2(-3, 3) / 6.0f,
			glm::vec2(-3, -3) / 6.0f, glm::vec2(-1, -5) / 6.0f, glm::vec2(1, -4) / 6.0f, 
			glm::vec2(2, -3) / 6.0f }));

		PrismModel horseheadModel1(horseheadShape, 0.6f, 0.6f, 0.05f);
		PrismModel horseheadModel2(horseheadShape, 0.55f, 0.55f, 0.212f);

		ConvexShape drumBaseShape(std::vector<glm::vec2>({
			glm::vec2(-1.0f, -0.75f), glm::vec2(1.0f, -0.75f),
			glm::vec2(0.75f, 1.0f), glm::vec2(-0.75f, 1.0f)
		}));

		PrismModel drumBaseModel(drumBaseShape, 0.6f, 0.6f, 0.55f);

		LatheModel barrelModel(20, std::vector<glm::vec2>({
			glm::vec2(0.25f, 0.05f), glm::vec2(0.25f, 0.0f),
			glm::vec2(0.3f, 0.0f), glm::vec2(0.3f, 0.05f), glm::vec2(0.25f, 0.05f),
			glm::vec2(0.25f, 0.30f), glm::vec2(0.3f, 0.30f), glm::vec2(0.3f, 0.35f),
			glm::vec2(0.25f, 0.35f), glm::vec2(0.25f, 0.6f), glm::vec2(0.3f, 0.6f),
			glm::vec2(0.3f, 0.65f), glm::vec2(0.25f, 0.65f), glm::vec2(0.25f, 0.6f)
			}));

		ConvexShape nutBase(6);
		PrismModel nutModel(nutBase, 0.03f, 0.03f, 0.05f);

		RenderableObject *active;
		RenderableObject *base;
		base = scene.addObject(pumpjack);
		base->setModel(&baseModel);
		base->setMaterial(&metal2);

		pumpjack->translate(glm::vec3(0.0f, 0.0f, 1.5f));

		
		RenderableObject *strut;

		strut = scene.addObject(&strutModel, &metal, pumpjack);
		strut->translate(glm::vec3(0.0f, 0.0f, -0.7f));

		RenderableObject *armJoint, *armBeam;
		armJoint = scene.addObject(&armJointModel, &metal, strut);
		armJoint->translate(glm::vec3(0.125f, 2.25f, 0.0f));
		armJoint->rotateZ(glm::radians(90.0f));

		armBeam = scene.addObject(&armBeamModel, &metal, armJoint);
		armBeam->translate(glm::vec3(0.12f, 0.125f, 0.0f));
		armBeam->rotateX(glm::radians(90.0f));
		armBeam->setAnimation([](SceneObject* obj)->void {
			obj->setRotationZ(glm::radians(sin(glm::radians(200*obj->getTime()+180.0f))*12.0f));
		});
		
		RenderableObject *horsehead;	
		horsehead = scene.addObject(armBeam);
		horsehead->translate(glm::vec3(-0.106f, 2.25f, -0.106f));
		horsehead->rotateX(glm::radians(90.0f));
		horsehead->rotateY(glm::radians(100.0f));
		RenderableObject *horseheadSide[2], *horseheadCenter;
		horseheadSide[0] = scene.addObject(&horseheadModel1, &metal, horsehead);
		horseheadSide[0]->translate(glm::vec3(0.0f, -0.05f, 0.0f));
		horseheadSide[1] = scene.addObject(&horseheadModel1, &metal, horsehead);
		horseheadSide[1]->translate(glm::vec3(0.0f, 0.212f, 0.0f));
		horseheadCenter = scene.addObject(&horseheadModel2, &metal, horsehead);
		

		RenderableObject *drumCore;
		RenderableObject *counterWeight1, *counterWeight2;
		drumCore = scene.addObject(&drumModel, &metal, pumpjack);

		drumCore->translate(glm::vec3(0.4f, 0.8f, 1.2f));
		drumCore->rotateZ(glm::radians(90.0f));

		drumCore->setAnimation([](SceneObject* obj)->void {
			obj->rotateY(glm::radians(0.2f));
		});

		RenderableObject *drumBase;
		drumBase = scene.addObject(&drumBaseModel, &metal, pumpjack);
		drumBase->translate(glm::vec3(0.3f, 0.4f, 1.2f));
		drumBase->rotateZ(glm::radians(90.0f));
		drumBase->rotateY(glm::radians(90.0f));

		RenderableObject *barrel[5];
		for (GLuint i = 0; i < 5; ++i) {
			barrel[i] = scene.addObject(&barrelModel, &metal);
		}
		barrel[0]->translate(glm::vec3(2.0f, 0.0f, 1.0f));
		barrel[1]->translate(glm::vec3(2.55f, 0.0f, 1.2f));
		barrel[2]->translate(glm::vec3(2.25f, 0.0f, 1.7f));
		barrel[3]->translate(glm::vec3(2.30f, 0.65f, 1.5f));
		barrel[4]->translate(glm::vec3(2.0f, 0.25f, -1.6f));
		barrel[4]->rotateX(glm::radians(90.0f));
		const GLuint NUT_NB = 6;
		RenderableObject *drumNut[NUT_NB * 2];
		for (GLuint i = 0; i < NUT_NB * 2; ++i) 
		{
			drumNut[i] = scene.addObject(&nutModel, &metal, drumCore);
		}

		for (GLuint i = 0; i < NUT_NB; ++i)
		{
			GLfloat step_angle = 2 * M_PI / (float)NUT_NB;
			drumNut[i]->translate(cylindrical(0.25f, 0.0f, i * step_angle));
			drumNut[i + NUT_NB]->translate(cylindrical(0.25f, 0.75f, i*step_angle));
		}

		counterWeight1 = scene.addObject(&counterWeightModel, &metal, drumCore);
		counterWeight1->translate(glm::vec3(0.0f, 0.05f, 0.0f));

		counterWeight2 = scene.addObject(&counterWeightModel, &metal, drumCore);
		counterWeight2->translate(glm::vec3(0.0f, 0.65f, 0.0f));


		RenderableObject *plane;
		ConvexShape planeShape(20);
		ConvexShapeModel planeModel(planeShape);

		plane = scene.addObject(&planeModel, &sand);

		plane->setPosition(glm::vec3(0.0, 0.0, 0.0));
		plane->setScale(glm::vec3(30, 30, 30));

		inputManager.bind(262, &camera ,[](SceneObject* obj)->void {
			obj->translate(glm::vec3(0.0f, 0.0f, -0.1f));
			obj->lookAt(obj->getPosition(), glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));
		});
		inputManager.bind(263, &camera, [](SceneObject* obj)->void {
			obj->translate(glm::vec3(0.0f, 0.0f, 0.1f));
			obj->lookAt(obj->getPosition(), glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));
		});
		inputManager.bind(83, &camera, [](SceneObject* obj)->void {
			obj->translate(glm::vec3(0.0f, - 0.1f, 0.0f));
			obj->lookAt(obj->getPosition(), glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));
		});
		inputManager.bind(87, &camera, [](SceneObject* obj)->void {
			obj->translate(glm::vec3(0.0f, 0.1f, 0.0f));
			obj->lookAt(obj->getPosition(), glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));
		});
		inputManager.bind(264, &camera, [](SceneObject* obj)->void {
			obj->translate(glm::vec3(0.1f, 0.0f, 0.0f));
			obj->lookAt(obj->getPosition(), glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));
		});
		inputManager.bind(265, &camera, [](SceneObject* obj)->void {
			obj->translate(glm::vec3(-0.1f, 0.0f, 0.0f));
			obj->lookAt(obj->getPosition(), glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));
		});

		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
			
			scene.draw();

			glfwSwapBuffers(window);
			
		}

	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}

	glfwTerminate();

	return 0;
}
