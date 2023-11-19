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


#include "Shader.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "Camera.h"
#include "Window.h"
#include "Application.h"
#include "Sphere.h"
#include "Plain.h"
#include "DrawableObject.h"

#include "suzi_smooth.h"
#include "suzi_flat.h"
#include "light.h"


int main()
{
	const unsigned int width = 800;
	const unsigned int height = 600;

	const GLfloat * usedModel = suziSmooth;
	const GLsizeiptr modelSize = sizeof(suziSmooth);

	Window win = Window::WindowBuilder("zpg")
		.SetFullscreen(false)
		.SetOpenGLVersion(3, 3)
		.SetSize(width, height)
		.Build();

	// Generates Shader object using shaders defualt.vert and default.frag
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	Shader shaderProgram(&camera, "default.vert", "default.frag");

	camera.Attach(&shaderProgram);

	Model monke = Model(usedModel, modelSize);

	DrawableObject dm = DrawableObject(&monke);
	dm.Initialize();

	Light lights[1];
	lights[0].position = glm::vec3(1.0f, 2.0f, 2.0f);
	lights[0].color = glm::vec3(1.0f, 0.0f, 1.0f);
	lights[0].ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	lights[0].diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	lights[0].specular = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 objectColor(0.5f, 0.5f, 0.5f);

	GLfloat rotation = 0.0f;
	double prevTime = glfwGetTime();
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(win.GetWindow())) {
	
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);
		shaderProgram.Activate();

		camera.Inputs(win.GetWindow());
		shaderProgram.SetCamera();

		shaderProgram.SetLights(lights, 1);

		dm.Draw();

		glfwSwapBuffers(win.GetWindow());
		glfwPollEvents();
	}

	shaderProgram.Delete();
	glfwTerminate();
	exit(EXIT_SUCCESS);
}