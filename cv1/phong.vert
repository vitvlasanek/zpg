#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;   // Fragment position in world space
out vec3 Normal;     // Normal vector in world space

uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;
uniform mat4 camMatrix;  // Camera transformation matrix

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // Transform position to camera space
    vec4 fragPosCameraSpace = camMatrix * vec4(FragPos, 1.0);
    //gl_Position = projection * view * fragPosCameraSpace;
    gl_Position = fragPosCameraSpace;

}
