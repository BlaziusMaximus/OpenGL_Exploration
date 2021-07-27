#pragma once

#include "VertexArray.h"
#include "Camera.h"

class Line {
public:
    std::vector<LineVertex> vertices;

    VertexArray VAO;

    Line(const std::vector<LineVertex>& vertices);

    void Draw(
        Shader& shader,
        Camera& camera,
        const glm::mat4& matrix = glm::mat4(1.0f));
};