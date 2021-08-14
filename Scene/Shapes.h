#pragma once

#include "Utils.h"

namespace Shapes {
class Cuboid {
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices{
        0, 1, 2,     // bottom
        0, 2, 3,     // bottom
        4, 5, 6,     // top
        4, 6, 7,     // top
        8, 9, 11,    // left
        8, 10, 11,   // left
        12, 13, 15,  // right
        12, 14, 15,  // right
        16, 17, 19,  // back
        16, 18, 19,  // back
        20, 21, 23,  // front
        20, 22, 23   // front
    };

    Cuboid(const std::vector<Vertex>& vertices);
    Cuboid(const glm::vec3& a, const glm::vec3& b, const glm::vec4& color);
};
}  // namespace Shapes