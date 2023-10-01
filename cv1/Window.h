#pragma once
#include <GLFW/glfw3.h>
class Window
{
private:
	GLFWwindow* window;
public:
	Window() = default;
	Window(GLFWwindow* window);
	void SetWindow(GLFWwindow* window);
	GLFWwindow* GetWindow();
	void window_focus_callback(int focused);
	void window_iconify_callback(int iconified);
	void window_size_callback(int width, int height);
};

