#include "FragmentShader.h"

void FragmentShader::CreateShader()
{
	this->shader_code =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}";

	this->shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->shader, 1, &this->shader_code, nullptr);
	glCompileShader(this->shader);
}

