#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

#define MAX_LIGHTS 4  // Adjust this based on your application's needs

struct Light {
    int type;         // 0 for point light, 1 for spotlight
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
    vec3 direction;  // Direction of the spotlight
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
    vec3 result = vec3(0.0);

    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(lights[i].position - FragPos);
        float cosTheta = dot(lightDir, normalize(-lights[i].direction));

        // Common calculations
        vec3 ambient = lights[i].ambient * lights[i].color;
        vec3 diffuse = lights[i].diffuse * max(dot(Normal, lightDir), 0.0);
        
        float specularStrength = 0.5; // Adjust this value as needed
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, normalize(Normal));
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // Shininess factor
        vec3 specular = lights[i].specular * (spec * specularStrength) * lights[i].color;

        float attenuation = 1.0;
        float spotlightEffect = 1.0;

        // Point light calculations
        if (lights[i].type == 0) {
            //float distance = length(lights[i].position - FragPos);
            float distance = 1;
            attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));
        }
        // Spotlight calculations
        else if(lights[i].type == 1) {
            spotlightEffect = smoothstep(lights[i].cutoff, lights[i].outerCutoff, cosTheta);
        }

        // Accumulate lighting contributions from each light
        result += (ambient + diffuse + specular) * texture(uTexture, TexCoord).xyz * objectColor * attenuation * spotlightEffect;
    }

    FragColor = vec4(result, 1.0);
}
