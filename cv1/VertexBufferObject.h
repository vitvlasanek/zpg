#pragma once
#include <GL/glew.h>

class VertexBufferObject
{
public:
	VertexBufferObject(const GLvoid* data, GLsizeiptr size, GLenum usage);
	~VertexBufferObject();
	void Bind();
	
	void Unbind();
	void Delete();
private:
	GLuint id_;
};