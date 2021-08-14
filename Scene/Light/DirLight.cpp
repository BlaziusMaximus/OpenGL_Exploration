#include "DirLight.h"

DirLight::DirLight(Shader& shader,
                   const std::string& uniform,
                   const glm::vec3& direction,
                   const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) :
    Light(shader, uniform, ambient, diffuse, specular),
    direction(direction) {
    shader.setVec3(lightUniform + ".direction", direction);
}

void DirLight::setDirection(const glm::vec3& dir) {
    shader.setVec3(lightUniform + ".direction", dir);
    direction = dir;
}
void DirLight::setDirection(const float& x, const float& y, const float& z) {
    shader.setVec3(lightUniform + ".direction", x, y, z);
    direction = glm::vec3(x, y, z);
}