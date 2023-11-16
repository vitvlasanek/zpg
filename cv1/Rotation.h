#pragma once
#include "TransformationComponent.h"
class Rotation :
    public TransformationComponent
{
    Rotation(const glm::vec3 rotation);
    // Inherited via TransformationComponent
    glm::mat4 GetMatrix() const override;

private:
    glm::vec3 rotation_;
};

