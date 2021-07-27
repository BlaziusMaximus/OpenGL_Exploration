#include "Utils.h"

glm::vec3 getMin(const std::vector<Vertex>& vertices) {
    if (vertices.size() == 0) { return glm::vec3(); }

    glm::vec3 min = vertices[0].position;

    for (Vertex v : vertices) {
        if (v.position.x < min.x) { min.x = v.position.x; }
        if (v.position.y < min.y) { min.y = v.position.y; }
        if (v.position.z < min.z) { min.z = v.position.z; }
    }

    return min;
}
glm::vec3 getMin(const std::vector<glm::vec3>& vertices) {
    if (vertices.size() == 0) { return glm::vec3(); }

    glm::vec3 min = vertices[0];

    for (glm::vec3 v : vertices) {
        if (v.x < min.x) { min.x = v.x; }
        if (v.y < min.y) { min.y = v.y; }
        if (v.z < min.z) { min.z = v.z; }
    }

    return min;
}

glm::vec3 getMax(const std::vector<Vertex>& vertices) {
    if (vertices.size() == 0) { return glm::vec3(); }

    glm::vec3 max = vertices[0].position;

    for (Vertex v : vertices) {
        if (v.position.x > max.x) { max.x = v.position.x; }
        if (v.position.y > max.y) { max.y = v.position.y; }
        if (v.position.z > max.z) { max.z = v.position.z; }
    }

    return max;
}
glm::vec3 getMax(const std::vector<glm::vec3>& vertices) {
    if (vertices.size() == 0) { return glm::vec3(); }

    glm::vec3 max = vertices[0];

    for (glm::vec3 v : vertices) {
        if (v.x > max.x) { max.x = v.x; }
        if (v.y > max.y) { max.y = v.y; }
        if (v.z > max.z) { max.z = v.z; }
    }

    return max;
}
