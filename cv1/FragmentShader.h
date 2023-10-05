#pragma once
#include "ShaderBase.h"
class FragmentShader : public ShaderBase
{
public:
	FragmentShader();
private:
	// Inherited via Shader
	void CreateShader() override;
};

