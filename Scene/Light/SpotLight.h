#pragma once

#include "PointLight.h"

class SpotLight : public PointLight {
public:
    glm::vec3 direction;

    float innerCone;
    float outerCone;

public:
    SpotLight(Shader& shader, const std::string& uniform,
              const glm::vec3& position,
              const glm::vec3& direciton,
              const float& innerCone = glm::cos(glm::radians(12.5)),
              const float& outerCone = glm::cos(glm::radians(17.5)),
              const float& quadratic = 0.032f,
              const float& linear = 0.09f,
              const float& constant = 1.0f,
              const glm::vec3& ambient = glm::vec3(0.2f),
              const glm::vec3& diffuse = glm::vec3(0.5f),
              const glm::vec3& specular = glm::vec3(1.0f));

    void setDirection(const glm::vec3& dir);
    void setDirection(const float& x, const float& y, const float& z);

    void setEdges(const float& inner, const float& outer);

    void RotateLocal(const GLfloat& angle, const glm::vec3& axis);
};
