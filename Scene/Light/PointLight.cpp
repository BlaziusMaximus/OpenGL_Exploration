#include "PointLight.h"

#include "Scene/Meshes/SphereMesh.h"

PointLight::PointLight(Shader& shader, const std::string& uniform,
                       const glm::vec3& position,
                       const float& quadratic, const float& linear, const float& constant,
                       const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) :
    Light(shader, uniform, ambient, diffuse, specular),
    position(position), quadratic(quadratic), linear(linear), constant(constant),
    lightSphere(SphereMesh::constructSphere(0.05f, 18, 9, glm::vec4(ambient * diffuse * specular, 1.0f))),
    modelMatrix(glm::mat4(1.0f)) {
    shader.setVec3(lightUniform + ".position", position);
    shader.setFloat(lightUniform + ".quadratic", quadratic);
    shader.setFloat(lightUniform + ".linear", linear);
    shader.setFloat(lightUniform + ".constant", constant);
}

void PointLight::setPosition(const glm::vec3& pos) {
    shader.setVec3(lightUniform + ".position", pos);
    position = pos;
    modelMatrix = glm::translate(position) * glm::mat4(1.0f);
}
void PointLight::setPosition(const float& x, const float& y, const float& z) {
    shader.setVec3(lightUniform + ".position", x, y, z);
    position = glm::vec3(x, y, z);
    modelMatrix = glm::translate(position) * glm::mat4(1.0f);
}

void PointLight::setAttenuation(const float& quadratic, const float& linear, const float& constant) {
    shader.setFloat(lightUniform + ".quadratic", quadratic);
    this->quadratic = quadratic;
    shader.setFloat(lightUniform + ".linear", linear);
    this->linear = linear;
    shader.setFloat(lightUniform + ".constant", constant);
    this->constant = constant;
}

void PointLight::drawSphere(Shader& shader, Camera& camera) {
    lightSphere.Draw(shader, camera, modelMatrix);
}

void PointLight::Translate(const glm::vec3& trans) {
    setPosition(glm::translate(trans) * glm::vec4(position, 1.0f));
}
void PointLight::Translate(const float& transx, const float& transy, const float& transz) {
    setPosition(glm::translate(glm::vec3(transx, transy, transz)) * glm::vec4(position, 1.0f));
}
void PointLight::RotateWorld(const GLfloat& angle, const glm::vec3& axis) {
    setPosition(glm::mat4_cast(glm::angleAxis(angle, axis)) * glm::vec4(position, 1.0f));
}
