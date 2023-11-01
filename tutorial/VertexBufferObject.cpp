#include "VertexBufferObject.h"


VertexBufferObject::VertexBufferObject()
{
	vbo_ = 0;
	glGenBuffers(1, &vbo_);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &vbo_);
}

void VertexBufferObject::Bind(GLsizeiptr size, const GLvoid* data, GLenum usage)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}
