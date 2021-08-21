#pragma once

#include "Scene/Mesh.h"

struct cyl_mesh_struct : public mesh_struct {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<GLuint> lineIndices;

    float radius;
    float height;
    unsigned int sectors;
    glm::vec4 color;
};

class CylinderMesh : public Mesh {
protected:
    float radius;
    float height;
    unsigned int sectors;
    glm::vec4 globalColor;

public:
    CylinderMesh(const cyl_mesh_struct& cylinder,
                 const std::vector<Texture>& textures = std::vector<Texture>());

    void setupLineVAO();

    static cyl_mesh_struct constructCylinder(const float& radius, const float& height,
                                             const unsigned int& sectors,
                                             const glm::vec4& color = glm::vec4());

    unsigned int getSectors() { return sectors; }
    void setSectors(const unsigned int& sectors);
};