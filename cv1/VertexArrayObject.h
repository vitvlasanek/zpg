#pragma once
#include <GL/glew.h>
#include "VertexBufferObject.h"
class VertexArrayObject
{
public:
	VertexArrayObject();
	~VertexArrayObject();
	void LinkVBO(VertexBufferObject& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	GLuint id;

	//void LinkVBO(VertexBufferObject& VBO, GLuint layout);
	void Bind();
	void Unbind();
	void Delete();
private:
};

