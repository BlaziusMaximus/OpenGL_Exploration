#version 330 core

in vec3 currPos;  // import current vertex position from vertex shader
in vec4 color;    // import colors from vertex shader

out vec4 FragColor;  // output final fragment color

uniform vec3 camPos;  // get camera position from main function

void main() {
    // output final color
    FragColor = color;
}