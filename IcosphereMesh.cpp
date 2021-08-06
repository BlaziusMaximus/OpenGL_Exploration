#include "IcosphereMesh.h"

IcosphereMesh::IcosphereMesh(const float& radius,
                             const unsigned int& subdivisions,
                             const std::vector<Texture>& textures) :
    Mesh(constructSphere(radius, subdivisions).vertices,
         constructSphere(radius, subdivisions).indices,
         textures),
    radius(radius),
    subdivisions(subdivisions) {
}

IcosphereMesh::IcosphereMesh(const float& radius,
                             const unsigned int& subdivisions,
                             const glm::vec4& color) :
    Mesh(constructSphere(radius, subdivisions, color).vertices,
         constructSphere(radius, subdivisions, color).indices),
    radius(radius),
    subdivisions(subdivisions) {
}

verts_inds IcosphereMesh::constructSphere(const float& radius,
                                          const unsigned int& subdivisions,
                                          const glm::vec4& color) {
    std::vector<Vertex> vertices;
    vertices.reserve(12);
    std::vector<GLuint> indices;
    std::vector<GLuint> lineIndices;

    const float T_ANGLE = PI / 180.0f * 72.0f;
    const float L_ANGLE = atanf(1.0f / 2.0f);

    float topAngle = -PI / 2.0f - T_ANGLE / 2.0f;
    float botAngle = -PI / 2.0f;

    const float projLineLength = radius * cosf(L_ANGLE);
    const float pointElevation = radius * sinf(L_ANGLE);

    glm::vec3 posT, posB;

    if (color != glm::vec4()) {
        vertices.push_back(Vertex{
            .position = glm::vec3(0.0f, radius, 0.0f),
            .normal = glm::vec3(0.0f, 1.0f, 0.0f),
            .color = color });
    } else {
        vertices.push_back(Vertex{
            .position = glm::vec3(0.0f, radius, 0.0f),
            .normal = glm::vec3(0.0f, 1.0f, 0.0f) });
    }

    for (int i = 1; i <= 5; i++) {
        posT.x = projLineLength * cosf(topAngle);
        posT.y = pointElevation;
        posT.z = projLineLength * sinf(topAngle);

        posB.x = projLineLength * cosf(topAngle);
        posB.y = -pointElevation;
        posB.z = projLineLength * sinf(botAngle);

        if (color != glm::vec4()) {
            vertices.push_back(Vertex{
                .position = posT,
                .normal = glm::normalize(posT),
                .color = color });
            vertices.push_back(Vertex{
                .position = posB,
                .normal = glm::normalize(posB),
                .color = color });
        } else {
            vertices.push_back(Vertex{
                .position = posT,
                .normal = glm::normalize(posT) });
            vertices.push_back(Vertex{
                .position = posB,
                .normal = glm::normalize(posB) });
        }
    }

    if (color != glm::vec4()) {
        vertices.push_back(Vertex{
            .position = glm::vec3(0.0f, -radius, 0.0f),
            .normal = glm::vec3(0.0f, -1.0f, 0.0f),
            .color = color });
    } else {
        vertices.push_back(Vertex{
            .position = glm::vec3(0.0f, -radius, 0.0f),
            .normal = glm::vec3(0.0f, -1.0f, 0.0f) });
    }

    return verts_inds{
        .vertices = vertices,
        .indices = indices,
        .lineIndices = lineIndices
    };
}
