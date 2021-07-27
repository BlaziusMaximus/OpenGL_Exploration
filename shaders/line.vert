#version 330 core

layout(location = 0) in vec3 aPos;    // positions
layout(location = 1) in vec4 aColor;  // colors

out vec3 currPos;  // current vertex position -> fragment shader
out vec4 color;    // color -> fragment shader

uniform mat4 camMatrix;                // imports camera matrix from main function
uniform mat4 modelMatrix = mat4(1.0);  // import model matrix from main function

void main() {
    // output to fragment shader
    currPos = vec3(modelMatrix * vec4(aPos, 1.0f));
    color = aColor;

    // output position of all vertices
    gl_Position = camMatrix * vec4(currPos, 1.0f);
}