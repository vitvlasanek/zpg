#include "Window.h"
#include <stdio.h>

Window::Window(GLFWwindow* window)
{
	this->SetWindow(window);
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
