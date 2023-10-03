#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include "WindowBuilder.h"


class Window
{
public:
	class WindowBuilder {
	public:
		WindowBuilder(const char* title);
		WindowBuilder& SetOpenGLVersion(int major, int minor);
		WindowBuilder& SetFullscreen(bool useFullscreen);
		WindowBuilder& SetSize(int width, int height);
		Window Build();
	private:
		const char* title_;
		int width_ = 800;
		int height_ = 600;
		int major_version_ = 3;
		int minor_version_ = 3;
		bool fullscreen_ = false;

		friend class Window;
	};


	Window(const WindowBuilder& builder);
	~Window();
	Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	void SetWindow(GLFWwindow* window);
	GLFWwindow* GetWindow();
	void window_focus_callback(int focused);
	void window_iconify_callback(int iconified);
	void window_size_callback(int width, int height);
	void GetInfo();
	void Run(GLuint shader_program, GLuint VAO);

private:
	GLFWwindow* window_;
	static void error_callback(int error, const char* description);
};

