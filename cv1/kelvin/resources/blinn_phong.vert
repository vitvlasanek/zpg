#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

void main()
{
    FragPos = vec3(uModelMatrix * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(uModelMatrix))) * aNormal;

    gl_Position = uProjectionMatrix * uViewMatrix * vec4(FragPos, 1.0);
}
