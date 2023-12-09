#pragma once
#include "LightBase.h"
#include "Subject.h"
#include "Observer.h"
#include "Camera.h"


class FlashLight : public LightBase, public Observer
{
public:
	FlashLight& AttachToCamera(Camera* cam);

// Inherited via Observer
	void Update() override;
private:
	Camera* cam_;
};

