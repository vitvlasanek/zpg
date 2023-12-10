#include "LightBase.h"

void LightBase::Render(int shaderIndex)
{
	this->Render(this->shader_, shaderIndex);
}


void LightBase::Render(Shader * shader, int shaderIndex)
{
	glUniform3fv(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].position"), 1, glm::value_ptr(this->light_.position));
	glUniform3fv(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].color"), 1, glm::value_ptr(this->light_.color));
	glUniform3fv(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].ambient"), 1, glm::value_ptr(this->light_.ambient));
	glUniform3fv(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].diffuse"), 1, glm::value_ptr(this->light_.diffuse));
	glUniform3fv(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].specular"), 1, glm::value_ptr(this->light_.specular));
}

LightBase& LightBase::SetColor(vec3 color)
{
	this->light_.color = color;
	return *this;
}

LightBase& LightBase::SetPosition(vec3 pos)
{
	this->light_.position = pos;
	return *this;
}

LightBase& LightBase::SetAmbient(vec3 ambient)
{
	this->light_.ambient = ambient;
	return *this;
}

LightBase& LightBase::SetDiffuse(vec3 diffuse)
{
	this->light_.diffuse = diffuse;
	return *this;
}

LightBase& LightBase::SetSpecular(vec3 specular)
{
	this->light_.specular = specular;
	return *this;
}

LightBase::LightBase(Shader * shader)
{
	this->light_.position = vec3(0.0f, 0.0f, 0.0f);
	this->light_.color = vec3(1.0f, 1.0f, 1.0f);
	this->light_.ambient = vec3(0.0f, 0.0f, 0.0f);
	this->light_.diffuse = vec3(0.5f, 0.5f, 0.5f);
	this->light_.specular = vec3(1.0f, 1.0f, 1.0f);
	this->shader_ = shader;
}
