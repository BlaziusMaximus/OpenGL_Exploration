#pragma once

#include <glad/glad.h>

class VertexBuffer;

class VertexArray {
public:
    // ID reference for the Vertex Array Object
    GLuint ID;
    // Constructor that generates a VAO ID
    VertexArray();

    // Links a VBO to the VAO using a certain layout
    void LinkAttrib(VertexBuffer& VBO,
                    const GLuint& layout,
                    const GLuint& numComponents,
                    const GLenum& type,
                    const GLsizeiptr& stride,
                    void* offset);

    // Binds the VAO
    void Bind();
    // Unbinds the VAO
    void Unbind();
    // Deletes the VAO
    void Delete();
};