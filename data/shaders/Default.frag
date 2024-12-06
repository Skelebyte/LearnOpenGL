#version 330 core

struct Material {
    sampler2D texture;
    vec3 baseColor;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform Material material;
uniform Light light;

// texture sampler

uniform vec3 cameraPosition;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform float specularStrength = 0.5f;
uniform float shininess = 32; // 2, 4, 6, 8, 16, 32, 64, 128, 256

void main()
{
    vec3 ambient = light.ambient * material.baseColor;

    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * material.baseColor;

    vec3 viewDirection = normalize(cameraPosition - FragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;
    FragColor = texture(material.texture, TexCoord) * vec4(result, 1.0);
}
