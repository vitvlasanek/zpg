#include "WindowBuilder.h"

WindowBuilder::WindowBuilder(const char* title)
{
	this->title_ = title;
}

WindowBuilder& WindowBuilder::SetOpenGLVersion(int major, int minor)
{
	major_version_ = major;
	minor_version_ = minor;
	return *this;
}

WindowBuilder& WindowBuilder::SetFullscreen(bool useFullscreen)
{
	fullscreen_ = useFullscreen;
	return *this;
}

WindowBuilder& WindowBuilder::SetSize(int width, int height)
{
	width_ = width;
	height_ = height;
	return *this;
}

Window WindowBuilder::Build()
{
	return Window();
}




