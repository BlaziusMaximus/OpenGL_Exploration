#pragma once

#include "Scene/Mesh.h"

#define G_RECT_W 0.525731112119133606f
#define G_RECT_L 0.850650808352039932f

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
        //                                              ROW_COL  i
        Vertex{ //                                      0_0      0
                .position = glm::vec3(N, Z, X),
                .texUV = glm::vec2(1 * S, 1 - 0.0f) },
        Vertex{ //                                      0_1      1
                .position = glm::vec3(N, Z, X),
                .texUV = glm::vec2(3 * S, 1 - 0.0f) },
        Vertex{ //                                      0_2      2
                .position = glm::vec3(N, Z, X),
                .texUV = glm::vec2(5 * S, 1 - 0.0f) },
        Vertex{ //                                      0_3      3
                .position = glm::vec3(N, Z, X),
                .texUV = glm::vec2(7 * S, 1 - 0.0f) },
        Vertex{ //                                      0_4      4
                .position = glm::vec3(N, Z, X),
                .texUV = glm::vec2(9 * S, 1 - 0.0f) },

        Vertex{ //                                      1_0      5
                .position = glm::vec3(-X, N, Z),
                .texUV = glm::vec2(0 * S, 1 - T) },
        Vertex{ //                                      1_1      6
                .position = glm::vec3(X, N, Z),
                .texUV = glm::vec2(2 * S, 1 - T) },
        Vertex{ //                                      1_2      7
                .position = glm::vec3(Z, X, N),
                .texUV = glm::vec2(4 * S, 1 - T) },
        Vertex{ //                                      1_3      8
                .position = glm::vec3(N, Z, -X),
                .texUV = glm::vec2(6 * S, 1 - T) },
        Vertex{ //                                      1_4      9
                .position = glm::vec3(-Z, X, N),
                .texUV = glm::vec2(8 * S, 1 - T) },
        Vertex{ //                                      1_5      10
                .position = glm::vec3(-X, N, Z),
                .texUV = glm::vec2(10 * S, 1 - T) },

        Vertex{ //                                      2_0      11
                .position = glm::vec3(N, -Z, X),
                .texUV = glm::vec2(1 * S, 1 - 2 * T) },
        Vertex{ //                                      2_1      12
                .position = glm::vec3(Z, -X, N),
                .texUV = glm::vec2(3 * S, 1 - 2 * T) },
        Vertex{ //                                      2_2      13
                .position = glm::vec3(X, N, -Z),
                .texUV = glm::vec2(5 * S, 1 - 2 * T) },
        Vertex{ //                                      2_3      14
                .position = glm::vec3(-X, N, -Z),
                .texUV = glm::vec2(7 * S, 1 - 2 * T) },
        Vertex{ //                                      2_4      15
                .position = glm::vec3(-Z, -X, N),
                .texUV = glm::vec2(9 * S, 1 - 2 * T) },
        Vertex{ //                                      2_5      16
                .position = glm::vec3(N, -Z, X),
                .texUV = glm::vec2(11 * S, 1 - 2 * T) },

        Vertex{ //                                      3_0      17
                .position = glm::vec3(N, -Z, -X),
                .texUV = glm::vec2(2 * S, 1 - 3 * T) },
        Vertex{ //                                      3_1      18
                .position = glm::vec3(N, -Z, -X),
                .texUV = glm::vec2(4 * S, 1 - 3 * T) },
        Vertex{ //                                      3_2      19
                .position = glm::vec3(N, -Z, -X),
                .texUV = glm::vec2(6 * S, 1 - 3 * T) },
        Vertex{ //                                      3_3      20
                .position = glm::vec3(N, -Z, -X),
                .texUV = glm::vec2(8 * S, 1 - 3 * T) },
        Vertex{ //                                      3_4      21
                .position = glm::vec3(N, -Z, -X),
                .texUV = glm::vec2(10 * S, 1 - 3 * T) } },
    .indices{
        0, 5, 6,
        1, 6, 7,
        2, 7, 8,
        3, 8, 9,
        4, 9, 10,
        5, 6, 11,
        6, 7, 12,
        7, 8, 13,
        8, 9, 14,
        9, 10, 15,
        6, 11, 12,
        7, 12, 13,
        8, 13, 14,
        9, 14, 15,
        10, 15, 16,
        11, 12, 17,
        12, 13, 18,
        13, 14, 19,
        14, 15, 20,
        15, 16, 21 },
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