#pragma once
#include <glm/vec3.hpp> // vec3
#include <glm/vec4.hpp> // vec4
#include <glm/mat4x4.hpp> // mat4
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp> // value_ptr

#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "Model.h"
#include "Subject.h"

using namespace glm;

class DrawableObject : public Subject
{
public:
	DrawableObject(Model* model);
	void Initialize();
	void Translate(const vec3& tranlation);
	void Rotate(const vec3& rotation);
	void Scale(const vec3& scale);
	void Delete();
	mat4 GetModelMatrix();
	void Draw();

private:
	mat4 modelMatrix;
	Model* model_;
};

