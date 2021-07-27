#version 330 core

layout(location = 0) in vec3 aPos;     // positions
layout(location = 1) in vec3 aNormal;  // normals
layout(location = 2) in vec4 aColor;   // colors
layout(location = 3) in vec2 aTex;     // texture coordinates

out vec3 currPos;    // current vertex position -> fragment shader
out vec3 Normal;     // normal -> fragment shader
out vec4 color;      // color -> fragment shader
out vec2 texCoords;  // texture coordinates -> fragment shader

uniform mat4 camMatrix;    // imports camera matrix from main function
uniform mat4 modelMatrix;  // import model matrix from main function
uniform mat3 normalMatrix;

void main() {
    // output to fragment shader
    currPos = vec3(modelMatrix * vec4(aPos, 1.0));
    Normal = normalMatrix * aNormal;
    color = aColor;
    // texCoords = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
    texCoords = aTex;

    // output position of all vertices
    gl_Position = camMatrix * vec4(currPos, 1.0);
}