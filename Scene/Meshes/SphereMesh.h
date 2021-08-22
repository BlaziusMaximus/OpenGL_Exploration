#pragma once

#include "Scene/Mesh.h"

struct sphere_mesh_struct : public mesh_struct {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<GLuint> lineIndices;

    float radius;
    unsigned int sectors;
    unsigned int stacks;
    glm::vec4 color;
};

class SphereMesh : public Mesh {
protected:
    float radius;
    unsigned int sectorCount, stackCount;
    glm::vec4 globalColor;

public:
    SphereMesh(const sphere_mesh_struct& sphere,
               const std::vector<Texture>& textures = std::vector<Texture>());

    static sphere_mesh_struct constructSphere(const float& radius,
                                              const unsigned int& sectors,
                                              const unsigned int& stacks,
                                              const glm::vec4& color = glm::vec4(1, 1, 1, 1));

    unsigned int getSectors() { return sectorCount; }
    void setSectors(unsigned int sectors);
    unsigned int getStacks() { return stackCount; }
    void setStacks(unsigned int stacks);
};
