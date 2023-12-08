#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

#define MAX_LIGHTS 4  // Adjust this based on your application's needs

struct Light {
    vec3 position;
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform Light lights[MAX_LIGHTS];
uniform int numLights;  // Number of active lights
uniform vec3 objectColor;

void main()
{
    vec3 result = vec3(0.0);

    for (int i = 0; i < numLights; ++i) {

        // Diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lights[i].position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = lights[i].diffuse * diff * lights[i].color;

        // Accumulate lighting contributions from each light
        result += diffuse * objectColor ;
    }

    FragColor = vec4(result, 1.0);
}
