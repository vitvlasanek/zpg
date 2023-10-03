#pragma once
#include<GL/glew.h>
class VertexArrayObject
{
public:
	VertexArrayObject();
	~VertexArrayObject();
	GLuint GetVAO();
private:
	GLuint vao_;
};

