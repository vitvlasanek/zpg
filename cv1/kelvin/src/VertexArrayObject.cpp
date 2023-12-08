#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &id); 
}

VertexArrayObject::~VertexArrayObject()
{
	this->Delete();
}

void VertexArrayObject::LinkVBO(VertexBufferObject& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout); //enable vertex attributes
	VBO.Unbind();
}

void VertexArrayObject::Bind()
{
	glBindVertexArray(id); //bind the VAO
}

void VertexArrayObject::Unbind()
{
	glBindVertexArray(0); //bind the VAO
}

void VertexArrayObject::Delete()
{
	glDeleteVertexArrays(1, &id);
}

