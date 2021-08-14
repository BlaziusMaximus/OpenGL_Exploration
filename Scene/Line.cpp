#include "Line.h"
#include "Renderer/VertexBuffer.h"

Line::Line(const std::vector<LineVertex>& vertices) :
    vertices(vertices) {
    // binds vertex array object
    VAO.Bind();

    // generates and links vertex buffer object to vertices
    VertexBuffer VBO(vertices);

    // links VBO attributes to VAO
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(LineVertex), (void*)0);
    VAO.LinkAttrib(VBO, 1, 4, GL_FLOAT, sizeof(LineVertex), (void*)(3 * sizeof(float)));
    // unbind after use
    VAO.Unbind();
    VBO.Unbind();
}

void Line::Draw(Shader& shader,
                Camera& camera,
                const glm::mat4& matrix) {
    shader.Activate();
    VAO.Bind();

    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.exportMatrix(shader, "camMatrix");

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

    glDrawArrays(GL_LINES, 0, vertices.size());
}
