#include "Window.h"
#include <stdio.h>
#include <stdlib.h>

void Window::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

Window::~Window()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

Window::Window(GLFWwindow* window)
{
	this->SetWindow(window);
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Window::Window(WindowBuilder* builder)
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	this->window = glfwCreateWindow(
		builder->width_, 
		builder->height_,
		builder->title_,
		builder->fullscreen_ ? monitor : NULL,
		NULL
	);

	if (!this->window) {
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{

	this->window = glfwCreateWindow(width, height, title, monitor, share);
	
	
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::SetWindow(GLFWwindow* window)
{
	this->window = window;
}

GLFWwindow* Window::GetWindow()
{
	return window;
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
