#pragma once
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "Model.h"

class DrawableObject
{
public:
	DrawableObject(Model* model);
	void Initialize();
	void Translate(const glm::vec3& tranlation);
	void Rotate(const glm::vec3& rotation);
	void Scale(const glm::vec3& scale);
	void Delete();
	void Draw();

private:
	glm::mat4 modelMatrix;
	Model* model_;
};

