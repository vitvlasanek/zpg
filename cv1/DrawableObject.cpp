#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model)
{
	this->model_ = model;
	this->modelMatrix = mat4(1.0f);
	this->color = vec3(1.0f, 0, 0.5f);
}

void DrawableObject::Initialize()
{
	this->model_->Initialize();
}

void DrawableObject::Translate(const vec3& translation) {
	modelMatrix = translate(modelMatrix, translation);
	this->Notify();
}

void DrawableObject::Rotate(const vec3& rotation) {
	modelMatrix = rotate(modelMatrix, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = rotate(modelMatrix, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = rotate(modelMatrix, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
	this->Notify();
}

void DrawableObject::Scale(const vec3& scale)
{
	modelMatrix = glm::scale(modelMatrix, scale);
	this->Notify();
}

void DrawableObject::Delete()
{
	this->model_->Delete();
}

void DrawableObject::SetTexture(GLuint* texture)
{
	this->texture_ = texture;
}

mat4 DrawableObject::GetModelMatrix() {
	return this->modelMatrix;
}

void DrawableObject::Draw()
{
	model_->Bind();
	glDrawArrays(GL_TRIANGLES, 0, model_->GetNumVertices() / (sizeof(GLfloat) * 6));
	model_->Unbind();
}

void DrawableObject::Transform(Transformation* transformation)
{
	this->modelMatrix *= transformation->GetMatrix();
}

