#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

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
uniform sampler2D uTexture;

void main()
{
    vec3 darkness = vec3(0.5);

    vec3 textureColor = texture(uTexture, TexCoord).xyz;

        // Accumulate lighting contributions from each light
    vec3 result = textureColor * objectColor * darkness;

    FragColor = vec4(result, 1.0);
}
