#pragma once

#include "Scene/Mesh.h"

#include "Scene/Shapes.h"

struct cube_mesh_struct : public mesh_struct {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<GLuint> lineIndices;

    glm::vec3 a;
    glm::vec3 b;
    glm::vec4 color;
};

class CuboidMesh : public Mesh {
protected:
    glm::vec3 a;
    glm::vec3 b;
    glm::vec4 globalColor;

public:
    CuboidMesh(const cube_mesh_struct& cuboid,
               const std::vector<Texture>& textures = std::vector<Texture>());

    cube_mesh_struct constructCuboid(const glm::vec3& a,
                                     const glm::vec3& b,
                                     const glm::vec4& color);
};
