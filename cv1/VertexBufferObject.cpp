#include "VertexBufferObject.h"


VertexBufferObject::VertexBufferObject(const GLvoid* data, GLsizeiptr size, GLenum usage)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, this->id);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &id);
}

void VertexBufferObject::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VertexBufferObject::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::Delete()
{
	glDeleteBuffers(1, &id);
}
