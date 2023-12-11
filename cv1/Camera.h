#pragma once
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Subject.h"

using namespace glm;
using namespace std;

// ---- Camera .h ---
// dopredna deklarace
class Shader;
class Camera : public Subject
{
private:
	Shader* shader_;

public:
	vec3 view_;
	// Camera constructor to set up initial values
	Camera(int width, int height, vec3 position, Shader* s);
	//Camera(Shader* s);
	Camera();



	vec3 Position;
	vec3 Orientation = vec3(0.0f, 0.0f, -1.0f);
	vec3 Up = vec3(0.0f, 1.0f, 0.0f);
	mat4 cameraMatrix = mat4(1.0f);

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;

	// Stores the width and height of the window
	int width;
	int height;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 0.1f;
	float sensitivity = 100.0f;


	// Updates and exports the camera matrix to the Vertex Shader
	void UpdateUniforms();

	void UpdateUniforms(Shader* shader);

	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Handles camera inputs
	void Inputs(GLFWwindow* window);


};
