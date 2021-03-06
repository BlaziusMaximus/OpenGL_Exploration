#include "Model.h"
#include "Renderer/Texture.h"

Model::Model(const char* file) :
    position(glm::vec3(0.0f, 0.0f, 0.0f)),
    boundingBoxShader("shaders/default.vert", "shaders/box.frag"),
    drawBoundingBox(false) {
    std::string text = get_file_contents(file);
    JSON = json::parse(text);

    Model::file = file;
    data = getData();

    traverseNode(0);
}

Model::~Model() {
    std::vector<unsigned char>().swap(data);
    json().swap(JSON);

    std::vector<Mesh>().swap(meshes);
    std::vector<glm::vec3>().swap(translationsMeshes);
    std::vector<glm::quat>().swap(rotationsMeshes);
    std::vector<glm::vec3>().swap(scalesMeshes);
    std::vector<glm::mat4>().swap(matricesMeshes);

    std::vector<std::string>().swap(loadedTexNames);
    std::vector<Texture>().swap(loadedTexs);

    std::vector<Shapes::Cuboid>().swap(boundingBoxes);
    std::vector<Mesh>().swap(boundingBoxMeshes);
    boundingBoxShader.Delete();
}

void Model::Draw(Shader& shader, Camera& camera) {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Mesh::Draw(shader, camera, matricesMeshes[i]);  // , translationsMeshes[i], rotationsMeshes[i], scalesMeshes[i]
        if (drawBoundingBox) { boundingBoxMeshes[i].Draw(boundingBoxShader, camera, matricesMeshes[i]); }
    }
}

void Model::Translate(const glm::vec3& trans) {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        // translationsMeshes[i] += trans;
        matricesMeshes[i] = glm::translate(-trans) * matricesMeshes[i];
        position = glm::translate(-trans) * glm::vec4(position, 1.0f);
    }
}
void Model::RotateLocal(const GLfloat& angle, const glm::vec3& axis) {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        // rotationsMeshes[i] *= rot;
        glm::vec3 modelPosition = position;
        Translate(-modelPosition);
        matricesMeshes[i] = glm::mat4_cast(glm::angleAxis(angle, axis)) * matricesMeshes[i];
        Translate(modelPosition);
    }
}
void Model::RotateWorld(const GLfloat& angle, const glm::vec3& axis) {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        // rotationsMeshes[i] *= rot;
        matricesMeshes[i] = glm::mat4_cast(glm::angleAxis(angle, axis)) * matricesMeshes[i];
        position = glm::mat4_cast(glm::angleAxis(angle, axis)) * glm::vec4(position, 1.0f);
    }
}
void Model::Scale(const glm::vec3& sca) {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        // scalesMeshes[i] += sca;
        Translate(glm::vec3(0.0f, (sca.y - 1.0f) / 2.0f, 0.0f));
        glm::vec3 modelPosition = position;
        Translate(-modelPosition);
        matricesMeshes[i] = glm::scale(sca) * matricesMeshes[i];
        Translate(modelPosition);
    }
}

void Model::showBoundingBox(const bool& show) {
    drawBoundingBox = show;
}

void Model::loadMesh(const unsigned int& indMesh) {
    // Get all accessor indices
    unsigned int posAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
    unsigned int normalAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
    unsigned int texAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
    unsigned int indAccInd = JSON["meshes"][indMesh]["primitives"][0]["indices"];

    // Use accessor indices to get all vertices components
    std::vector<float> posVec = getFloats(JSON["accessors"][posAccInd]);
    std::vector<glm::vec3> positions = groupFloatsVec3(posVec);
    std::vector<float> normalVec = getFloats(JSON["accessors"][normalAccInd]);
    std::vector<glm::vec3> normals = groupFloatsVec3(normalVec);
    std::vector<float> texVec = getFloats(JSON["accessors"][texAccInd]);
    std::vector<glm::vec2> texUVs = groupFloatsVec2(texVec);

    // Combine all the vertex components and also get the indices and textures
    std::vector<Vertex> vertices = assembleVertices(positions, normals, texUVs);
    std::vector<GLuint> indices = getIndices(JSON["accessors"][indAccInd]);
    std::vector<Texture> textures = getTextures(JSON["accessors"][texAccInd]);

    // Combine the vertices, indices, and textures into a mesh
    meshes.push_back(Mesh(vertices, indices, std::vector<GLuint>(), textures));

    json jsonMin = JSON["accessors"][posAccInd]["min"];
    json jsonMax = JSON["accessors"][posAccInd]["max"];
    glm::vec3 minVec = getMin(positions);  //glm::vec3(jsonMin[0], jsonMin[1], jsonMin[2]);
    glm::vec3 maxVec = getMax(positions);  //glm::vec3(jsonMax[0], jsonMax[1], jsonMax[2]);

    Shapes::Cuboid bBox = Shapes::Cuboid(minVec, maxVec, glm::vec4(0.8f, 0.0f, 0.1f, 0.25f));
    boundingBoxes.push_back(bBox);
    boundingBoxMeshes.push_back(Mesh(bBox.vertices, bBox.indices));
}

