#pragma once
#include <vector>

#include "TransformationComponent.h"
class Transformation : public TransformationComponent
{
public:

	// Inherited via TransformationComponent
	glm::mat4 GetMatrix() const override;
	void AddTransformation(TransformationComponent* transformation);
private:
	std::vector<TransformationComponent*> components;
};

