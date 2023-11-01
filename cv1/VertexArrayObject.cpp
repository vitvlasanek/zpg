#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &id); //generate the VAO

	//glEnableVertexAttribArray(0); //enable vertex attributes
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
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