void Model::traverseNode(const unsigned int& nextNode, const glm::mat4& matrix) {
    // Current node
    json node = JSON["nodes"][nextNode];

    // Get translation if it exists
    glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
    if (node.find("translation") != node.end()) {
        float transValues[3];
        for (unsigned int i = 0; i < node["translation"].size(); i++)
            transValues[i] = (node["translation"][i]);
        translation = glm::make_vec3(transValues);
        position = glm::translate(translation) * glm::vec4(position, 1.0f);
    }
    // Get quaternion if it exists
    glm::quat rotation = glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    if (node.find("rotation") != node.end()) {
        float rotValues[4] = {
            node["rotation"][3],
            node["rotation"][0],
            node["rotation"][1],
            node["rotation"][2]
        };
        rotation = glm::make_quat(rotValues);  // * glm::quat(0.0f, 0.7071068f, 0.0f, 0.7071068f);
    }
    // Get scale if it exists
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    if (node.find("scale") != node.end()) {
        float scaleValues[3];
        for (unsigned int i = 0; i < node["scale"].size(); i++)
            scaleValues[i] = (node["scale"][i]);
        scale = glm::make_vec3(scaleValues);
    }
    // Get matrix if it exists
    glm::mat4 matNode = glm::mat4(1.0f);
    if (node.find("matrix") != node.end()) {
        float matValues[16];
        for (unsigned int i = 0; i < node["matrix"].size(); i++)
            matValues[i] = (node["matrix"][i]);
        matNode = glm::make_mat4(matValues);
    }

    // Initialize matrices
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    // Use translation, rotation, and scale to change the initialized matrices
    trans = glm::translate(trans, translation);
    rot = glm::mat4_cast(rotation);
    sca = glm::scale(sca, scale);

    // Multiply all matrices together
    glm::mat4 matNextNode = matrix * matNode * trans * rot * sca;

    // Check if the node contains a mesh and if it does load it
    if (node.find("mesh") != node.end()) {
        translationsMeshes.push_back(translation);
        rotationsMeshes.push_back(rotation);
        scalesMeshes.push_back(scale);
        matricesMeshes.push_back(matNextNode);

        loadMesh(node["mesh"]);
    }

    // rotate about Y 90 deg
    RotateLocal(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    // Check if the node has children, and if it does, apply this function to them with the matNextNode
    if (node.find("children") != node.end()) {
        for (unsigned int i = 0; i < node["children"].size(); i++)
            traverseNode(node["children"][i], matNextNode);
    }
}

std::vector<unsigned char> Model::getData() {
    std::string bytesText;
    std::string uri = JSON["buffers"][0]["uri"];

    std::string fileStr = std::string(file);
    std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
    bytesText = get_file_contents((fileDirectory + uri).c_str());

    std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
    return data;
}

std::vector<float> Model::getFloats(json& accessor) {
    std::vector<float> floatVec;

    unsigned int buffViewInd = accessor.value("bufferView", 1);
    unsigned int count = accessor["count"];
    unsigned int accByteOffset = accessor.value("byteOffset", 0);
    std::string type = accessor["type"];

    json bufferView = JSON["bufferViews"][buffViewInd];
    unsigned int byteOffset = bufferView["byteOffset"];

    unsigned int numPerVert;
    if (type == "SCALAR") {
        numPerVert = 1;
    } else if (type == "VEC2") {
        numPerVert = 2;
    } else if (type == "VEC3") {
        numPerVert = 3;
    } else if (type == "VEC4") {
        numPerVert = 4;
    } else {
        throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3, or VEC4)");
    }

    unsigned int beginningOfData = byteOffset + accByteOffset;
    unsigned int lengthOfData = count * 4 * numPerVert;
    for (unsigned int i = beginningOfData; i < beginningOfData + lengthOfData; i) {
        unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
        float value;
        std::memcpy(&value, bytes, sizeof(float));
        floatVec.push_back(value);
    }

    return floatVec;
}

