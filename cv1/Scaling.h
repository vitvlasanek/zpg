#pragma once
#include "TransformationComponent.h"

class Scaling :
    public TransformationComponent
{
public:
    Scaling(const glm::vec3& scale) : scale(scale) {}

    // Inherited via TransformationComponent   
    glm::mat4 GetMatrix() const override {
        return glm::scale(glm::mat4(1.0f), scale);
    }

private:
    glm::vec3 scale;
};
