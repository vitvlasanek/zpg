#pragma once
#include "TransformationComponent.h"

class Scaling :
    public TransformationComponent
{
public:
    Scaling(const vec3& scale) : scale_(scale) {}

    // Inherited via TransformationComponent   
    mat4 GetMatrix() const override {
        return glm::scale(mat4(1.0f), scale_);
    }

private:
    vec3 scale_;
};
