#pragma once

#include "Scene/Mesh.h"

#include "Scene/Shapes.h"

class CuboidMesh : public Mesh {
public:
    Shapes::Cuboid cuboid;

    CuboidMesh(const std::vector<Vertex>& vertices,
               const std::vector<GLuint>& indices,
               const std::vector<Texture>& textures = std::vector<Texture>());
    CuboidMesh(glm::vec3 a, glm::vec3 b,
               const std::vector<Vertex>& vertices,
               const std::vector<GLuint>& indices,
               const std::vector<Texture>& textures = std::vector<Texture>());
};