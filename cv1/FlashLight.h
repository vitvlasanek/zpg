#pragma once
#include "LightBase.h"
#include "Subject.h"
#include "Observer.h"
#include "Camera.h"


class FlashLight : public LightBase, public Observer
{
public:
	FlashLight& AttachToCamera(Camera* cam);
	FlashLight();
	void SetUniforms(Shader* shader, int shaderIndex) override;
// Inherited via Observer
	void Update() override;
private:
	Camera* cam_;
};

