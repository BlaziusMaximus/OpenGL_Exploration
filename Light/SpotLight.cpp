#include "SpotLight.h"

SpotLight::SpotLight(Shader& shader, const std::string& uniform,
                     const glm::vec3& position, const glm::vec3& direciton,
                     const float& innerCone, const float& outerCone,
                     const float& quadratic, const float& linear, const float& constant,
                     const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) :
    PointLight(shader, uniform, position, quadratic, linear, constant, ambient, diffuse, specular),
    direction(direction), innerCone(innerCone), outerCone(outerCone) {
    shader.setVec3(lightUniform + ".direction", direction);
    shader.setFloat(lightUniform + ".cutOff", innerCone);
    shader.setFloat(lightUniform + ".outerCutOff", outerCone);
}

void SpotLight::setDirection(const glm::vec3& dir) {
    shader.setVec3(lightUniform + ".direction", dir);
    direction = dir;
}
void SpotLight::setDirection(const float& x, const float& y, const float& z) {
    shader.setVec3(lightUniform + ".direction", x, y, z);
    direction = glm::vec3(x, y, z);
}

void SpotLight::setEdges(const float& inner, const float& outer) {
    shader.setFloat(lightUniform + ".cutOff", inner);
    innerCone = inner;
    shader.setFloat(lightUniform + ".outerCutOff", outer);
    outerCone = outer;
}

void SpotLight::RotateLocal(const GLfloat& angle, const glm::vec3& axis) {
    setDirection(glm::mat3_cast(glm::angleAxis(angle, axis)) * direction);
}
