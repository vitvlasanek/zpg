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
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cerrno>
#include <fstream>
#include <map>
#include <vector>

#include "light.h"
#include "Observer.h"

#define MAX_LIGHTS 10

using namespace std;

// ------- Shader .h ------
// dopredna deklarace
class Camera;
class Shader : public Observer
{
private:
	Camera* cam_;
	GLuint id_;
	map<string, GLint> uniformLocations;
	string type_;

	string GetShaderCode(const char* filename);
	void CompileErrors(GLuint shader, const char* type, GLenum pname);
public:
	Shader(Camera* c, const char* vertexFile, const char* fragmentFile);
	Shader(const char* vertexFile, const char* fragmentFile);
	Shader(Camera* c);
	GLint GetUniformLocation(const string& name);
	void Activate();
	void Deactivate();
	void Delete();
	void LightsCount(int n);

	void SetTexture(GLuint * texture);


	// Inherited via Observer
	void Update() override;
};
