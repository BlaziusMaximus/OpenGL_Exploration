#include "SphereMesh.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/ElementBuffer.h"
#include "Scene/Camera.h"

SphereMesh::SphereMesh(const sphere_mesh_struct& sphere,
                       const std::vector<Texture>& textures) :
    Mesh(sphere.vertices, sphere.indices, sphere.lineIndices, textures),
    radius(sphere.radius),
    sectorCount(sphere.sectors),
    stackCount(sphere.stacks),
    globalColor(sphere.color) {}

sphere_mesh_struct SphereMesh::constructSphere(const float& radius,
                                               const unsigned int& sectors,
                                               const unsigned int& stacks,
                                               const glm::vec4& color) {
    sphere_mesh_struct sphere{
        .radius = radius,
        .sectors = sectors,
        .stacks = stacks,
        .color = color
    };

    sphere.vertices.reserve((stacks + 1) * (sectors + 1));
    sphere.indices.reserve((stacks - 1) * sectors * 6);
    sphere.lineIndices.reserve(stacks * sectors * 4 - 2 * sectors);

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

            sphere.vertices.push_back(Vertex{
                .position = pos,
                .normal = pos * lengthInv,
                .color = color,
                .texUV = glm::vec2((float)j / sectors, (float)i / stacks) });

            if (i != stacks && j != sectors) {
                // not top stack
                if (i != 0) {
                    sphere.indices.push_back(k1 + 1);
                    sphere.indices.push_back(k2);
                    sphere.indices.push_back(k1);
                }
                // not bottom stack
                if (i != (stacks - 1)) {
                    sphere.indices.push_back(k2 + 1);
                    sphere.indices.push_back(k2);
                    sphere.indices.push_back(k1 + 1);
                }

                sphere.lineIndices.push_back(k1);
                sphere.lineIndices.push_back(k2);
                if (i != 0) {
                    sphere.lineIndices.push_back(k1);
                    sphere.lineIndices.push_back(k1 + 1);
                }
            }
        }
    }

    return sphere;
}

void SphereMesh::setSectors(unsigned int sectors) {
    if (sectors == sectorCount || sectors < 3) { return; }
    this->sectorCount = sectors;

    sphere_mesh_struct cylinder = constructSphere(radius, sectors, stackCount, globalColor);

    updateMesh(cylinder.vertices, cylinder.indices);
    lineIndices = cylinder.lineIndices;
    setupLineVAO();
}

void SphereMesh::setStacks(unsigned int stacks) {
    if (stacks == stackCount || stacks < 2) { return; }
    this->stackCount = stacks;

    sphere_mesh_struct cylinder = constructSphere(radius, sectorCount, stacks, globalColor);

    updateMesh(cylinder.vertices, cylinder.indices);
    lineIndices = cylinder.lineIndices;
    setupLineVAO();
}
