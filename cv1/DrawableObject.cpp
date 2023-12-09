#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, Shader * shader)
{
	this->model_ = model;
	this->modelMatrix_ = mat4(1.0f);
	this->color_ = vec3(1.0f, 0, 0.5f);
	this->shader_ = shader;
}

void DrawableObject::Initialize()
{
	this->model_->Initialize();
}

void DrawableObject::Translate(const vec3& translation) {
	modelMatrix_ = translate(modelMatrix_, translation);
	this->Notify();
}

void DrawableObject::Rotate(const vec3& rotation) {
	modelMatrix_ = rotate(modelMatrix_, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
	modelMatrix_ = rotate(modelMatrix_, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
	modelMatrix_ = rotate(modelMatrix_, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
	this->Notify();
}

void DrawableObject::Scale(const vec3& scale)
{
	modelMatrix_ = glm::scale(modelMatrix_, scale);
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


void DrawableObject::Draw()
{

	glUniformMatrix4fv(this->shader_->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(this->modelMatrix_));
	glUniform3fv(this->shader_->GetUniformLocation("objectColor"), 1, glm::value_ptr(this->color_));
	if (this->texture_ != nullptr)
	{
		glUniform1d(this->shader_->GetUniformLocation("texture"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *(this->texture_));
	}
	else
	{
		glUniform1d(this->shader_->GetUniformLocation("texture"), -1);
	}
	this->Draw();

	model_->Bind();
	glDrawArrays(GL_TRIANGLES, 0, model_->GetNumVertices() / (sizeof(GLfloat) * 6));
	model_->Unbind();
}

void DrawableObject::Transform(Transformation* transformation)
{
	this->modelMatrix_ *= transformation->GetMatrix();
}

