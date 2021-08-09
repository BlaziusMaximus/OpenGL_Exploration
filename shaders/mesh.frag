#version 330 core

in vec3 currPos;    // import current vertex position from vertex shader
in vec3 Normal;     // import normals from vertex shader
in vec4 color;      // import colors from vertex shader
in vec2 texCoords;  // import texture coordinates from vertex shader

out vec4 FragColor;  // output final fragment color

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    bool on;
};
struct PointLight {
    vec3 position;

    float quadratic;
    float linear;
    float constant;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    bool on;
};
struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float quadratic;
    float linear;
    float constant;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    bool on;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
uniform Material material;
uniform vec3 camPos = vec3(0.0, 0.0, 2.0);  // get camera position from main function

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDir);

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(camPos - currPos);

    vec3 result = calcDirLight(dirLight, norm, viewDir);

    result += calcPointLight(pointLight, norm, viewDir);

    if (spotLight.on) {
        result += calcSpotLight(spotLight, norm, viewDir);
    }

    // output final color
    // FragColor = vec4(result, 1.0);
    FragColor = color;
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    // ambient lighting constant
    vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb;

    // diffuse lighting
    vec3 lightDir = normalize(-light.direction);
    float diffAmount = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diffAmount * texture(material.diffuse, texCoords).rgb;

    // specular lighting
    vec3 reflectionDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0), 16);
    vec3 specular = light.specular * specAmount * texture(material.specular, texCoords).r;

    return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir) {
    // vector from fragment to light
    vec3 lightVec = light.position - currPos;

    // attenuation of light w.r.t. distance
    float dist = length(lightVec);
    float a = light.quadratic;
    float b = light.linear;
    float c = light.constant;
    float attenuation = 1.0 / (a * dist * dist + b * dist + c);

    // ambient lighting
    vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb * attenuation;

    // diffuse lighting
    vec3 lightDir = normalize(lightVec);
    float diffAmount = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diffAmount * texture(material.diffuse, texCoords).rgb * attenuation;

    // specular lighting
    vec3 reflectionDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0), material.shininess);
    vec3 specular = light.specular * specAmount * texture(material.specular, texCoords).r * attenuation;

    return ambient + diffuse + specular;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDir) {
    // vector from fragment to light
    vec3 lightVec = light.position - currPos;
    vec3 lightDir = normalize(lightVec);

    // area to be lit
    float innerCone = light.cutOff;
    float outerCone = light.outerCutOff;

    // attenuation of light w.r.t. distance
    float dist = length(lightVec);
    float a = light.quadratic;
    float b = light.linear;
    float c = light.constant;
    float attenuation = 1.0 / (a * dist * dist + b * dist + c);

    // calculate intensity w.r.t. angle of light cone
    float theta = dot(lightDir, normalize(-light.direction));
    float intensity = clamp((theta - outerCone) / (innerCone - outerCone), 0.0, 1.0);

    // ambient lighting constant
    vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb * attenuation * intensity;

    // diffuse lighting
    float diffAmount = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diffAmount * texture(material.diffuse, texCoords).rgb * attenuation * intensity;

    // specular lighting
    vec3 reflectionDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0), material.shininess);
    vec3 specular = light.specular * specAmount * texture(material.specular, texCoords).r * attenuation * intensity;

    return vec4(vec3(ambient + diffuse + specular), 1.0);
}