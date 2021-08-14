#pragma once

#include <json/json.h>

#include "Mesh.h"
#include "Shapes.h"

using json = nlohmann::json;

class Model {
public:
    glm::vec3 position;

public:
    Model(const char* file);

    void Draw(Shader& shader, Camera& camera);

    void Translate(const glm::vec3& trans);
    void RotateLocal(const GLfloat& angle, const glm::vec3& axis);
    void RotateWorld(const GLfloat& angle, const glm::vec3& axis);
    void Scale(const glm::vec3& sca);

    void showBoundingBox(const bool& show);

private:
    const char* file;
    std::vector<unsigned char> data;
    json JSON;

    std::vector<Mesh> meshes;
    std::vector<glm::vec3> translationsMeshes;
    std::vector<glm::quat> rotationsMeshes;
    std::vector<glm::vec3> scalesMeshes;
    std::vector<glm::mat4> matricesMeshes;

    std::vector<std::string> loadedTexNames;
    std::vector<Texture> loadedTexs;

    std::vector<Shapes::Cuboid> boundingBoxes;
    std::vector<Mesh> boundingBoxMeshes;
    Shader boundingBoxShader;
    bool drawBoundingBox;

    void loadMesh(const unsigned int& indMesh);

    // Traverses a node recursively, so it essentially traverses all connected nodes
    void traverseNode(const unsigned int& nextNode, const glm::mat4& matrix = glm::mat4(1.0f));

    std::vector<unsigned char> getData();
    std::vector<float> getFloats(json& accessor);
    std::vector<GLuint> getIndices(json& accessor);
    std::vector<Texture> getTextures(json& accessor);

    std::vector<Vertex> assembleVertices(const std::vector<glm::vec3>& positions,
                                         const std::vector<glm::vec3>& normals,
                                         const std::vector<glm::vec2>& texUVs);

    std::vector<glm::vec2> groupFloatsVec2(const std::vector<float>& floatVec);
    std::vector<glm::vec3> groupFloatsVec3(const std::vector<float>& floatVec);
    std::vector<glm::vec4> groupFloatsVec4(const std::vector<float>& floatVec);
};