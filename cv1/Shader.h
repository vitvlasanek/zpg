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

#include "light.h"


#define MAX_LIGHTS 10

// ------- Shader .h ------
// dopredna deklarace
class Camera;
class Shader {
private:
	Camera* cam;
	std::string GetShaderCode(const char* filename);
	std::map<std::string, GLint> uniformLocations;
	void CompileErrors(GLuint shader, const char* type, GLenum pname);
	GLint GetUniformLocation(const std::string& name);
public:
	GLuint Id;
	Shader(Camera* c, const char* vertexFile, const char* fragmentFile);
	Shader(Camera* c);
	void Activate();
	void Delete();
	void SetLights(Light* lights, int numLights);
	void SetCamera();
};
