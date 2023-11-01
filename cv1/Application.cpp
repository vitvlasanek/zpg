#include "Application.h"

Application::Application()
{
	win = nullptr;
	shader = nullptr;
}

int Application::Initialize()
{
	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};


	Window wn = Window::WindowBuilder("zpg")
			.SetFullscreen(false)
			.SetOpenGLVersion(3, 3)
			.SetSize(800, 600)
			.Build();
	win = &wn;

	// Generates Vertex Array Object and binds it

	VertexArrayObject * vao{};
	vao->Bind();

	// Generates Vertex Buffer Object and links it to vertices
	vbo = new VertexBufferObject(vertices, sizeof(vertices), GL_STATIC_DRAW);
	// Generates Element Buffer Object and links it to indices

	// Links VertexBufferObject to VertexArrayObject
	vao->LinkVBO(*vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	vao->Unbind();
	vbo->Unbind();


    return 0;
}

void Application::CreateShaders()
{
	Shader shaderProgram(nullptr, "default.vert", "default.frag");
	shader = &shaderProgram;
}

void Application::CreateModels()
{
}

void Application::Run()
{
}

void Application::Delete()
{
	vao->Delete();
	vbo->Delete();
	shader->Delete();
	glfwTerminate();
}
