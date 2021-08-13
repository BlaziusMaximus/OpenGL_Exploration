#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <vector>
#include <utility>
#include <functional>

#define PI 3.14159265358979323846

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec4 color;
    glm::vec2 texUV;
};

struct LineVertex {
    glm::vec3 position;
    glm::vec4 color;
};

template <typename T>
void flipVertices(const T& first, const T& last) {
    for (T i = first; i != last; i++) {
        i->position *= -1.0f;
    }
}

glm::vec3 getMin(const std::vector<Vertex>& vertices);
glm::vec3 getMin(const std::vector<glm::vec3>& vertices);

glm::vec3 getMax(const std::vector<Vertex>& vertices);
glm::vec3 getMax(const std::vector<glm::vec3>& vertices);

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        return h1 ^ h2;
    }
};
