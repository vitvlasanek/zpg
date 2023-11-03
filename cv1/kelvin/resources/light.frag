#version 330 core

out vec4 FragColor;

in vec3 lightColor;


void main()
{
	FragColor = lightColor;
}