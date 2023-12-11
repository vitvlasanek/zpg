#pragma once
#include "Window.h"
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void Window::Run(GLuint shader_program, GLuint VAO)
{
	while (!glfwWindowShouldClose(window_)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window_);
	}
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(this->window_);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(this->window_);
}

void Window::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

Window::Window(const WindowBuilder& builder)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, builder.major_version_);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, builder.minor_version_);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window_ = glfwCreateWindow(
		builder.width_, 
		builder.height_,
		builder.title_,
		builder.fullscreen_ ? monitor : NULL,
		NULL
	);
	
	if (!this->window_) {
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(this->window_);
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

}

Window::~Window()
{
	glfwDestroyWindow(this->window_);
	glfwTerminate();
}
Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{

	this->window_ = glfwCreateWindow(width, height, title, monitor, share);
	
	
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glfwMakeContextCurrent(this->window_);
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	if (!glewInit())
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
}

void Window::SetWindow(GLFWwindow* window)
{
	this->window_ = window;
}

GLFWwindow* Window::GetWindow()
{
	return window_;
}

void Window::window_focus_callback(int focused)
{
	printf("window_focus_callback \n");
}

void Window::window_iconify_callback(int iconified)
{
	printf("window_iconify_callback \n");
}

void Window::window_size_callback(int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Window::GetInfo()
{
	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}
