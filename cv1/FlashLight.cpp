#include "FlashLight.h"

FlashLight& FlashLight::AttachToCamera(Camera* cam)
{
	this->cam_ = cam;
	cam->Attach(this);
	return *this;
}

void FlashLight::Update()
{
	if (cam_ != nullptr) {
		this->SetPosition(this->cam_->Position);
	}
	else
	{
		cout << "Flashlight not attached to camera" << endl;
	}
}
