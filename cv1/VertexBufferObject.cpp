#include "VertexBufferObject.h"


void VertexBufferObject::SetData(const GLvoid* data, GLsizeiptr size, GLenum usage)
{
	glGenBuffers(1, &id_);
	glBindBuffer(GL_ARRAY_BUFFER, this->id_);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBufferObject::SetData(vector<GLfloat> data, GLenum usage)
{
	glGenBuffers(1, &id_);
	glBindBuffer(GL_ARRAY_BUFFER, this->id_);
	glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(GLfloat), &data[0], usage);
}

void VertexBufferObject::SetData(vector<GLfloat> data)
{
	this->SetData(data, GL_STATIC_DRAW);
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