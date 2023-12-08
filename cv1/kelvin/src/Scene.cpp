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
	this->cam_->Attach(shader);

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

		shader->SetLights(this->lights_, numLights_);
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

void Scene::SetLights(Light* lights, int numlights)
{
	this->lights_ = lights;
	this->numLights_ = numlights;
}


