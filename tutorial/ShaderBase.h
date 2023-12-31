#pragma once
#include <GL/glew.h>
class ShaderBase
{
public:
	virtual void CreateShader() =0;
	void AttachShader(GLuint* shader_program);
	GLuint GetShader();
	~ShaderBase();
protected:
	const char* shader_code;
	GLuint shader;
};

