#pragma once
//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


//Include the standard C++ headers  
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include "Window.h"
#include "Shader.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "suzi_smooth.h"
#include "plain.h"
#include "tree.h"
#include "Camera.h"
#include "Sphere.h"
#include "bushes.h"


class Scene
{
public:
	Scene();
	int Initialize();
	void Run();
	void Delete();
	void SetModels(vector<DrawableObject*> drawableObjects);
	void AddModels(vector<DrawableObject*> drawableObjects);
	void SetCamera(Camera* cam);
	void SetLights(Light* lights, int numlights);
private:
	Window* win;
	Shader* shader;
	Camera* cam_;
	Light* lights_;
	int numLights_;
	vector<DrawableObject*> drawableObjects_;
};

