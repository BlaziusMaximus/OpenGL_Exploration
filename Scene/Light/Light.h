#pragma once

#include "Utils.h"
#include "Renderer/Shader.h"

#include <string>

class Light {
protected:
    Shader shader;
    std::string lightUniform;

public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    bool switchedOn;

public:
    Light(Shader& shader,
          const std::string& uniform,
          const glm::vec3& ambient = glm::vec3(1.0f),
          const glm::vec3& diffuse = glm::vec3(1.0f),
          const glm::vec3& specular = glm::vec3(1.0f));
    ~Light();

    void setAmbient(const glm::vec3& color);
    void setAmbient(const float& r, const float& g, const float& b);

    void setDiffuse(const glm::vec3& color);
    void setDiffuse(const float& r, const float& g, const float& b);

    void setSpecular(const glm::vec3& color);
    void setSpecular(const float& r, const float& g, const float& b);

    void switchOnOff();
    void setSwitchedOn(const bool& sw);
};