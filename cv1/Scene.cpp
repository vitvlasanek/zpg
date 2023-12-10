#include "Scene.h"


Scene::Scene(std::string shader_type)
{
	const unsigned int width = 1280;
	const unsigned int height = 720;
	win = Window::WindowBuilder("zpg")
		.SetFullscreen(false)
		.SetOpenGLVersion(3, 3)
		.SetSize(width, height)
		.Build();
	//win = &window;

	const auto s = new Shader((shader_type + ".vert").c_str(), (shader_type + ".frag").c_str());
	this->shaders_[shader_type] = s;
	this->cam_ = new Camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f), this->shaders_[shader_type]);
}

int Scene::Initialize()
{
	this->shader = this->shaders_["phong"];
	this->cam_->Attach(this->shader);

	for (int i = 0; i < drawableObjects_.size(); i++)
	{
		drawableObjects_[i]->Attach(this->shader);
	}

	GLfloat rotation = 0.0f;
	double prevTime = glfwGetTime();
	glEnable(GL_DEPTH_TEST);

	while (!win->ShouldClose())
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		this->DrawLights();


		cam_->UpdateMatrix(45.0f, 0.1f, 100.0f);
		shader->Activate();

		cam_->Inputs(win->GetWindow());
		for (int i = 0; i < drawableObjects_.size(); i++)
		{
			drawableObjects_[i]->Draw();
		}
		cam_->UpdateUniforms();
		//shader->Update();

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


#pragma region Models
Scene& Scene::SetModels(vector<DrawableObject*> drawableObjects)
{
	this->drawableObjects_ = drawableObjects;
	return *this;
}

Scene& Scene::AddModels(vector<DrawableObject*> drawableObjects)
{
	for (int i = 0; i < drawableObjects.size(); i++)
	{
		this->drawableObjects_.push_back(drawableObjects[i]);
	}
	return *this;
}

Scene& Scene::AddModels(DrawableObject* drawableObject)
{
	this->drawableObjects_.push_back(drawableObject);
	return *this;
}

void Scene::DrawModels()
{
	for (int i = 0; i < this->drawableObjects_.size(); i++)
	{
		drawableObjects_[i]->Draw();
	}
}
#pragma endregion

#pragma region Lights
Scene& Scene::SetLights(vector<LightBase*> lights)
{
	this->lightsVector_ = lights;
	return *this;
}

Scene& Scene::AddLights(vector<LightBase*> lights)
{
	for (int i = 0; i < lights.size(); i++)
	{
		this->lightsVector_.push_back(lights.at(i));
	}
	return *this;
}

Scene& Scene::AddLights(LightBase* light)
{
	this->lightsVector_.push_back(light);
	return *this;
}

void Scene::DrawLights()
{
	for (int i = 0; i < this->lightsVector_.size(); i++)
	{
		this->lightsVector_[i]->Render(shader, i);
	}
	shader->LightsCount(lightsVector_.size());
}
#pragma endregion

Scene& Scene::SetShaders(map<string, Shader*> shaders)
{
	this->shaders_ = shaders;
	return *this;
}

Scene& Scene::AddShaders(vector<Shader*> shaders)
{
	return *this;
}


Scene& Scene::SetCamera(Camera* cam)
{
	this->cam_ = cam;
	this->shader = new Shader(this->cam_, "phong.vert", "phong.frag");
	return *this;
}

Scene& Scene::SetLights(Light* lights, int numlights)
{
	this->lights_ = lights;
	this->numLights_ = numlights;
	return *this;
}



