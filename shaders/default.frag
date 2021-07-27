#version 330 core

in vec3 currPos;    // import current vertex position from vertex shader
in vec3 Normal;     // import normals from vertex shader
in vec4 color;      // import colors from vertex shader
in vec2 texCoords;  // import texture coordinates from vertex shader

out vec4 FragColor;  // output final fragment color

uniform sampler2D diffuse0;   // get texture unit from main function
uniform sampler2D specular0;  // get specular map from main function
uniform vec4 lightColor;      // get light color from main function
uniform vec3 lightPos;        // get light position form main function
uniform vec3 camPos;          // get camera position from main function

vec4 pointLight() {
    // vector from fragment to light
    vec3 lightVec = lightPos - currPos;

    // intensity of light w.r.t. distance
    float dist = length(lightVec);
    float a = 3.0f;
    float b = 0.7f;
    float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);

    // ambient lighting constant
    float ambient = 0.2f;

    // diffuse lighting
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightVec);
    float diffuse = max(dot(normal, lightDir), 0.0f);

    // specular lighting
    float specularLight = 0.5f;
    vec3 viewDir = normalize(camPos - currPos);
    vec3 reflectionDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 16);
    float specular = specAmount * specularLight;

    return (texture(diffuse0, texCoords) * (diffuse * intensity + ambient) + texture(specular0, texCoords).r * specular * intensity) * lightColor;
}

vec4 directLight() {
    // ambient lighting constant
    float ambient = 0.2f;

    // diffuse lighting
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(vec3(1.0f, 1.0f, 0.0f));
    float diffuse = max(dot(normal, lightDir), 0.0f);

    // specular lighting
    float specularLight = 0.5f;
    vec3 viewDir = normalize(camPos - currPos);
    vec3 reflectionDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 16);
    float specular = specAmount * specularLight;

    return (texture(diffuse0, texCoords) * (diffuse + ambient) + texture(specular0, texCoords).r * specular) * lightColor;
}

vec4 spotLight() {
    // area to be lit
    float outerCone = 0.90f;
    float innerCone = 0.95f;

    // ambient lighting constant
    float ambient = 0.2f;

    // diffuse lighting
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - currPos);
    float diffuse = max(dot(normal, lightDir), 0.0f);

    // specular lighting
    float specularLight = 0.5f;
    vec3 viewDir = normalize(camPos - currPos);
    vec3 reflectionDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 16);
    float specular = specAmount * specularLight;

    // calculate intensity w.r.t. angle of light cone
    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDir);
    float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    return (texture(diffuse0, texCoords) * (diffuse * intensity + ambient) + texture(specular0, texCoords).r * specular * intensity) * lightColor;
}

float near = 0.1f;
float far = 10.0f;

float linearizeDepth(float depth) {
    return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float logisticDepth(float depth, float steepness, float offset) {
    float zVal = linearizeDepth(depth);
    return 1 / (1 + exp(-steepness * (zVal - offset)));
}

void main() {
    // output final color
    float depth = logisticDepth(gl_FragCoord.z, 0.9f, 5.0f);
    FragColor = directLight() * (1.0f - depth) + vec4(depth * vec3(0.85f, 0.85f, 0.90f), 1.0f);
    // FragColor = vec4(vec3(linearizeDepth(gl_FragCoord.z) / far), 1.0f - linearizeDepth(gl_FragCoord.z)) + pointLight();
}