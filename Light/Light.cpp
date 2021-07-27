#include "Light.h"

Light::Light(Shader& shader,
             const std::string& uniform,
             const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) :
    shader(shader),
    lightUniform(uniform), ambient(ambient), diffuse(diffuse), specular(specular), switchedOn(true) {
    shader.setVec3(lightUniform + ".ambient", ambient);
    shader.setVec3(lightUniform + ".diffuse", diffuse);
    shader.setVec3(lightUniform + ".specular", specular);
    shader.setBool(lightUniform + ".on", true);
}

void Light::setAmbient(const glm::vec3& color) {
    shader.setVec3(lightUniform + ".ambient", color);
    ambient = color;
}
void Light::setAmbient(const float& r, const float& g, const float& b) {
    shader.setVec3(lightUniform + ".ambient", r, g, b);
    ambient = glm::vec3(r, g, b);
}

void Light::setDiffuse(const glm::vec3& color) {
    shader.setVec3(lightUniform + ".diffuse", color);
    diffuse = color;
}
void Light::setDiffuse(const float& r, const float& g, const float& b) {
    shader.setVec3(lightUniform + ".diffuse", r, g, b);
    diffuse = glm::vec3(r, g, b);
}

void Light::setSpecular(const glm::vec3& color) {
    shader.setVec3(lightUniform + ".specular", color);
    specular = color;
}
void Light::setSpecular(const float& r, const float& g, const float& b) {
    shader.setVec3(lightUniform + ".specular", r, g, b);
    specular = glm::vec3(r, g, b);
}

void Light::switchOnOff() {
    switchedOn = !switchedOn;
    shader.setBool(lightUniform + ".on", switchedOn);
}
void Light::setSwitchedOn(const bool& sw) {
    switchedOn = sw;
    shader.setBool(lightUniform + ".on", switchedOn);
}