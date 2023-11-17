#include "Rotation.h"

Rotation::Rotation(const vec3 rotation)
{
	this->rotation_ = rotation;
}

mat4 Rotation::GetMatrix() const
{
    mat4 returnMatrix;

	returnMatrix = rotate(returnMatrix, radians(rotation_.x), vec3(1.0f, 0.0f, 0.0f));
	returnMatrix = rotate(returnMatrix, radians(rotation_.y), vec3(0.0f, 1.0f, 0.0f));
	returnMatrix = rotate(returnMatrix, radians(rotation_.z), vec3(0.0f, 0.0f, 1.0f));

	return returnMatrix;
}
