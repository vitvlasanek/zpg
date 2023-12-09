#pragma once
#include <glm/vec3.hpp> // vec3
#include <glm/vec4.hpp> // vec4
#include <glm/mat4x4.hpp> // mat4
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp> // value_ptr

#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "Model.h"
#include "SkinnedModel.h"
#include "Subject.h"
#include "Transformation.h"
#include "Translation.h"
#include "Scaling.h"
#include "Rotation.h"
#include "Shader.h"

using namespace glm;

class DrawableObject : public Subject
{
public:
	DrawableObject(Model* model, Shader * shader);
	void Initialize();
	void Delete();
	void SetTexture(GLuint* texture);
	void Draw();

#pragma region Transformations
	void Transform(Transformation* transformationMatrix);
	void Translate(const vec3& tranlation);
	void Rotate(const vec3& rotation);
	void Scale(const vec3& scale);
#pragma endregion


private:
	vec3 color_;
	GLuint* texture_;
	mat4 modelMatrix_;
	Model* model_;
	Shader* shader_;
};

