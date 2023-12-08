#pragma once
#include "TransformationComponent.h"
class Rotation :
    public TransformationComponent
{
    Rotation(const vec3 rotation);
    // Inherited via TransformationComponent
    mat4 GetMatrix() const override;

private:
    vec3 rotation_;
};

