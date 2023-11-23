#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 uLightPosition;
uniform vec3 uLightColor;
uniform vec3 uObjectColor;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(uLightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uLightColor; // Diffuse light

    // Final color
    vec3 result = diffuse * uObjectColor;
    FragColor = vec4(result, 1.0);
}
