#include "Scene.h"


Scene::Scene()
{
	const unsigned int width = 800;
	const unsigned int height = 600;
	win = Window::WindowBuilder("zpg")
		.SetFullscreen(false)
		.SetOpenGLVersion(3, 3)
		.SetSize(width, height)
		.Build();
	//win = &window;

	this->cam_ = new Camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	this->shader = new Shader(this->cam_, "phong.vert", "phong.frag");
}

int Scene::Initialize()
{

	const GLfloat* usedModel = tree;
	const GLsizeiptr modelSize = sizeof(tree);

	const GLfloat* usedModel2 = plain;
	const GLsizeiptr modelSize2 = sizeof(plain);


	// Generates Shader object using shaders defualt.vert and default.frag

	this->cam_->Attach(shader);

	//Model tree = Model(usedModel, modelSize);
	//Model plain = Model(usedModel2, modelSize2);

	//DrawableObject dm = DrawableObject(&tree);

	//DrawableObject* trees[10];


	//for (int i = 0; i < 10; i++)
	//{
	//	int xOffset = rand() % 20;
	//	int yOffset = rand() % 20;
	//	trees[i] = new DrawableObject(&tree);
	//	trees[i]->color = vec3(0, 0, 1.0f);
	//	trees[i]->Initialize();
	//	trees[i]->Translate(glm::vec3(xOffset - 10, 0, yOffset - 10));
	//	trees[i]->Attach(this->shader);
	//	shader->objects.push_back(trees[i]);
	//}



	//DrawableObject dm2 = DrawableObject(&plain);
	//dm2.Initialize();
	//dm2.Scale(glm::vec3(10));

	Light lights[1];
	lights[0].position = glm::vec3(1.0f, 2.0f, 2.0f);
	lights[0].color = glm::vec3(1.0f, 0.0f, 1.0f);
	lights[0].ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	lights[0].diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	lights[0].specular = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 objectColor(0.5f, 0.5f, 0.5f);


	//dm2.Attach(shader);
	//shader->objects.push_back(&dm2);

	for (int i = 0; i < drawableObjects_.size(); i++)
	{
		drawableObjects_[i]->Attach(this->shader);
		this->shader->objects.push_back(drawableObjects_[i]);
	}


	GLfloat rotation = 0.0f;
	double prevTime = glfwGetTime();
	glEnable(GL_DEPTH_TEST);

	while (!win->ShouldClose()) 
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		shader->SetLights(lights, 1);
		cam_->UpdateMatrix(45.0f, 0.1f, 100.0f);
		shader->Activate();

		cam_->Inputs(win->GetWindow());
		shader->Update();

		glfwSwapBuffers(win->GetWindow());
		glfwPollEvents();
	}

	shader->Delete();
	return 0;
}

void Scene::Run()
{
}

void Scene::Delete()
{
	glfwTerminate();
}

void Scene::SetModels(vector<DrawableObject*> drawableObjects)
{
	this->drawableObjects_ = drawableObjects;
}

void Scene::AddModels(vector<DrawableObject*> drawableObjects)
{
	for (int i = 0; i < drawableObjects.size(); i++)
	{
		this->drawableObjects_.push_back(drawableObjects[i]);
	}
}

void Scene::SetCamera(Camera* cam)
{
	this->cam_ = cam;
	this->shader = new Shader(this->cam_, "phong.vert", "phong.frag");
}


