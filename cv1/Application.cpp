#include "Application.h"
#include "SOIL.h"

Application::Application()
{
}

void Application::Initialize(int version)
{
	version_ = version;
}

void Application::Run()
{

	Scene* sc2 = new Scene("phong");

	SkinnedModel* sphereModel = new SkinnedModel(plain, sizeof(plain));

	vector<DrawableObject*> drawableObjects;
	DrawableObject* spheres[4];
	GLuint textureID = SOIL_load_OGL_texture(
		"wooden_fence.png",  // Replace with the path to your texture file
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	for (int i = 0; i < 4; i++)
	{
		int ope = i < 2 ? -1 : 1;
		ope *= 2;
		spheres[i] = new DrawableObject(sphereModel, sc2->shaders_["phong"]);
		spheres[i]->SetColor(vec3(i % 2, (i * 2) % 2, (i + 3) % 2));
		spheres[i]->Initialize();
		spheres[i]->Translate(glm::vec3(i % 2 * ope, 0, (i + 1) % 2 * ope));
		spheres[i]->Rotate(glm::vec3(45, 45, 45));

		spheres[i]->SetTexture(&textureID);
		drawableObjects.push_back(spheres[i]);
	}

	Light lights[1];
	lights[0].position = glm::vec3(1.0f, 0.1f, 0.1f);
	lights[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
	lights[0].ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	lights[0].diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	lights[0].specular = glm::vec3(1.0f, 1.0f, 1.0f);

	sc2->SetLights(lights, 1);
	LightBase* lb = new LightBase(sc2->shaders_["phong"]);
	sc2->AddLights(lb);

	sc2->AddModels(drawableObjects);
	sc2->Initialize();
	delete(sc2);

	//if (version_ == 1)
	//{
	//	Scene* sc1 = new Scene("phong");
	//	const GLfloat* usedModel2 = plain;
	//	const GLsizeiptr modelSize2 = sizeof(plain);
	//	const GLfloat* usedModel = tree;
	//	const GLsizeiptr modelSize = sizeof(tree);

	//	//Model* plain = new  Model(usedModel2, modelSize2);
	//	Model* treeModel = new SkinnedModel("tree.obj");
	//	//DrawableObject* dm2 = new DrawableObject(plain);

	//	//Model* bush = new Model(bushes, sizeof(bushes));

	//	//dm2->Initialize();
	//	//dm2->Scale(glm::vec3(10));
	//	//dm2->color = vec3(0.5f, 0.5f, 0);
	//	vector<DrawableObject*> drawableObjects;
	//	
	//	DrawableObject* trees[2];

	//	GLuint textureID = SOIL_load_OGL_texture("tree.png",
	//		SOIL_LOAD_AUTO,
	//		SOIL_CREATE_NEW_ID,
	//		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	//	);

	//	for (int i = 0; i < 2; i++)
	//	{
	//		int xOffset = rand() % 20;
	//		int yOffset = rand() % 20;
	//		trees[i] = new DrawableObject(treeModel);
	//		trees[i]->color_ = vec3(0, 0, 1.0f);

	//		trees[i]->Initialize();
	//		trees[i]->SetTexture(&textureID);
	//		trees[i]->Translate(glm::vec3(xOffset - 10, 0, yOffset - 10));
	//		drawableObjects.push_back(trees[i]);
	//	}

	//	//for (int i = 0; i < 30; i++)
	//	//{
	//	//	int xOffset = rand() % 20;
	//	//	int yOffset = rand() % 20;
	//	//	DrawableObject* b = new DrawableObject(bush);
	//	//	b->color = vec3(0, 1, 0);
	//	//	b->Initialize();

	//	//	TransformationComponent * t = new Translation(glm::vec3(xOffset - 10, 0, yOffset - 10));
	//	//	Transformation* tran = new Transformation();
	//	//	tran->AddTransformation(t);

	//	//	b->Transform(tran);
	//	//	b->Scale(vec3(5));
	//	//	drawableObjects.push_back(b);
	//	//}



	//	Light lights[2];
	//	lights[0].position = glm::vec3(0.0f, 3.0f, 0.0f);
	//	lights[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
	//	lights[0].ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	//	lights[0].diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	//	lights[0].specular = glm::vec3(1.0f, 1.0f, 1.0f);

	//	lights[1].position = glm::vec3(10.0f, 1.0f, 5.0f);
	//	lights[1].color = glm::vec3(0.8f, 0.8f, 0.8f);
	//	lights[1].ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	//	lights[1].diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	//	lights[1].specular = glm::vec3(1.0f, 1.0f, 1.0f);

	//	sc1->SetLights(lights, 2);

	//	//drawableObjects.push_back(dm2);
	//	sc1->AddModels(drawableObjects);
	//	sc1->Initialize();
	//	delete(sc1);

	//}
	//else if (version_ == 2)
	//{
	//	Scene* sc2 = new Scene();

	//	SkinnedModel* sphereModel = new SkinnedModel(plain, sizeof(plain));

	//	vector<DrawableObject*> drawableObjects;
	//	DrawableObject* spheres[4];
	//	GLuint textureID = SOIL_load_OGL_texture(
	//		"wooden_fence.png",  // Replace with the path to your texture file
	//		SOIL_LOAD_AUTO,
	//		SOIL_CREATE_NEW_ID,
	//		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	//	);

	//	for (int i = 0; i < 4; i++)
	//	{
	//		int ope = i < 2 ? -1 : 1;
	//		ope *= 2;
	//		spheres[i] = new DrawableObject(sphereModel);
	//		spheres[i]->color_ = vec3(i%2, (i*2)%2, (i+3)%2);
	//		spheres[i]->Initialize();
	//		spheres[i]->Translate(glm::vec3(i % 2 * ope, 0, (i + 1) % 2 * ope));
	//		spheres[i]->Rotate(glm::vec3(45, 45, 45));

	//		spheres[i]->SetTexture(&textureID);
	//		drawableObjects.push_back(spheres[i]);
	//	}

	//	Light lights[1];
	//	lights[0].position = glm::vec3(1.0f, 0.1f, 0.1f);
	//	lights[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
	//	lights[0].ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	//	lights[0].diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	//	lights[0].specular = glm::vec3(1.0f, 1.0f, 1.0f);

	//	sc2->SetLights(lights, 1);

	//	sc2->AddModels(drawableObjects);
	//	sc2->Initialize();
	//	delete(sc2);
	//}
	//else if (version_ == 3)
	//{
	//	Scene* sc1 = new Scene();
	//	const GLfloat* usedModel2 = plain;
	//	const GLsizeiptr modelSize2 = sizeof(plain);
	//	const GLfloat* usedModel = tree;
	//	const GLsizeiptr modelSize = sizeof(tree);


	//	Model* treeModel = new Model(usedModel, modelSize);
	//	Model* plain = new  Model(usedModel2, modelSize2);
	//	DrawableObject* dm2 = new DrawableObject(plain);

	//	Model* bush = new Model(bushes, sizeof(bushes));

	//	dm2->Initialize();
	//	dm2->Scale(glm::vec3(10));
	//	dm2->color_ = vec3(0.5f, 0.5f, 0);
	//	vector<DrawableObject*> drawableObjects;

	//	DrawableObject* trees[10];

	//	for (int i = 0; i < 10; i++)
	//	{
	//		int xOffset = rand() % 20;
	//		int yOffset = rand() % 20;
	//		trees[i] = new DrawableObject(treeModel);
	//		trees[i]->color_ = vec3(0, 0, 1.0f);

	//		//trees[i]->SetTexture(&textureID);
	//		trees[i]->Initialize();
	//		trees[i]->Translate(glm::vec3(xOffset - 10, 0, yOffset - 10));
	//		drawableObjects.push_back(trees[i]);
	//	}
	//	drawableObjects.push_back(dm2);

	//	for (int i = 0; i < 30; i++)
	//	{
	//		int xOffset = rand() % 20;
	//		int yOffset = rand() % 20;
	//		DrawableObject* b = new DrawableObject(bush);
	//		b->color_ = vec3(0, 1, 0);
	//		b->Initialize();

	//		TransformationComponent * t = new Translation(glm::vec3(xOffset - 10, 0, yOffset - 10));
	//		Transformation* tran = new Transformation();
	//		tran->AddTransformation(t);

	//		b->Transform(tran);
	//		b->Scale(vec3(5));
	//		drawableObjects.push_back(b);
	//	}


	//	Light lights[4];
	//	lights[0].position = glm::vec3(0.0f, 3.0f, 0.0f);
	//	lights[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
	//	lights[0].ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	//	lights[0].diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	//	lights[0].specular = glm::vec3(1.0f, 1.0f, 1.0f);

	//	lights[1].position = glm::vec3(10.0f, 8.0f, 5.0f);
	//	lights[1].color = glm::vec3(0.8f, 0.8f, 0.0f);
	//	lights[1].ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	//	lights[1].diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	//	lights[1].specular = glm::vec3(1.0f, 1.0f, 1.0f);

	//	lights[2].position = glm::vec3(10.0f, 1.0f, 5.0f);
	//	lights[2].color = glm::vec3(0.8f, 0.8f, 0.8f);
	//	lights[2].ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	//	lights[2].diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	//	lights[2].specular = glm::vec3(1.0f, 1.0f, 1.0f);

	//	lights[3].position = glm::vec3(1.0f, 8.0f, 5.0f);
	//	lights[3].color = glm::vec3(0.8f, 0.8f, 0.8f);
	//	lights[3].ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	//	lights[3].diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	//	lights[3].specular = glm::vec3(1.0f, 1.0f, 1.0f);

	//	sc1->SetLights(lights, 2);

	//	//drawableObjects.push_back(dm2);
	//	sc1->AddModels(drawableObjects);
	//	sc1->Initialize();
	//	delete(sc1);

	//	}
}

void Application::Delete()
{
	glfwTerminate();
}
