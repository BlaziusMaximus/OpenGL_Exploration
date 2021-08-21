#pragma once

#include "Drawable.h"

#include <vector>

class VertexArray;

class Line : public Drawable {
public:
    std::vector<LineVertex> vertices;

    Line(const std::vector<LineVertex>& vertices);
    ~Line();

    void Draw(
        Shader& shader,
        Camera& camera,
        const glm::mat4& matrix = glm::mat4(1.0f));
};