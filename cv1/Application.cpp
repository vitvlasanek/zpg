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
	const unsigned int width = 1280;
	const unsigned int height = 720;
	Scene* sc2 = new Scene("phong");


	Window* win  = Window::WindowBuilder("zpg")
		.SetFullscreen(false)
		.SetOpenGLVersion(3, 3)
		.SetSize(width, height)
		.SetScene(sc2)
		.Build();



	Shader* shader_def = new Shader("default");
	Shader* shader_lamb = new Shader("lambert");
	Shader* shader_ph = new Shader("phong");

	vector<DrawableObject*> drawableObjects;

	SkinnedModel* sphereModel2 = new SkinnedModel("model.obj");
	SkinnedModel* plane = new SkinnedModel("teren.obj");
	SkinnedModel* dome = new SkinnedModel("skydome.obj");
	SkinnedModel* tree = new SkinnedModel("tree.obj");



	DrawableObject* trees[10];

	Texture* t = new Texture("model.png");
	Texture* treeTexture = new Texture("tree.png");
	Texture* domeTexture = new Texture("skydome.png");

	Camera* cam = new Camera(1280, 720, glm::vec3(0.0f, 0.0f, 2.0f), win->GetWindow());
	sc2->SetCamera(cam);

	DrawableObject* loaded = new DrawableObject(sphereModel2, shader_ph);
	loaded->Initialize();
	loaded->SetTexture(t);

	DrawableObject* grass = new DrawableObject(plane, shader_lamb);
	DrawableObject* sd = new DrawableObject(dome, shader_def);
	sd->Initialize();
	sd->SetTexture(domeTexture);
	//sd->Scale(vec3(5));
	Texture* grassTexture = new Texture("grass.png");
	grass->Initialize();
 	grass->SetTexture(grassTexture);
	grass->SetColor(vec3(1));


	for (int i = 0; i < 10; i++)
	{
		int xOffset = rand() % 200;
		int yOffset = rand() % 200;
		int rotate = rand() % 90;
		trees[i] = new DrawableObject(tree, shader_ph);
		trees[i]->SetColor(vec3(1, 1, 1));
		trees[i]->Initialize();
		trees[i]->Scale(vec3(0.2f));
		trees[i]->Rotate(glm::vec3(0, rotate, 0));
		trees[i]->Translate(glm::vec3(xOffset - 100, 0, yOffset - 100));

		trees[i]->SetTexture(treeTexture);
		drawableObjects.push_back(trees[i]);
	}
	drawableObjects.push_back(loaded);
	drawableObjects.push_back(grass);
	//drawableObjects.push_back(sd);
	sc2->DomeObject_ = tuple<Shader*, DrawableObject*>(shader_def, sd);

	LightBase* lb = new LightBase();
	FlashLight* lb2 = new FlashLight();
	lb2->AttachToCamera(cam);

	lb->SetColor(vec3(1, 0, 0)).SetPosition(vec3(10,10,0));
	lb2->SetPosition(vec3(100, 100, 100));
	sc2->AddLights(lb);
	sc2->AddLights(lb2);

	sc2->AddModels(drawableObjects);
	sc2->Initialize();
	win->Run();
	delete(sc2);
}

void Application::Delete()
{
	glfwTerminate();
}
