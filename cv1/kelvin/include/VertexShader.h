#pragma once
#include "ShaderBase.h"
class VertexShader :
    public ShaderBase
{
public:
    VertexShader();
private:
    // Inherited via Shader
    void CreateShader() override;

};

