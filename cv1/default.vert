#version 330 core

//Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Normals (not necessarily normalized)
layout (location = 2) in vec3 aNormal;



// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the current position for the Fragment Shader
out vec3 crntPos;

uniform float scale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 camMatrix;


void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;

	Normal = aNormal;
}