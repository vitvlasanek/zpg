// --- Camera . cpp --
# include "Camera.h"
# include "Shader.h"
Camera::Camera() {
}



Camera::Camera(int width, int height, vec3 position, Shader* s)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
	//this->shader_ = s;
}

//
//void Camera::UpdateUniforms()
//{
//	glUniformMatrix4fv(this->shader_->GetUniformLocation("camMatrix"), 1, GL_FALSE, glm::value_ptr(this->cameraMatrix));
//	glUniform3fv(this->shader_->GetUniformLocation("viewPos"), 1, glm::value_ptr(this->Position));
//}

void Camera::UpdateUniforms(Shader * shader)
{
	glUniformMatrix4fv(shader->GetUniformLocation("camMatrix"), 1, GL_FALSE, glm::value_ptr(this->cameraMatrix));
	glUniform3fv(shader->GetUniformLocation("viewPos"), 1, glm::value_ptr(this->Position));
	this->Notify();
}

void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	mat4 view = mat4(1.0f);
	mat4 projection = mat4(1.0f);

	view = lookAt(Position, Position + Orientation, Up);
	
	projection = perspective(radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	this->cameraMatrix = projection * view;
	this->Notify();
}



void Camera::Inputs(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -normalize(cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * normalize(cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}


	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		// Calculates upcoming vertical change in the Orientation
		vec3 newOrientation = rotate(Orientation, radians(-rotX), normalize(cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(angle(newOrientation, Up) - radians(90.0f)) <= radians(85.0f))
		{
			Orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		Orientation = rotate(Orientation, radians(-rotY), Up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}