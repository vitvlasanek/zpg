
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

#include "suzi_smooth.h"
#include "suzi_flat.h"


GLfloat vertices[] =
{ //     COORDINATES     /        COLORS          /         NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	  0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,      0.0f, 0.5f,  0.8f  // Facing side
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

int main()
{
	const unsigned int width = 800;
	const unsigned int height = 600;

	const GLfloat * usedModel = suziFlat;
	const GLsizeiptr modelSize = sizeof(suziFlat);
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
	VertexBufferObject VertexBufferObject1(usedModel, modelSize, GL_STATIC_DRAW);
	// Generates Element Buffer Object and links it to indices

	// Links VertexBufferObject to VertexArrayObject
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	VertexArrayObject1.LinkVBO(VertexBufferObject1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (GLvoid*)0);
	VertexArrayObject1.LinkVBO(VertexBufferObject1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	VertexArrayObject1.LinkVBO(VertexBufferObject1, 2, 3, GL_FLOAT, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	// Unbind all to prevent accidentally modifying them
	VertexArrayObject1.Unbind();
	VertexBufferObject1.Unbind();

	Shader lightShader(nullptr, "light.vert", "light.frag");
	VertexArrayObject lightVAO;
	lightVAO.Bind();
	VertexBufferObject lightVBO(lightVertices, sizeof(lightVertices), GL_STATIC_DRAW);

	lightVAO.LinkVBO(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (GLvoid*)0);
	lightVAO.Unbind();
	lightVBO.Unbind();







	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);



	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.Id, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.Id, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.Id, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.Id, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.Id, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	GLfloat rotation = 0.0f;
	double prevTime = glfwGetTime();
	glEnable(GL_DEPTH_TEST);


	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(win.GetWindow())) {
		// clear color and depth buffer

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);
		shaderProgram.Activate();

		camera.Inputs(win.GetWindow());
		// Updates and exports the camera matrix to the Vertex Shader


		camera.Matrix(shaderProgram, "camMatrix");

		/*
		double currentTime = glfwGetTime();
		if (currentTime - prevTime >= 1/60)
		{
			rotation += 5.0f;
			prevTime = currentTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 size = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);


		//glm::scale(size, glm::vec3(0.0f, 1.0f, 0.0f));

		GLuint scaleLoc = glGetUniformLocation(shaderProgram.Id, "scale");
		glUniform1f(scaleLoc, 0.1f);
		//glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, glm::value_ptr(model));

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -5.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.Id, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.Id, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.Id, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		*/

		VertexArrayObject1.Bind();
		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, modelSize / (sizeof(GLfloat) * 6)); //mode,first,count
		// update other events like input handling
		lightShader.Activate();

		camera.Matrix(lightShader, "camMatrix");

		lightVAO.Bind();

		glDrawArrays(GL_TRIANGLES, 0, sizeof(lightVertices) / (sizeof(float) * 3));

		//glDrawElements(GL_TRIANGLES, 2880, GL_UNSIGNED_INT, 0);
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(win.GetWindow());

		glfwPollEvents();

	}

	VertexArrayObject1.Delete();
	VertexBufferObject1.Delete();
	shaderProgram.Delete();
	glfwTerminate();
	exit(EXIT_SUCCESS);
}