#include "CuboidMesh.h"

CuboidMesh::CuboidMesh(const std::vector<Vertex>& vertices,
                       const std::vector<GLuint>& indices,
                       const std::vector<Texture>& textures) :
    Mesh(vertices, indices, textures),
    cuboid(vertices) {}

CuboidMesh::CuboidMesh(glm::vec3 a, glm::vec3 b,
                       const std::vector<Vertex>& vertices,
                       const std::vector<GLuint>& indices,
                       const std::vector<Texture>& textures) :
    Mesh(vertices, indices, textures),
    cuboid(a, b, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) {}
