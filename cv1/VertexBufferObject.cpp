#include "VertexBufferObject.h"


VertexBufferObject::VertexBufferObject(const GLvoid* data, GLsizeiptr size, GLenum usage)
{
	glGenBuffers(1, &id_);
	glBindBuffer(GL_ARRAY_BUFFER, this->id_);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &id_);
}

void VertexBufferObject::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->id_);
}

void VertexBufferObject::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::Delete()
{
	glDeleteBuffers(1, &id_);
}
1