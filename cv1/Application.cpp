#include "Application.h"
#include "tree.h"


Application::Application()
{
	win = nullptr;
	shader = nullptr;
}

int Application::Initialize()
{
	const unsigned int width = 800;
	const unsigned int height = 600;

	const GLfloat* usedModel = tree;
	const GLsizeiptr modelSize = sizeof(tree);

	const GLfloat* usedModel2 = plain;
	const GLsizeiptr modelSize2 = sizeof(plain);

	Window win = Window::WindowBuilder("zpg")
		.SetFullscreen(false)
		.SetOpenGLVersion(3, 3)
		.SetSize(width, height)
		.Build();

	// Generates Shader object using shaders defualt.vert and default.frag
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	Shader shaderProgram(&camera, "phong.vert", "phong.frag");

	camera.Attach(&shaderProgram);

	Model tree = Model(usedModel, modelSize);
	Model plain = Model(usedModel2, modelSize2);

	//DrawableObject dm = DrawableObject(&tree);

	DrawableObject * trees[10];

	for (int i = 0; i < 10; i++)
	{
		trees[i] = new DrawableObject(&tree);
		trees[i]->Initialize();
		trees[i]->Translate(glm::vec3(i, 0.0f, 0.0f));
		trees[i]->Attach(&shaderProgram);
		shaderProgram.objects.push_back(trees[i]);
	}



	DrawableObject dm2 = DrawableObject(&plain);
	dm2.Initialize();

	Light lights[1];
	lights[0].position = glm::vec3(1.0f, 2.0f, 2.0f);
	lights[0].color = glm::vec3(1.0f, 0.0f, 1.0f);
	lights[0].ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	lights[0].diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	lights[0].specular = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 objectColor(0.5f, 0.5f, 0.5f);


	dm2.Attach(&shaderProgram);
	shaderProgram.objects.push_back(&dm2);


	GLfloat rotation = 0.0f;
	double prevTime = glfwGetTime();
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(win.GetWindow())) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		shaderProgram.SetLights(lights, 1);
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);
		shaderProgram.Activate();

		camera.Inputs(win.GetWindow());
		shaderProgram.Update();

		glfwSwapBuffers(win.GetWindow());
		glfwPollEvents();
	}

	shaderProgram.Delete();
	return 0;
}

void Application::Run()
{
}

void Application::Delete()
{
	glfwTerminate();
}