std::vector<GLuint> Model::getIndices(json& accessor) {
    std::vector<GLuint> indices;

    // Get properties from the accessor
    unsigned int buffViewInd = accessor.value("bufferView", 0);
    unsigned int count = accessor["count"];
    unsigned int accByteOffset = accessor.value("byteOffset", 0);
    unsigned int componentType = accessor["componentType"];

    // Get properties from the bufferView
    json bufferView = JSON["bufferViews"][buffViewInd];
    unsigned int byteOffset = bufferView["byteOffset"];

    // Get indices with regards to their type: unsigned int, unsigned short, or short
    unsigned int beginningOfData = byteOffset + accByteOffset;
    if (componentType == 5125) {
        for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i) {
            unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
            unsigned int value;
            std::memcpy(&value, bytes, sizeof(unsigned int));
            indices.push_back((GLuint)value);
        }
    } else if (componentType == 5123) {
        for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i) {
            unsigned char bytes[] = { data[i++], data[i++] };
            unsigned short value;
            std::memcpy(&value, bytes, sizeof(unsigned short));
            indices.push_back((GLuint)value);
        }
    } else if (componentType == 5122) {
        for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i) {
            unsigned char bytes[] = { data[i++], data[i++] };
            short value;
            std::memcpy(&value, bytes, sizeof(short));
            indices.push_back((GLuint)value);
        }
    }

    return indices;
}

std::vector<Texture> Model::getTextures(json& accessor) {
    std::vector<Texture> textures;

    std::string fileStr = std::string(file);
    std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);

    for (unsigned int i = 0; i < JSON["images"].size(); i++) {
        std::string texPath = JSON["images"][i]["uri"];

        bool skip = false;
        for (unsigned int j = 0; j < loadedTexNames.size(); j++) {
            if (loadedTexNames[j] == texPath) {
                textures.push_back(loadedTexs[j]);
                skip = true;
                break;
            }
        }

        if (!skip) {
            if (texPath.find("baseColor") != std::string::npos) {
                Texture diffuse = Texture((fileDirectory + texPath).c_str(), "diffuse", loadedTexs.size());
                textures.push_back(diffuse);
                loadedTexs.push_back(diffuse);
                loadedTexNames.push_back(texPath);
            } else if (texPath.find("metallicRoughness") != std::string::npos) {
                Texture specular = Texture((fileDirectory + texPath).c_str(), "specular", loadedTexs.size());
                textures.push_back(specular);
                loadedTexs.push_back(specular);
                loadedTexNames.push_back(texPath);
            }
        }
    }

    return textures;
}

std::vector<Vertex> Model::assembleVertices(const std::vector<glm::vec3>& positions,
                                            const std::vector<glm::vec3>& normals,
                                            const std::vector<glm::vec2>& texUVs) {
    std::vector<Vertex> vertices;
    vertices.reserve(positions.size());

    for (int i = 0; i < positions.size(); i++) {
        vertices.push_back(
            Vertex{
                positions[i],
                normals[i],
                glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                texUVs[i] });
    }

    return vertices;
}

std::vector<glm::vec2> Model::groupFloatsVec2(const std::vector<float>& floatVec) {
    std::vector<glm::vec2> vectors;
    vectors.reserve(floatVec.size());

    for (int i = 0; i < floatVec.size(); i) {
        vectors.emplace_back(floatVec[i++], floatVec[i++]);
    }

    return vectors;
}

std::vector<glm::vec3> Model::groupFloatsVec3(const std::vector<float>& floatVec) {
    std::vector<glm::vec3> vectors;
    vectors.reserve(floatVec.size());

    for (int i = 0; i < floatVec.size(); i) {
        vectors.emplace_back(floatVec[i++], floatVec[i++], floatVec[i++]);
    }

    return vectors;
}

std::vector<glm::vec4> Model::groupFloatsVec4(const std::vector<float>& floatVec) {
    std::vector<glm::vec4> vectors;
    vectors.reserve(floatVec.size());

    for (int i = 0; i < floatVec.size(); i) {
        vectors.emplace_back(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]);
    }

    return vectors;
}
