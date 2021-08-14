#pragma once

#include "Utils.h"

class VertexBuffer {
public:
    // Reference ID of the Vertex Buffer Object
    GLuint ID;
    // Constructor that generates a Vertex Buffer Object and links it to vertices
    template <typename T>
    VertexBuffer(const std::vector<T>& vertices);

    // Binds the VBO
    void Bind();
    // Unbinds the VBO
    void Unbind();
    // Deletes the VBO
    void Delete();
};