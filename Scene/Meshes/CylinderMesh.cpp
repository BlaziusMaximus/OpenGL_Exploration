#include "CylinderMesh.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/ElementBuffer.h"

CylinderMesh::CylinderMesh(const cyl_mesh_struct& cylinder) :
    Mesh(cylinder.vertices, cylinder.indices, cylinder.lineIndices),
    radius(cylinder.radius),
    height(cylinder.height),
    sectors(cylinder.sectors),
    globalColor(cylinder.color) {
    setupLineVAO();
}
CylinderMesh::CylinderMesh(const cyl_mesh_struct& cylinder, const std::vector<Texture>& textures) :
    Mesh(cylinder.vertices, cylinder.indices, cylinder.lineIndices, textures),
    radius(cylinder.radius),
    height(cylinder.height),
    sectors(cylinder.sectors),
    globalColor(cylinder.color) {
    setupLineVAO();
}

void CylinderMesh::setupLineVAO() {
    lineVAO.Bind();
    VertexBuffer lineVBO(vertices);
    ElementBuffer lineEBO(lineIndices);

    VAO.LinkAttrib(lineVBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    VAO.LinkAttrib(lineVBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

    lineVAO.Unbind();
    lineVBO.Unbind();
    lineEBO.Unbind();
}

cyl_mesh_struct CylinderMesh::constructCylinder(const float& radius, const float& height,
                                                const unsigned int& sectors,
                                                const glm::vec4& color) {
    cyl_mesh_struct cylinder{
        .radius = radius,
        .height = height,
        .sectors = sectors,
        .color = color
    };

    const float sectorStep = 2 * PI / sectors;

    float theta = 0.0f;
    glm::vec3 pos;

    for (unsigned int i = 0; i < sectors; i++, theta += sectorStep) {
        pos.x = radius * cosf(theta);
        pos.y = height / 2.0f;
        pos.z = radius * sinf(theta);

        cylinder.vertices.push_back(Vertex{
            .position = pos,
            .normal = glm::normalize(glm::vec3(pos.x, 0.0f, pos.z)),
            .color = color });
        pos.y *= -1;
        cylinder.vertices.push_back(Vertex{
            .position = pos,
            .normal = glm::normalize(glm::vec3(pos.x, 0.0f, pos.z)),
            .color = color });
    }

    GLuint tl, bl, tr, br;
    for (unsigned int i = 0; i < cylinder.vertices.size(); i += 2) {
        tl = i + 0;
        bl = i + 1;
        tr = i + 2;
        br = i + 3;
        if (tr >= cylinder.vertices.size()) {
            tr = 0;
            br = 1;
        }

        cylinder.indices.push_back(tl);
        cylinder.indices.push_back(bl);
        cylinder.indices.push_back(tr);

        cylinder.indices.push_back(tr);
        cylinder.indices.push_back(bl);
        cylinder.indices.push_back(br);

        cylinder.lineIndices.push_back(tl);
        cylinder.lineIndices.push_back(tr);

        cylinder.lineIndices.push_back(tl);
        cylinder.lineIndices.push_back(bl);

        cylinder.lineIndices.push_back(bl);
        cylinder.lineIndices.push_back(br);
    }

    return cylinder;
}

void CylinderMesh::setSectors(unsigned int sectors) {
    this->sectors = sectors;

    cyl_mesh_struct cylinder = constructCylinder(radius, height, sectors, globalColor);

    updateMesh(cylinder.vertices, cylinder.indices);
    lineIndices = cylinder.lineIndices;
    setupLineVAO();
}
