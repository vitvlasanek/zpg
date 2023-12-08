#pragma once
#include <vector>

#include "TransformationComponent.h"

using namespace glm;
using namespace std;

class Transformation : public TransformationComponent
{
public:

	// Inherited via TransformationComponent
	mat4 GetMatrix() const override;
	void AddTransformation(TransformationComponent* transformation);
private:
	vector<TransformationComponent*> components;
};

