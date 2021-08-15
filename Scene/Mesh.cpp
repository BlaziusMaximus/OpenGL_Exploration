#include "Mesh.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/ElementBuffer.h"
#include "Camera.h"

Mesh::Mesh(const std::vector<Vertex>& vertices,
           const std::vector<GLuint>& indices,
           const std::vector<GLuint>& lineIndices,
           const std::vector<Texture>& textures) :
    position(glm::vec3(0.0f)),
    meshMatrix(glm::mat4(1.0f)),
    vertices(vertices), indices(indices), lineIndices(lineIndices), textures(textures),
    lineShader("shaders/line.vert", "shaders/line.frag"),
    outlined(false),
    outlineShader("shaders/outline.vert", "shaders/outline.frag") {
    // binds vertex array object
    VAO.Bind();

    // generates and links vertex & element buffer objects to vertices & indices
    VertexBuffer VBO(vertices);
    ElementBuffer EBO(indices);

    // links VBO attributes to VAO
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    VAO.LinkAttrib(VBO, 2, 4, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(10 * sizeof(float)));
    // unbind after use
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();

    if (textures.size() == 0) {
        this->textures.push_back(Texture("textures/1X1_WHITE.png", "diffuse", 0));
        this->textures.push_back(Texture("textures/1X1_BLACK.png", "specular", 1));
    }
}

void Mesh::updateMesh(const std::vector<Vertex>& vertices,
                      const std::vector<GLuint>& indices) {
    this->vertices = vertices;
    this->indices = indices;

    // binds vertex array object
    VAO.Bind();

    // generates and links vertex & element buffer objects to vertices & indices
    VertexBuffer VBO(vertices);
    ElementBuffer EBO(indices);

    // links VBO attributes to VAO
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    VAO.LinkAttrib(VBO, 2, 4, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(10 * sizeof(float)));
    // unbind after use
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void Mesh::Draw(Shader& shader,
                Camera& camera,
                const glm::mat4& matrix) {
    if (outlined) {
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
    }

    shader.Activate();
    VAO.Bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (int i = 0; i < textures.size(); i++) {
        std::string material = "material.";
        std::string type = textures[i].type;

        textures[i].texUnit(shader, (material + type).c_str(), i);
        textures[i].Bind();
    }

    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.exportMatrix(shader, "camMatrix");

    glm::mat4 modelMatrix = meshMatrix * matrix;
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    if (glGetUniformLocation(shader.ID, "normalMatrix") != -1) {
        glm::mat3 normalMatrix(glm::transpose(glm::inverse(modelMatrix)));
        glUniformMatrix3fv(glGetUniformLocation(shader.ID, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    if (outlined) {
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);

        outlineShader.Activate();
        glUniform1f(glGetUniformLocation(outlineShader.ID, "outline"), 0.08f);
        camera.exportMatrix(outlineShader, "camMatrix");

        glUniformMatrix4fv(glGetUniformLocation(outlineShader.ID, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST);
    }
}

void Mesh::drawLines(Camera& camera) {
    lineShader.Activate();
    lineVAO.Bind();

    glUniform3f(glGetUniformLocation(lineShader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.exportMatrix(lineShader, "camMatrix");

    glUniformMatrix4fv(glGetUniformLocation(lineShader.ID, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(meshMatrix));

    glDrawElements(GL_LINES, lineIndices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::Translate(const glm::vec3& trans) {
    meshMatrix = glm::translate(trans) * meshMatrix;
    position = glm::translate(trans) * glm::vec4(position, 1.0f);
}
void Mesh::Translate(const float& transx, const float& transy, const float& transz) {
    glm::vec3 trans(transx, transy, transz);
    meshMatrix = glm::translate(trans) * meshMatrix;
    position = glm::translate(trans) * glm::vec4(position, 1.0f);
}
void Mesh::RotateLocal(const GLfloat& angle, const glm::vec3& axis) {
    glm::vec3 modelPosition = position;
    Translate(-modelPosition);
    meshMatrix = glm::mat4_cast(glm::angleAxis(angle, axis)) * meshMatrix;
    Translate(modelPosition);
}
void Mesh::RotateWorld(const GLfloat& angle, const glm::vec3& axis) {
    meshMatrix = glm::mat4_cast(glm::angleAxis(angle, axis)) * meshMatrix;
    position = glm::mat4_cast(glm::angleAxis(angle, axis)) * glm::vec4(position, 1.0f);
}
void Mesh::Scale(const glm::vec3& sca) {
    Translate(glm::vec3(0.0f, (sca.y - 1.0f) / 2.0f, 0.0f));
    glm::vec3 modelPosition = position;
    Translate(-modelPosition);
    meshMatrix = glm::scale(sca) * meshMatrix;
    Translate(modelPosition);
}

// Welp, this turned out to be unnecessary
// void Mesh::removeRedundantLines(std::vector<GLuint>& lineIndices) {
//     std::unordered_set<std::pair<GLuint, GLuint>, pair_hash> uset;

//     for (int i = 0; i < lineIndices.size(); i += 2) {
//         std::pair<GLuint, GLuint> line(lineIndices[i], lineIndices[i + 1]);
//         if (uset.find(line) == uset.end()) {
//             uset.emplace(line);
//         } else {
//             lineIndices.erase(lineIndices.begin() + i);
//             lineIndices.erase(lineIndices.begin() + i + 1);
//             i -= 2;
//         }
//     }
// }
