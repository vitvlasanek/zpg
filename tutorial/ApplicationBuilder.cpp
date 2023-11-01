#include "ApplicationBuilder.h"
#include "Window.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include <stdlib.h>

ApplicationBuilder& ApplicationBuilder::Initialize()
{

	const float b[] = {
	 -.5f, -.5f, .5f,   1, 1, 0,
	 -.5f, .5f, .5f,  1, 0, 0,
	   .5f, .5f, .5f,  0, 0, 0,
	   .5f, -.5f, .5f,  0, 1, 0 };

	float points[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
	};
	Window win = Window::WindowBuilder("ZPG")
		.SetOpenGLVersion(3, 3)
		.SetSize(800, 600)
		.Build();


	win.GetInfo();

	this->window_ = win.GetWindow();

	VertexBufferObject* vbo = new VertexBufferObject();
	vbo->Bind(sizeof(points), points, GL_STATIC_DRAW);

	VertexArrayObject* vao = new VertexArrayObject();

	this->VAO_ = vao->GetVAO();
	return *this;
}

ApplicationBuilder& ApplicationBuilder::CreateShaders()
{

	VertexShader vso = VertexShader();
	GLuint vertexShader = vso.GetShader();

	FragmentShader fso = FragmentShader();
	GLuint fragmentShader = fso.GetShader();

	this->shaderProgram_ = glCreateProgram();

	vso.AttachShader(&this->shaderProgram_);
	fso.AttachShader(&this->shaderProgram_);

	glLinkProgram(this->shaderProgram_);
	return *this;
}

ApplicationBuilder& ApplicationBuilder::CreateModels()
{
	// TODO: insert return statement here
	return *this;
}

void ApplicationBuilder::Run()
{

	while (!glfwWindowShouldClose(this->window_)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(this->shaderProgram_);
		glBindVertexArray(this->VAO_);
		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(this->window_);
	}
}



void ApplicationBuilder::window_focus_callback(int focused)
{
	printf("window_focus_callback \n");
}

void ApplicationBuilder::window_iconify_callback(int iconified)
{
	printf("window_iconify_callback \n");
}

void ApplicationBuilder::window_size_callback(int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}
