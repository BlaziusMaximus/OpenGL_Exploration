#pragma once

#include "Mesh.h"

struct verts_inds {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<GLuint> lineIndices;
};

class IcosphereMesh : Mesh {
private:
    float radius;
    unsigned int subdivisions;

    verts_inds constructSphere(const float& radius,
                               const unsigned int& subdivisions,
                               const glm::vec4& color = glm::vec4());

public:
    IcosphereMesh(const float& radius,
                  const unsigned int& subdivisions,
                  const std::vector<Texture>& textures);
    IcosphereMesh(const float& radius,
                  const unsigned int& subdivisions,
                  const glm::vec4& color);
};