#include "DrawableObject.h"

DrawableObject::DrawableObject(const float* vertices, const int numVertices)
	: vbo(vertices, numVertices, GL_STATIC_DRAW)
{
	this->usedModel = vertices;
	this->modelSize = numVertices;
}

void DrawableObject::Initialize()
{

	vao.Bind();
	// Links VertexBufferObject to VertexArrayObject
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	vao.LinkVBO(vbo, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (GLvoid*)0);
	vao.LinkVBO(vbo, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	// Unbind all to prevent accidentally modifying them
	vao.Unbind();
	vbo.Unbind();
}

void DrawableObject::Translate(const glm::vec3& translation) {
	modelMatrix = glm::translate(modelMatrix, translation);
}

void DrawableObject::Rotate(const glm::vec3& rotation) {
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void DrawableObject::Scale(const glm::vec3& scale)
{
	modelMatrix = glm::scale(modelMatrix, scale);
}

void DrawableObject::Delete()
{
	vao.Delete();
	vbo.Delete();
}

void DrawableObject::Draw()
{
	vao.Bind();
	glDrawArrays(GL_TRIANGLES, 0, modelSize / (sizeof(GLfloat) * 6));
}
