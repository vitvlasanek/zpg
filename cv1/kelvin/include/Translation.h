#pragma once
#include "TransformationComponent.h"

class Translation :
    public TransformationComponent
{
    // Inherited via TransformationComponent
    mat4 GetMatrix() const override;
public:
    Translation(vec3 translation);
private:
    vec3 translation_;
};

