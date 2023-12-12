#include "FlashLight.h"

FlashLight& FlashLight::AttachToCamera(Camera* cam)
{
	this->cam_ = cam;
	cam->Attach(this);
	return *this;
}

FlashLight::FlashLight() : LightBase()
{
	this->light_.cuttof = cos(radians(5.02f));
	this->light_.outerCutoff = cos(radians(20.0f));
  	this->light_.type = 1;
	this->light_.diffuse = vec3(1.0f);
	this->light_.specular = vec3(1.0f);
	this->light_.ambient = vec3(0.1f);
	this->light_.color = vec3(1.0f, 1.0f, 0.75f);
	this->light_.position = vec3(1, 1, 1);
	this->light_.direction = vec3(1, 1, 1);
}

void FlashLight::SetUniforms(Shader* shader, int shaderIndex)
{
	glUniform3fv(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].direction"), 1, glm::value_ptr(this->light_.direction));
	glUniform3fv(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].position"), 1, glm::value_ptr(this->light_.position));
	glUniform3fv(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].color"), 1, glm::value_ptr(this->light_.color));
	glUniform3fv(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].ambient"), 1, glm::value_ptr(this->light_.ambient));
	glUniform3fv(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].diffuse"), 1, glm::value_ptr(this->light_.diffuse));
	glUniform3fv(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].specular"), 1, glm::value_ptr(this->light_.specular));
	glUniform1i(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].type"), this->light_.type);
	glUniform1f(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].constant"), this->light_.constant);
	glUniform1f(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].linear"), this->light_.linear);
	glUniform1f(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].quadratic"), this->light_.quadratic);
	glUniform1f(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].cuttof"), this->light_.cuttof);
	glUniform1f(shader->GetUniformLocation("lights[" + to_string(shaderIndex) + "].outerCutoff"), this->light_.outerCutoff);
}

void FlashLight::Update()
{
	if (cam_ != nullptr) {
		this->SetPosition(this->cam_->Position);
		this->light_.direction = this->cam_->Orientation;
	}
	else
	{
		cout << "Flashlight not attached to camera" << endl;
	}
}
