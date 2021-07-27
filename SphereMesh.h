#pragma once

#include "Mesh.h"

struct verts_inds {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<GLuint> lineIndices;
};

class SphereMesh : public Mesh {
private:
    float radius;
    unsigned int sectorCount, stackCount;

    Shader lineShader;
    VertexArray lineVAO;
    std::vector<GLuint> lineIndices;

    verts_inds constructSphere(
        const float& radius,
        const unsigned int& sectors,
        const unsigned int& stacks,
        const glm::vec4& color = glm::vec4());

public:
    SphereMesh(
        const float& radius,
        const unsigned int& sectors,
        const unsigned int& stacks,
        const std::vector<Texture>& textures);
    SphereMesh(
        const float& radius,
        const unsigned int& sectors,
        const unsigned int& stacks,
        const glm::vec4& color);

    void drawLines(Camera& camera);
};