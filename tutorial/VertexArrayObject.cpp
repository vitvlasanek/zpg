#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	//Vertex Array Object (VAO)
	vao_ = 0;
	glGenVertexArrays(1, &vao_); //generate the VAO
	glBindVertexArray(vao_); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &vao_);
}

GLuint VertexArrayObject::GetVAO()
{
	return this->vao_;
}
