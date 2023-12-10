#pragma once
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "light.h"
#include "Shader.h"

class LightBase
{
protected:
	Light light_;
public:
	LightBase();

	/// <summary>
	/// Sets light to index in referenced shader
	/// </summary>
	/// <param name="shaderIndex">: from referecned Shader</param>
	void Render(Shader* shader, int shaderIndex);

	/// <summary>
	/// Changes light color (defauls is white)
	/// </summary>
	/// <param name="color">glm::vec3 with RGB</param>
	/// <returns></returns>
	virtual LightBase& SetColor(vec3 color);
	virtual LightBase& SetPosition(vec3 pos);
	virtual LightBase& SetAmbient(vec3 ambient);
	virtual LightBase& SetDiffuse(vec3 diffuse);
	virtual LightBase& SetSpecular(vec3 specular);
};

