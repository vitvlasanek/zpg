#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

#define MAX_LIGHTS 4  // Adjust this based on your application's needs

struct Light {
    int type;         // 0 for point light, 1 for spotlight
    vec3 direction;  // Direction of the spotlight
    vec3 position;
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // Properties for both point light and spotlight
    float constant;
    float linear;
    float quadratic;

    // Additional properties for spotlight
    float cutoff;     // Cutoff angle in radians
    float outerCutoff; // Outer cutoff angle for smooth falloff
};

uniform vec3 viewPos;
uniform Light lights[MAX_LIGHTS];
uniform int numLights;  // Number of active lights
uniform vec3 objectColor;
uniform sampler2D uTexture;


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
