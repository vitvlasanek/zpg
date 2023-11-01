#pragma once
#include <GL/glew.h>

class VertexBufferObject
{
public:
	VertexBufferObject();
	~VertexBufferObject();
	void Bind(GLsizeiptr size, const GLvoid* data, GLenum usage);
private:
	GLuint vbo_;
};