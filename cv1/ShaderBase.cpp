#include "ShaderBase.h"

void ShaderBase::AttachShader(GLuint* shader_program)
{
	glAttachShader(*shader_program, this->shader);
	return;
}

ShaderBase::~ShaderBase()
{
	glDeleteShader(this->shader);
}
