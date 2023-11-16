#include "Rotation.h"

Rotation::Rotation(const glm::vec3 rotation)
{
	this->rotation_ = rotation;
}

glm::mat4 Rotation::GetMatrix() const
{
    glm::mat4 returnMatrix;

	returnMatrix = glm::rotate(returnMatrix, glm::radians(rotation_.x), glm::vec3(1.0f, 0.0f, 0.0f));
	returnMatrix = glm::rotate(returnMatrix, glm::radians(rotation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
	returnMatrix = glm::rotate(returnMatrix, glm::radians(rotation_.z), glm::vec3(0.0f, 0.0f, 1.0f));

	return returnMatrix;
}
