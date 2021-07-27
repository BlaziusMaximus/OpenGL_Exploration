#include "Shapes.h"

Shapes::Cuboid::Cuboid(const std::vector<Vertex>& vertices) :
    vertices(vertices) {}

Shapes::Cuboid::Cuboid(const glm::vec3& a, const glm::vec3& b, const glm::vec4& color) {
    Vertex _vertices[] = {
        //   COORDINATES, NORMALS, COLORS  //   face  // vert // ind //
        Vertex{ glm::vec3(a.x, a.y, b.z),  //   bottom   (1)     0
                glm::vec3(0.0f, -1.0f, 0.0f),
                color },
        Vertex{ glm::vec3(a.x, a.y, a.z),  //   bottom   (2)     1
                glm::vec3(0.0f, -1.0f, 0.0f),
                color },
        Vertex{ glm::vec3(b.x, a.y, a.z),  //   bottom   (3)     2
                glm::vec3(0.0f, -1.0f, 0.0f),
                color },
        Vertex{ glm::vec3(b.x, a.y, b.z),  //   bottom   (4)     3
                glm::vec3(0.0f, -1.0f, 0.0f),
                color },

        Vertex{ glm::vec3(a.x, b.y, b.z),  //   top      (5)     4
                glm::vec3(0.0f, 1.0f, 0.0f),
                color },
        Vertex{ glm::vec3(a.x, b.y, a.z),  //   top      (6)     5
                glm::vec3(0.0f, 1.0f, 0.0f),
                color },
        Vertex{ glm::vec3(b.x, b.y, a.z),  //   top      (7)     6
                glm::vec3(0.0f, 1.0f, 0.0f),
                color },
        Vertex{ glm::vec3(b.x, b.y, b.z),  //   top      (8)     7
                glm::vec3(0.0f, 1.0f, 0.0f),
                color },

        Vertex{ glm::vec3(a.x, a.y, b.z),  //   left     (1)     8
                glm::vec3(-1.0f, 0.0f, 0.0f),
                color },
        Vertex{ glm::vec3(a.x, a.y, a.z),  //   left     (2)     9
                glm::vec3(-1.0f, 0.0f, 0.0f),
                color },
        Vertex{ glm::vec3(a.x, b.y, b.z),  //   left     (5)     10
                glm::vec3(-1.0f, 0.0f, 0.0f),
                color },
        Vertex{ glm::vec3(a.x, b.y, a.z),  //   left     (6)     11
                glm::vec3(-1.0f, 0.0f, 0.0f),
                color },

        Vertex{ glm::vec3(b.x, a.y, a.z),  //   right    (3)     12
                glm::vec3(1.0f, 0.0f, 0.0f),
                color },
        Vertex{ glm::vec3(b.x, a.y, b.z),  //   right    (4)     13
                glm::vec3(1.0f, 0.0f, 0.0f),
                color },
        Vertex{ glm::vec3(b.x, b.y, a.z),  //   right    (7)     14
                glm::vec3(1.0f, 0.0f, 0.0f),
                color },
        Vertex{ glm::vec3(b.x, b.y, b.z),  //   right    (8)     15
                glm::vec3(1.0f, 0.0f, 0.0f),
                color },

        Vertex{ glm::vec3(a.x, a.y, a.z),  //   back     (2)     16
                glm::vec3(0.0f, 0.0f, -1.0f),
                color },
        Vertex{ glm::vec3(b.x, a.y, a.z),  //   back     (3)     17
                glm::vec3(0.0f, 0.0f, -1.0f),
                color },
        Vertex{ glm::vec3(a.x, b.y, a.z),  //   back     (6)     18
                glm::vec3(0.0f, 0.0f, -1.0f),
                color },
        Vertex{ glm::vec3(b.x, b.y, a.z),  //   back     (7)     19
                glm::vec3(0.0f, 0.0f, -1.0f),
                color },

        Vertex{ glm::vec3(a.x, a.y, b.z),  //   front    (1)     20
                glm::vec3(0.0f, 0.0f, 1.0f),
                color },
        Vertex{ glm::vec3(b.x, a.y, b.z),  //   front    (4)     21
                glm::vec3(0.0f, 0.0f, 1.0f),
                color },
        Vertex{ glm::vec3(a.x, b.y, b.z),  //   front    (5)     22
                glm::vec3(0.0f, 0.0f, 1.0f),
                color },
        Vertex{ glm::vec3(b.x, b.y, b.z),  //   front    (8)     23
                glm::vec3(0.0f, 0.0f, 1.0f),
                color },
    };

    vertices = std::vector<Vertex>(_vertices, _vertices + sizeof(_vertices) / sizeof(Vertex));
}