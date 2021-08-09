#pragma once

#include "Mesh.h"

struct ico_mesh_struct : public mesh_struct {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<GLuint> lineIndices;

    float radius;
    unsigned int subdivisions;
};

const float X = 0.525731112119133606f;
const float Z = 0.850650808352039932f;
const float N = 0.0f;
const float S = 1.0f / 11.0f;
const float T = 1.0f / 3.0f;
const ico_mesh_struct ICOSAHEDRON{
    .vertices{
        Vertex{
            .position = glm::vec3(-X, N, Z),
            .texUV = glm::vec2(0.0f, T) },
        Vertex{
            .position = glm::vec3(X, N, Z),
            .texUV = glm::vec2(2 * S, T) },
        Vertex{
            .position = glm::vec3(-X, N, -Z),
            .texUV = glm::vec2(7 * S, 2 * T) },
        Vertex{
            .position = glm::vec3(X, N, -Z),
            .texUV = glm::vec2(5 * S, 2 * T) },

        Vertex{
            .position = glm::vec3(N, Z, X),
            .texUV = glm::vec2(S, 0.0f) },
        Vertex{
            .position = glm::vec3(N, Z, -X),
            .texUV = glm::vec2(6 * S, T) },
        Vertex{
            .position = glm::vec3(N, -Z, X),
            .texUV = glm::vec2(S, 2 * T) },
        Vertex{
            .position = glm::vec3(N, -Z, -X),
            .texUV = glm::vec2(2 * S, 3 * T) },

        Vertex{
            .position = glm::vec3(Z, X, N),
            .texUV = glm::vec2(4 * S, T) },
        Vertex{
            .position = glm::vec3(-Z, X, N),
            .texUV = glm::vec2(8 * S, T) },
        Vertex{
            .position = glm::vec3(Z, -X, N),
            .texUV = glm::vec2(3 * S, 2 * T) },
        Vertex{
            .position = glm::vec3(-Z, -X, N),
            .texUV = glm::vec2(9 * S, 2 * T) } },
    .indices{
        0, 4, 1,
        0, 9, 4,
        9, 5, 4,
        4, 5, 8,
        4, 8, 1,

        8, 10, 1,
        8, 3, 10,
        5, 3, 8,
        5, 2, 3,
        2, 7, 3,

        7, 10, 3,
        7, 6, 10,
        7, 11, 6,
        11, 0, 6,
        0, 1, 6,

        6, 1, 10,
        9, 0, 11,
        9, 11, 2,
        9, 2, 5,
        7, 2, 11 },
    .lineIndices{
        0, 1,
        0, 4,
        0, 6,
        0, 9,
        0, 11,
        1, 4,
        1, 6,
        1, 8,
        1, 10,
        2, 3,
        2, 5,
        2, 7,
        2, 9,
        2, 11,
        3, 5,
        3, 7,
        3, 8,
        3, 10,
        4, 5,
        4, 8,
        4, 9,
        5, 8,
        5, 9,
        6, 7,
        6, 10,
        6, 11,
        7, 10,
        7, 11,
        8, 10,
        9, 11 },
    .radius = 1.0f,
    .subdivisions = 0,
};

class IcosphereMesh : public Mesh {
private:
    float radius;
    unsigned int subdivisions;

    Shader lineShader;
    VertexArray lineVAO;
    std::vector<GLuint> lineIndices;

    static void constructSubdividedSphere(ico_mesh_struct& sphere, const unsigned int& subdivisions);

public:
    IcosphereMesh(const ico_mesh_struct& sphereMesh);
    IcosphereMesh(const ico_mesh_struct& sphereMesh, const std::vector<Texture>& textures);

    void setupLineVAO();

    static ico_mesh_struct constructSphere(const float& radius,
                                           const unsigned int& subdivisions,
                                           const glm::vec4& color = glm::vec4());

    void subdivideSphere(const unsigned int& subs);

    void drawLines(Camera& camera);
};