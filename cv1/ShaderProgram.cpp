#include "ShaderProgram.h"

void ShaderProgram::Activate()
{
	glUseProgram(this->id);
}

void ShaderProgram::Delete()
{
	glDeleteProgram(this->id);
}
