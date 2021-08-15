#include "SphereMesh.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/ElementBuffer.h"
#include "Scene/Camera.h"

SphereMesh::SphereMesh(const sphere_mesh_struct& sphere,
                       const std::vector<Texture>& textures) :
    Mesh(sphere.vertices, sphere.indices, sphere.lineIndices, textures),
    radius(sphere.radius),
    sectorCount(sphere.sectors),
    stackCount(sphere.stacks) {
    lineVAO.Bind();
    VertexBuffer lineVBO(vertices);
    ElementBuffer lineEBO(lineIndices);

    VAO.LinkAttrib(lineVBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    VAO.LinkAttrib(lineVBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

    lineVAO.Unbind();
    lineVBO.Unbind();
    lineEBO.Unbind();
}

sphere_mesh_struct SphereMesh::constructSphere(const float& radius,
                                               const unsigned int& sectors,
                                               const unsigned int& stacks,
                                               const glm::vec4& color) {
    std::vector<Vertex> vertices;
    vertices.reserve((stacks + 1) * (sectors + 1));
    std::vector<GLuint> indices;
    indices.reserve((stacks - 2) * sectors * 10);
    std::vector<GLuint> lineIndices;

    const float sectorStep = 2 * PI / sectors;
    const float stackStep = PI / stacks;
    const float lengthInv = 1.0f / radius;

    float sectorAngle, stackAngle;
    glm::vec3 pos;

    GLuint k1, k2;

    for (int i = 0; i <= stacks; i++) {
        stackAngle = PI / 2.0f - i * stackStep;

        k1 = i * (sectors + 1);
        k2 = k1 + sectors + 1;

        for (int j = 0; j <= sectors; j++, k1++, k2++) {
            sectorAngle = j * sectorStep;

            pos.x = radius * cos(stackAngle) * sin(sectorAngle);
            pos.y = radius * cos(stackAngle) * cos(sectorAngle);
            pos.z = radius * sin(stackAngle);
            pos = glm::rotateX(pos, (float)(PI / 2.0f));

            if (color != glm::vec4()) {
                vertices.push_back(Vertex{
                    .position = pos,
                    .normal = pos * lengthInv,
                    .color = color });
            } else {
                vertices.push_back(Vertex{
                    .position = pos,
                    .normal = pos * lengthInv,
                    .texUV = glm::vec2((float)j / sectors, (float)i / stacks) });
            }

            if (i != stacks && j != sectors) {
                // not top stack
                if (i != 0) {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);
                }
                // not bottom stack
                if (i != (stacks - 1)) {
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);
                }

                lineIndices.push_back(k1);
                lineIndices.push_back(k2);
                if (i != 0) {
                    lineIndices.push_back(k1);
                    lineIndices.push_back(k1 + 1);
                }
            }
        }
    }

    return sphere_mesh_struct{
        .vertices = vertices,
        .indices = indices,
        .lineIndices = lineIndices,
        .radius = radius,
        .sectors = sectors,
        .stacks = stacks
    };
}
