#pragma once

#include "Light.h"

class DirLight : public Light {
public:
    glm::vec3 direction;

public:
    DirLight(Shader& shader,
             const std::string& uniform,
             const glm::vec3& direction = glm::vec3(0.0f, -1.0f, 0.0f),
             const glm::vec3& ambient = glm::vec3(0.2f),
             const glm::vec3& diffuse = glm::vec3(0.5f),
             const glm::vec3& specular = glm::vec3(1.0f));

    void setDirection(const glm::vec3& dir);
    void setDirection(const float& x, const float& y, const float& z);
};