#include "IcosphereMesh.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/ElementBuffer.h"

IcosphereMesh::IcosphereMesh(const ico_mesh_struct& sphereMesh) :
    Mesh(sphereMesh.vertices, sphereMesh.indices),
    radius(sphereMesh.radius),
    subdivisions(sphereMesh.subdivisions),
    lineShader("shaders/line.vert", "shaders/line.frag"),
    lineIndices(sphereMesh.lineIndices) {
    setupLineVAO();
}

IcosphereMesh::IcosphereMesh(const ico_mesh_struct& sphereMesh, const std::vector<Texture>& textures) :
    Mesh(sphereMesh.vertices, sphereMesh.indices, textures),
    radius(sphereMesh.radius),
    subdivisions(sphereMesh.subdivisions),
    lineShader("shaders/line.vert", "shaders/line.frag"),
    lineIndices(sphereMesh.lineIndices) {
    setupLineVAO();
}

void IcosphereMesh::setupLineVAO() {
    lineVAO.Bind();
    VertexBuffer lineVBO(vertices);
    ElementBuffer lineEBO(lineIndices);

    VAO.LinkAttrib(lineVBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    VAO.LinkAttrib(lineVBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

    lineVAO.Unbind();
    lineVBO.Unbind();
    lineEBO.Unbind();
}

ico_mesh_struct IcosphereMesh::constructSphere(const float& radius,
                                               const unsigned int& subdivisions,
                                               const glm::vec4& color) {
    ico_mesh_struct sphere = ICOSAHEDRON;
    sphere.radius = radius;
    for (Vertex& v : sphere.vertices) {
        v.position *= radius;
        v.normal = glm::normalize(v.position);
        v.color = color;
    }

    if (subdivisions <= 0) { return sphere; }

    constructSubdividedSphere(sphere, subdivisions);

    return sphere;
}

void IcosphereMesh::constructSubdividedSphere(ico_mesh_struct& sphere, const unsigned int& subdivisions) {
    Vertex v0, v1, v2;  // original vertices for a given triangle
    Vertex s0, s1, s2;  // new, subdivided vertices
    GLuint new_ind = sphere.vertices.size();

    for (unsigned int sub = 1; sub <= subdivisions; sub++) {
        const int numTriangles = sphere.indices.size() / 3;

        sphere.vertices.reserve(sphere.vertices.size() * 2);
        sphere.indices.reserve(numTriangles * 4 * 3);

        sphere.lineIndices.clear();
        sphere.lineIndices.reserve(numTriangles * 9 * 2);

        for (GLuint i = 0; i < numTriangles; i++, new_ind += 3) {
            v0 = sphere.vertices[sphere.indices[0]];
            v1 = sphere.vertices[sphere.indices[1]];
            v2 = sphere.vertices[sphere.indices[2]];

            s0.position = (v0.position + v1.position) * (sphere.radius / sqrtf(glm::dot(v0.position + v1.position, v0.position + v1.position)));
            s0.normal = glm::normalize(s0.position);
            s0.color = glm::mix(v0.color, v1.color, 0.5f);
            s0.texUV = glm::mix(v0.texUV, v1.texUV, 0.5f);

            s1.position = (v2.position + v1.position) * (sphere.radius / sqrtf(glm::dot(v2.position + v1.position, v2.position + v1.position)));
            s1.normal = glm::normalize(s0.position);
            s1.color = glm::mix(v2.color, v1.color, 0.5f);
            s1.texUV = glm::mix(v2.texUV, v1.texUV, 0.5f);

            s2.position = (v0.position + v2.position) * (sphere.radius / sqrtf(glm::dot(v0.position + v2.position, v0.position + v2.position)));
            s2.normal = glm::normalize(s0.position);
            s2.color = glm::mix(v0.color, v2.color, 0.5f);
            s2.texUV = glm::mix(v0.texUV, v2.texUV, 0.5f);

            sphere.vertices.push_back(s0);
            sphere.vertices.push_back(s1);
            sphere.vertices.push_back(s2);

            sphere.indices.push_back(sphere.indices[0]);
            sphere.indices.push_back(new_ind + 0);
            sphere.indices.push_back(new_ind + 2);

            sphere.indices.push_back(new_ind + 0);
            sphere.indices.push_back(sphere.indices[1]);
            sphere.indices.push_back(new_ind + 1);

            sphere.indices.push_back(new_ind + 0);
            sphere.indices.push_back(new_ind + 1);
            sphere.indices.push_back(new_ind + 2);

            sphere.indices.push_back(new_ind + 2);
            sphere.indices.push_back(new_ind + 1);
            sphere.indices.push_back(sphere.indices[2]);

            sphere.lineIndices.push_back(sphere.indices[0]);
            sphere.lineIndices.push_back(new_ind + 0);

            sphere.lineIndices.push_back(new_ind + 0);
            sphere.lineIndices.push_back(new_ind + 2);

            sphere.lineIndices.push_back(new_ind + 2);
            sphere.lineIndices.push_back(sphere.indices[0]);

            sphere.lineIndices.push_back(new_ind + 0);
            sphere.lineIndices.push_back(sphere.indices[1]);

            sphere.lineIndices.push_back(sphere.indices[1]);
            sphere.lineIndices.push_back(new_ind + 1);

            sphere.lineIndices.push_back(new_ind + 1);
            sphere.lineIndices.push_back(new_ind + 0);

            sphere.lineIndices.push_back(new_ind + 2);
            sphere.lineIndices.push_back(new_ind + 1);

            sphere.lineIndices.push_back(new_ind + 1);
            sphere.lineIndices.push_back(sphere.indices[2]);

            sphere.lineIndices.push_back(sphere.indices[2]);
            sphere.lineIndices.push_back(new_ind + 2);

            sphere.indices.erase(sphere.indices.begin(), sphere.indices.begin() + 3);
        }
    }
}

void IcosphereMesh::subdivideSphere(const unsigned int& subs) {
    if (subs <= 0) { return; }

    ico_mesh_struct sphere{
        .vertices = vertices,
        .indices = indices,
        .lineIndices = lineIndices,
        .radius = radius,
        .subdivisions = subdivisions
    };

    constructSubdividedSphere(sphere, subs);

    updateMesh(sphere.vertices, sphere.indices);
    lineIndices = sphere.lineIndices;
    setupLineVAO();
    subdivisions += subs;
}

void IcosphereMesh::drawLines(Camera& camera) {
    lineShader.Activate();
    lineVAO.Bind();

    glUniform3f(glGetUniformLocation(lineShader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.exportMatrix(lineShader, "camMatrix");

    glUniformMatrix4fv(glGetUniformLocation(lineShader.ID, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(meshMatrix));

    glDrawElements(GL_LINES, lineIndices.size(), GL_UNSIGNED_INT, 0);
}
