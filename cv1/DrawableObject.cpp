#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model)
{
	this->model_ = model;
}

void DrawableObject::Initialize()
{
	this->model_->Initialize();
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
	this->model_->Delete();
}

void DrawableObject::Draw()
{
	model_->Bind();
	glDrawArrays(GL_TRIANGLES, 0, model_->GetNumVertices() / (sizeof(GLfloat) * 6));
}
