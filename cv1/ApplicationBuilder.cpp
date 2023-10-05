#include "ApplicationBuilder.h"
#include "Window.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include <stdlib.h>

ApplicationBuilder& ApplicationBuilder::Initialize()
{

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
	return * this;
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
