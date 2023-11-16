#include "Transformation.h"

glm::mat4 Transformation::GetMatrix() const
{
	glm::mat4 resultMatrix(1.0f);

	for (const TransformationComponent * component : components) {
		resultMatrix *= component->GetMatrix();
	}

	return resultMatrix;
}

void Transformation::AddTransformation(TransformationComponent* transformation)
{
	components.push_back(transformation);
}
