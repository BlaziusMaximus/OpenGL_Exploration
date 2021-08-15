#include "CuboidMesh.h"

CuboidMesh::CuboidMesh(const cube_mesh_struct& cuboid,
                       const std::vector<Texture>& textures) :
    Mesh(cuboid.vertices, cuboid.indices, cuboid.lineIndices, textures),
    a(cuboid.a), b(cuboid.b),
    globalColor(cuboid.color) {}

cube_mesh_struct constructCuboid(const glm::vec3& a,
                                 const glm::vec3& b,
                                 const glm::vec4& color) {
    std::vector<Vertex> vertices{
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
        Vertex{ glm::vec3(a.x, b.y, a.z),  //   left     (5)     10
                glm::vec3(-1.0f, 0.0f, 0.0f),
                color },
        Vertex{ glm::vec3(a.x, b.y, b.z),  //   left     (6)     11
                glm::vec3(-1.0f, 0.0f, 0.0f),
                color },

        Vertex{ glm::vec3(b.x, a.y, a.z),  //   right    (3)     12
                glm::vec3(1.0f, 0.0f, 0.0f),
                color },
        Vertex{ glm::vec3(b.x, a.y, b.z),  //   right    (4)     13
                glm::vec3(1.0f, 0.0f, 0.0f),
                color },
        Vertex{ glm::vec3(b.x, b.y, b.z),  //   right    (7)     14
                glm::vec3(1.0f, 0.0f, 0.0f),
                color },
        Vertex{ glm::vec3(b.x, b.y, a.z),  //   right    (8)     15
                glm::vec3(1.0f, 0.0f, 0.0f),
                color },

        Vertex{ glm::vec3(a.x, a.y, a.z),  //   back     (2)     16
                glm::vec3(0.0f, 0.0f, -1.0f),
                color },
        Vertex{ glm::vec3(b.x, a.y, a.z),  //   back     (3)     17
                glm::vec3(0.0f, 0.0f, -1.0f),
                color },
        Vertex{ glm::vec3(b.x, b.y, a.z),  //   back     (6)     18
                glm::vec3(0.0f, 0.0f, -1.0f),
                color },
        Vertex{ glm::vec3(a.x, b.y, a.z),  //   back     (7)     19
                glm::vec3(0.0f, 0.0f, -1.0f),
                color },

        Vertex{ glm::vec3(a.x, a.y, b.z),  //   front    (1)     20
                glm::vec3(0.0f, 0.0f, 1.0f),
                color },
        Vertex{ glm::vec3(a.x, b.y, b.z),  //   front    (4)     21
                glm::vec3(0.0f, 0.0f, 1.0f),
                color },
        Vertex{ glm::vec3(b.x, b.y, b.z),  //   front    (5)     22
                glm::vec3(0.0f, 0.0f, 1.0f),
                color },
        Vertex{ glm::vec3(b.x, a.y, b.z),  //   front    (8)     23
                glm::vec3(0.0f, 0.0f, 1.0f),
                color },
    };

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

    std::vector<GLuint> lineIndices{
        0, 1,
        0, 2,
        1, 3,
        0, 3,

        4, 5,
        5, 6,
        6, 7,
        4, 7,

        8, 9,
        9, 10,
        10, 11,
        8, 11,

        12, 13,
        13, 14,
        14, 15,
        12, 15,

        16, 17,
        17, 18,
        18, 19,
        16, 19,

        20, 21,
        21, 22,
        22, 23,
        20, 23
    };

    return (cube_mesh_struct){
        .vertices = vertices,
        .indices = indices,
        .lineIndices = lineIndices,
        .a = a,
        .b = b,
        .color = color
    };
}
