#include "Window.h"


Window::WindowBuilder::WindowBuilder(const char* title)
{
	this->title_ = title;
}

Window::WindowBuilder& Window::WindowBuilder::SetOpenGLVersion(int major, int minor)
{
	this->major_version_ = major;
	this->minor_version_ = minor;
	return *this;
}

Window::WindowBuilder& Window::WindowBuilder::SetFullscreen(bool useFullscreen)
{
	this->fullscreen_ = useFullscreen;
	return *this;
}

Window::WindowBuilder& Window::WindowBuilder::SetSize(int width, int height)
{
	this->width_ = width;
	this->height_ = height;
	return *this;
}

Window Window::WindowBuilder::Build()
{
	return Window(*this);
}


//WindowBuilder& WindowBuilder::SetOpenGLVersion(int major, int minor)
//{
//	major_version_ = major;
//	minor_version_ = minor;
//	return *this;
//}
//
//WindowBuilder& WindowBuilder::SetFullscreen(bool useFullscreen)
//{
//	fullscreen_ = useFullscreen;
//	return *this;
//}
//
//WindowBuilder& WindowBuilder::SetSize(int width, int height)
//{
//	width_ = width;
//	height_ = height;
//	return *this;
//}
//Window WindowBuilder::Build()
//{
//	return Window(this);
//}




