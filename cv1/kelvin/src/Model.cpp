#include "Model.h"


Model::Model(const GLfloat* vertices, const GLsizeiptr numVertices) : vbo_(vertices, numVertices, GL_STATIC_DRAW)
{
	this->numVertices_ = numVertices;
	this->verticies_ = vertices;
}

void Model::Initialize()
{
	// Links VertexBufferObject to VertexArrayObject
	this->Bind();
	vao_.LinkVBO(vbo_, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (GLvoid*)0);
	vao_.LinkVBO(vbo_, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	// Unbind all to prevent accidentally modifying them

	this->Unbind();
}

void Model::Delete()
{
	vao_.Delete();
	vbo_.Delete();
}

void Model::Bind()
{
	vao_.Bind();
}

void Model::Unbind()
{
	vao_.Unbind();
	vbo_.Unbind();

}

GLsizeiptr Model::GetNumVertices()
{
	return this->numVertices_;
}

Model::~Model()
{
	this->Delete();
}
