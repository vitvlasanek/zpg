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

	if (version_ == 1)
	{
		Scene* sc1 = new Scene();
		const GLfloat* usedModel2 = plain;
		const GLsizeiptr modelSize2 = sizeof(plain);
		const GLfloat* usedModel = tree;
		const GLsizeiptr modelSize = sizeof(tree);

		//Model* plain = new  Model(usedModel2, modelSize2);
		Model* treeModel = new SkinnedModel("skydome.obj");
		//DrawableObject* dm2 = new DrawableObject(plain);

		//Model* bush = new Model(bushes, sizeof(bushes));

		//dm2->Initialize();
		//dm2->Scale(glm::vec3(10));
		//dm2->color = vec3(0.5f, 0.5f, 0);
		vector<DrawableObject*> drawableObjects;
		
		DrawableObject* trees[2];

		GLuint textureID = SOIL_load_OGL_texture("skydome.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
		);

		for (int i = 0; i < 2; i++)
		{
			int xOffset = rand() % 20;
			int yOffset = rand() % 20;
			trees[i] = new DrawableObject(treeModel);
			trees[i]->color = vec3(0, 0, 1.0f);

			//trees[i]->SetTexture(&textureID);
			trees[i]->Initialize();
			trees[i]->Translate(glm::vec3(xOffset - 10, 0, yOffset - 10));
			drawableObjects.push_back(trees[i]);
		}

		//for (int i = 0; i < 30; i++)
		//{
		//	int xOffset = rand() % 20;
		//	int yOffset = rand() % 20;
		//	DrawableObject* b = new DrawableObject(bush);
		//	b->color = vec3(0, 1, 0);
		//	b->Initialize();

		//	TransformationComponent * t = new Translation(glm::vec3(xOffset - 10, 0, yOffset - 10));
		//	Transformation* tran = new Transformation();
		//	tran->AddTransformation(t);

		//	b->Transform(tran);
		//	b->Scale(vec3(5));
		//	drawableObjects.push_back(b);
		//}



		Light lights[2];
		lights[0].position = glm::vec3(0.0f, 3.0f, 0.0f);
		lights[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
		lights[0].ambient = glm::vec3(0.0f, 0.0f, 0.0f);
		lights[0].diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		lights[0].specular = glm::vec3(1.0f, 1.0f, 1.0f);

		lights[1].position = glm::vec3(10.0f, 1.0f, 5.0f);
		lights[1].color = glm::vec3(0.8f, 0.8f, 0.8f);
		lights[1].ambient = glm::vec3(0.1f, 0.1f, 0.1f);
		lights[1].diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		lights[1].specular = glm::vec3(1.0f, 1.0f, 1.0f);

		sc1->SetLights(lights, 2);

		//drawableObjects.push_back(dm2);
		sc1->AddModels(drawableObjects);
		sc1->Initialize();
		delete(sc1);

	}
	else if (version_ == 2)
	{
		Scene* sc2 = new Scene();

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
			spheres[i] = new DrawableObject(sphereModel);
			spheres[i]->color = vec3(i%2, (i*2)%2, (i+3)%2);
			spheres[i]->Initialize();
			spheres[i]->Translate(glm::vec3(i % 2 * ope, 0, (i + 1) % 2 * ope));
			spheres[i]->SetTexture(&textureID);
			drawableObjects.push_back(spheres[i]);
		}

		Light lights[1];
		lights[0].position = glm::vec3(0.0f, 0.0f, 0.0f);
		lights[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
		lights[0].ambient = glm::vec3(0.2f, 0.2f, 0.2f);
		lights[0].diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		lights[0].specular = glm::vec3(1.0f, 1.0f, 1.0f);

		sc2->SetLights(lights, 1);

		sc2->AddModels(drawableObjects);
		sc2->Initialize();
		delete(sc2);
	}
}

void Application::Delete()
{
	glfwTerminate();
}
