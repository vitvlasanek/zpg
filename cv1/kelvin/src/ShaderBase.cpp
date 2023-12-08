#include "ShaderBase.h"

void ShaderBase::AttachShader(GLuint* shader_program)
{
	glAttachShader(*shader_program, this->shader);
	return;
}

GLuint ShaderBase::GetShader()
{
	return this->shader;
}

ShaderBase::~ShaderBase()
{
	glDeleteShader(this->shader);
}
