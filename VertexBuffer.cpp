#include "VertexBuffer.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices
template <typename T>
VertexBuffer::VertexBuffer(const std::vector<T>& vertices) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), GL_STATIC_DRAW);
}
template VertexBuffer::VertexBuffer<Vertex>(const std::vector<Vertex>& vertices);
template VertexBuffer::VertexBuffer<LineVertex>(const std::vector<LineVertex>& vertices);

// Binds the VBO
void VertexBuffer::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VertexBuffer::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VertexBuffer::Delete() {
    glDeleteBuffers(1, &ID);
}