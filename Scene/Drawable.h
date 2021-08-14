#pragma once

#include "Utils.h"
#include "Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

class Camera;

class Drawable {
protected:
    VertexArray VAO;

public:
    virtual void Draw(
        Shader& shader,
        Camera& camera,
        const glm::mat4& matrix = glm::mat4(1.0f)) = 0;
};