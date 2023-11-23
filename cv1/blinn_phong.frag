#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 uLightPosition;
uniform vec3 uViewPosition;
uniform vec3 uLightColor;
uniform vec3 uObjectColor;
uniform float uShininess;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(uLightPosition - FragPos);
    vec3 viewDir = normalize(uViewPosition - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float diff = max(dot(norm, lightDir), 0.0);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), uShininess);

    vec3 diffuse = diff * uLightColor; // Diffuse light
    vec3 specular = spec * uLightColor; // Specular light

    // Final color
    vec3 result = (diffuse + specular) * uObjectColor;
    FragColor = vec4(result, 1.0);
}
