#pragma once

#include "Light.h"
#include "Scene/Meshes/SphereMesh.h"

class PointLight : public Light {
protected:
    SphereMesh lightSphere;

    glm::mat4 modelMatrix;

public:
    glm::vec3 position;

    float quadratic;
    float linear;
    float constant;

public:
    PointLight(Shader& shader, const std::string& uniform,
               const glm::vec3& position,
               const float& quadratic = 0.032f,
               const float& linear = 0.09f,
               const float& constant = 1.0f,
               const glm::vec3& ambient = glm::vec3(0.2f),
               const glm::vec3& diffuse = glm::vec3(0.5f),
               const glm::vec3& specular = glm::vec3(1.0f));

    void setPosition(const glm::vec3& pos);
    void setPosition(const float& x, const float& y, const float& z);

    void setAttenuation(const float& quadratic, const float& linear, const float& constant);

    void drawSphere(Shader& shader, Camera& camera);

    void Translate(const glm::vec3& trans);
    void Translate(const float& transx, const float& transy, const float& transz);
    void RotateWorld(const GLfloat& angle, const glm::vec3& axis);
};