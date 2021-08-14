#include "VertexArray.h"
#include "VertexBuffer.h"

// Constructor that generates a VAO ID
VertexArray::VertexArray() {
    glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
void VertexArray::LinkAttrib(VertexBuffer& VBO,
                             const GLuint& layout,
                             const GLuint& numComponents,
                             const GLenum& type,
                             const GLsizeiptr& stride,
                             void* offset) {
    VBO.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

// Binds the VAO
void VertexArray::Bind() {
    glBindVertexArray(ID);
}

// Unbinds the VAO
void VertexArray::Unbind() {
    glBindVertexArray(0);
}

// Deletes the VAO
void VertexArray::Delete() {
    glDeleteVertexArrays(1, &ID);
}