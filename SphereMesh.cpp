#include "SphereMesh.h"

SphereMesh::SphereMesh(const float& radius,
                       const unsigned int& sectors,
                       const unsigned int& stacks,
                       const std::vector<Texture>& textures) :
    Mesh(constructSphere(radius, sectors, stacks).vertices,
         constructSphere(radius, sectors, stacks).indices,
         textures),
    radius(radius),
    sectorCount(sectors),
    stackCount(stacks),
    lineShader("shaders/line.vert", "shaders/line.frag"),
    lineIndices(constructSphere(radius, sectors, stacks).lineIndices) {
    lineVAO.Bind();
    VertexBuffer lineVBO(vertices);
    ElementBuffer lineEBO(lineIndices);

    VAO.LinkAttrib(lineVBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    VAO.LinkAttrib(lineVBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

    lineVAO.Unbind();
    lineVBO.Unbind();
    lineEBO.Unbind();
}

SphereMesh::SphereMesh(const float& radius,
                       const unsigned int& sectors,
                       const unsigned int& stacks,
                       const glm::vec4& color) :
    Mesh(constructSphere(radius, sectors, stacks, color).vertices,
         constructSphere(radius, sectors, stacks, color).indices),
    radius(radius),
    sectorCount(sectors),
    stackCount(stacks),
    lineShader("shaders/line.vert", "shaders/line.frag"),
    lineIndices(constructSphere(radius, sectors, stacks, color).lineIndices) {
    lineVAO.Bind();
    VertexBuffer lineVBO(vertices);
    ElementBuffer lineEBO(lineIndices);

    VAO.LinkAttrib(lineVBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    VAO.LinkAttrib(lineVBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

    lineVAO.Unbind();
    lineVBO.Unbind();
    lineEBO.Unbind();
}

void SphereMesh::drawLines(Camera& camera) {
    lineShader.Activate();
    lineVAO.Bind();

    glUniform3f(glGetUniformLocation(lineShader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.exportMatrix(lineShader, "camMatrix");

    glUniformMatrix4fv(glGetUniformLocation(lineShader.ID, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(meshMatrix));

    glDrawElements(GL_LINES, lineIndices.size(), GL_UNSIGNED_INT, 0);
}

mesh_struct SphereMesh::constructSphere(const float& radius,
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

    return mesh_struct{
        .vertices = vertices,
        .indices = indices,
        .lineIndices = lineIndices
    };
}
