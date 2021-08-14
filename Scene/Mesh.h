#pragma once

#include "Drawable.h"
#include "../Renderer/Texture.h"

#include <string>

class VertexArray;
class ElementBuffer;

struct mesh_struct {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<GLuint> lineIndices;
};

class Mesh : public Drawable {
protected:
    glm::vec3 position;
    glm::mat4 meshMatrix;

    // void removeRedundantLines(std::vector<GLuint>& lineIndices);

public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    Mesh(const std::vector<Vertex>& vertices,
         const std::vector<GLuint>& indices,
         const std::vector<Texture>& textures = std::vector<Texture>());

    void updateMesh(const std::vector<Vertex>& vertices,
                    const std::vector<GLuint>& indices);

    void Draw(Shader& shader,
              Camera& camera,
              const glm::mat4& matrix = glm::mat4(1.0f));

    void Translate(const glm::vec3& trans);
    void Translate(const float& tx, const float& ty, const float& tz);
    void RotateLocal(const GLfloat& angle, const glm::vec3& axis);
    void RotateWorld(const GLfloat& angle, const glm::vec3& axis);
    void Scale(const glm::vec3& sca);
};
