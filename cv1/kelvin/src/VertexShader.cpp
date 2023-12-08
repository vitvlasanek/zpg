#include "VertexShader.h"

VertexShader::VertexShader()
{
	this->CreateShader();
}

void VertexShader::CreateShader()
{

	this->shader_code =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"void main () {"
		"     gl_Position = vec4 (vp, 1.0);"
		"}";

	this->shader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(this->shader, 1, &this->shader_code, nullptr);
	glCompileShader(this->shader);

}
