#pragma once

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
#include "LightBase.h"
#include "FlashLight.h"
#include "DrawableObject.h"


class Scene
{
public:
	Scene();
	Scene(std::string shader_type);
	int Initialize();
	void Run();
	void Delete();

#pragma region Models
	Scene& SetModels(vector<DrawableObject*> drawableObjects);
	Scene& AddModels(vector<DrawableObject*> drawableObjects);
	Scene& AddModels(DrawableObject* drawableObject);
	void DrawModels();
#pragma endregion

#pragma region Lights
	Scene& SetLights(vector<LightBase*> lights);
	Scene& AddLights(vector<LightBase*> lights);
	Scene& AddLights(LightBase* light);
	void DrawLights();
	void DrawLights(Shader* s);
#pragma endregion


	Scene& SetShaders(map<string, Shader*> shaders);
	Scene& AddShaders(vector<Shader*> shaders);


	Scene& SetCamera(Camera* cam);
	map<string, Shader*> shaders_;

	tuple<Shader*, DrawableObject*> DomeObject_;

private:
	Window* win;
	Shader* shader;
	Camera* cam_;
	vector<DrawableObject*> drawableObjects_;
	vector<LightBase*> lightsVector_;
	map<Shader*, vector<DrawableObject*>> ShaderObjects_;
};

