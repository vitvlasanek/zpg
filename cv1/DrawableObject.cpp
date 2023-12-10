#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, Shader * shader)
{
	this->model_ = model;
	this->modelMatrix_ = mat4(1.0f);
	this->color_ = vec3(1, 1, 1);
	this->shader_ = shader;
	this->texture_ = nullptr;
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

void DrawableObject::SetTexture(Texture* texture)
{
	this->texture_ = texture;
}

void DrawableObject::SetColor(vec3 color)
{
	this->color_ = color;
}


void DrawableObject::Draw()
{

	glUniformMatrix4fv(this->shader_->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(this->modelMatrix_));
	glUniform3fv(this->shader_->GetUniformLocation("objectColor"), 1, glm::value_ptr(this->color_));
	if (this->texture_ != nullptr)
	{
		this->texture_->Render(this->shader_);
	}
	else
	{
		glUniform1d(this->shader_->GetUniformLocation("texture"), -1);
	}
	model_->Bind();
	glDrawArrays(GL_TRIANGLES, 0, model_->GetNumVertices() / (sizeof(GLfloat)));
	model_->Unbind();
}

void DrawableObject::Transform(Transformation* transformation)
{
	this->modelMatrix_ *= transformation->GetMatrix();
}

