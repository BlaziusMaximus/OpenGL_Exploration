#include "CylinderMesh.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/ElementBuffer.h"

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

    // top/bottom cap center
    cylinder.vertices.push_back(Vertex{
        .position = glm::vec3(0.0f, height / 2.0f, 0.0f),
        .normal = glm::vec3(0.0f, 1.0f, 0.0f),
        .color = color });
    cylinder.vertices.push_back(Vertex{
        .position = glm::vec3(0.0f, -height / 2.0f, 0.0f),
        .normal = glm::vec3(0.0f, -1.0f, 0.0f),
        .color = color });

    // circle vertice construction
    const float sectorStep = 2 * PI / sectors;
    float theta = 0.0f;
    glm::vec3 pos;
    for (unsigned int i = 0; i < sectors; i++, theta += sectorStep) {
        pos.x = radius * sinf(theta);
        pos.y = height / 2.0f;
        pos.z = radius * cosf(theta);

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

    // triangle/line index generation
    GLuint tc = 0, bc = 1;  // cap: top center, bottom center
    GLuint tl, bl, tr, br;  // sector: top left, bottom left, top right, bottom right
    for (unsigned int i = 2; i < cylinder.vertices.size(); i += 2) {
        tl = i + 0;
        bl = i + 1;
        tr = i + 2;
        br = i + 3;
        if (tr >= cylinder.vertices.size()) {
            tr = 2;
            br = 3;
        }

        // --cap slice indices--
        // top trangle
        cylinder.indices.push_back(tc);
        cylinder.indices.push_back(tl);
        cylinder.indices.push_back(tr);
        // bottom triangle
        cylinder.indices.push_back(bc);
        cylinder.indices.push_back(br);
        cylinder.indices.push_back(bl);
        // top line
        cylinder.lineIndices.push_back(tc);
        cylinder.lineIndices.push_back(tl);
        // bottom line
        cylinder.lineIndices.push_back(bc);
        cylinder.lineIndices.push_back(bl);

        // --side sector indices--
        // upper left triangle
        cylinder.indices.push_back(tl);
        cylinder.indices.push_back(bl);
        cylinder.indices.push_back(tr);
        // lower right triangle
        cylinder.indices.push_back(tr);
        cylinder.indices.push_back(bl);
        cylinder.indices.push_back(br);
        // top line
        cylinder.lineIndices.push_back(tl);
        cylinder.lineIndices.push_back(tr);
        // left line
        cylinder.lineIndices.push_back(tl);
        cylinder.lineIndices.push_back(bl);
        // bottom line
        cylinder.lineIndices.push_back(bl);
        cylinder.lineIndices.push_back(br);
    }

    return cylinder;
}

void CylinderMesh::setSectors(unsigned int sectors) {
    if (sectors < 3) { return; }
    this->sectors = sectors;

    cyl_mesh_struct cylinder = constructCylinder(radius, height, sectors, globalColor);

    updateMesh(cylinder.vertices, cylinder.indices);
    lineIndices = cylinder.lineIndices;
    setupLineVAO();
}
