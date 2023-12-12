#version 400 core

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
    vec3 result = vec3(0.0);

    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(lights[i].position - FragPos);
//        if (lights[i].type == 1) {
//            lightDir = normalize(lights[i].direction);
//        }

        // Common calculations
        vec3 ambient = lights[i].ambient * lights[i].color;



        vec3 diffuse = lights[i].diffuse * max(dot(Normal, lightDir), 0.0) * lights[i].color;

        float specularStrength = 0.5; // Adjust this value as needed
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(lightDir, normalize(Normal));

        float attenuation = 1.0;
        float spotlightEffect = 1.0;
        float distance_ = length(lights[i].position - FragPos);

        // Point light calculations
        attenuation = (1.0) / (lights[i].constant + lights[i].linear * distance_ + lights[i].quadratic * (distance_ * distance_));
        // Spotlight calculations
        if(lights[i].type == 1) {
            float cosTheta = dot(lightDir, normalize(-lights[i].direction));
            if (cosTheta > lights[i].outerCutoff)
            {
                  spotlightEffect = (1.0 - (1.0-cosTheta)/(1.0-lights[i].outerCutoff));
            }
            else
            {
                spotlightEffect = 0.0;
            }
             // spotlightEffect = smoothstep(lights[i].outerCutoff, lights[i].cutoff, cosTheta);

        }

        // Accumulate lighting contributions from each light
        result += (ambient + diffuse ) * texture(uTexture, TexCoord).xyz * objectColor * attenuation * spotlightEffect;
    }

    FragColor = vec4(result, 1.0);
}
