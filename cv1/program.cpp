
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


#include"Shader.h"
#include"VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "Camera.h"
#include "Window.h"
#include "Application.h"


GLfloat vertices[] =
{ //     COORDINATES     /        COLORS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,
};


// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};

int main()
{
	const unsigned int width = 800;
	const unsigned int height = 600;


	//Application* app = new Application();
	//app->Initialize(); //OpenGL inicialization

	////Loading scene
	//app->CreateShaders();
	//app->CreateModels();
	//app->Run(); //Rendering 

	//delete(app);


	Window win = Window::WindowBuilder("zpg")
		.SetFullscreen(false)
		.SetOpenGLVersion(3, 3)
		.SetSize(width, height)
		.Build();

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram(nullptr, "default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VertexArrayObject VertexArrayObject1;
	VertexArrayObject1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VertexBufferObject VertexBufferObject1(vertices, sizeof(vertices), GL_STATIC_DRAW);
	// Generates Element Buffer Object and links it to indices

	// Links VertexBufferObject to VertexArrayObject
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	VertexArrayObject1.LinkVBO(VertexBufferObject1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VertexArrayObject1.LinkVBO(VertexBufferObject1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VertexArrayObject1.Unbind();
	VertexBufferObject1.Unbind();

	GLuint uniId = glGetUniformLocation(shaderProgram.Id, "scale");


	GLfloat rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Main while loop
	while (!glfwWindowShouldClose(win.GetWindow())) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		double currentTime = glfwGetTime();
		if (currentTime - prevTime >= 1/60)
		{
			rotation += 0.5f; 
			prevTime = currentTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);


		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.Id, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.Id, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.Id, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));



		glUniform1f(uniId, 0.5f);
		VertexArrayObject1.Bind();
		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, 5); //mode,first,count
		// update other events like input handling
		glfwPollEvents();


		//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(win.GetWindow());
	}

	VertexArrayObject1.Delete();
	VertexBufferObject1.Delete();
	shaderProgram.Delete();
	glfwTerminate();
	exit(EXIT_SUCCESS);
}