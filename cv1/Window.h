#pragma once
#include <GLFW/glfw3.h>
#include "WindowBuilder.h"
class Window
{
private:
	GLFWwindow* window;
	static void error_callback(int error, const char* description);
	const char* title_;
	int width_ = 800;
	int height_ = 600;
	int major_version_ = 3;
	int minor_version_ = 3;
	bool fullscreen_ = false;
public:
	~Window();
	Window() = default;
	Window(GLFWwindow* window);
	Window(WindowBuilder* builder);
	Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	void SetWindow(GLFWwindow* window);
	GLFWwindow* GetWindow();
	void window_focus_callback(int focused);
	void window_iconify_callback(int iconified);
	void window_size_callback(int width, int height);




	void Initialize();
	void Run();
};

