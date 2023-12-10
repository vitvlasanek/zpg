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
    vec3 result = vec3(0.0);

    for (int i = 0; i < numLights; ++i) {
        // Ambient
        vec3 ambient = lights[i].ambient * lights[i].color;
        vec3 textureColor = texture(uTexture, TexCoord).xyz;

        // Accumulate lighting contributions from each light
        result += ambient * textureColor * objectColor ;
    }

    FragColor = vec4(result, 1.0);
}
