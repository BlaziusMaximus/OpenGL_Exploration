#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 camMatrix;
uniform mat4 modelMatrix;
uniform float outline;

void main() {
    vec3 currPos = vec3(modelMatrix * vec4(aPos + aNormal * outline, 1.0));
    gl_Position = camMatrix * vec4(currPos, 1.0);
}