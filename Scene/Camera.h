#pragma once

#include "Utils.h"

class Shader;

class Camera {
public:
    // window width/height
    GLsizei* width;
    GLsizei* height;

    // aspect ratio
    float aspect;

    // vectors & matrix for position and coordinate frame
    glm::vec3 Position;

    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;

    glm::mat4 cameraMatrix;

    // movement speed, mouse sensitivity
    float speed;
    float sensitivity;
    // cusor control logic variables
    bool usingCursor;
    double xpos, ypos;

    // construct camera
    Camera(GLsizei* width, GLsizei* height, const glm::vec3& position);
    Camera(GLsizei* width, GLsizei* height, const float& aspect, const glm::vec3& position);

    // update matrix and send to vertex shader
    void updateMatrix(const float& FOVdeg, const float& nearPlane, const float& farPlane);
    // export camera matrix to shader
    void exportMatrix(Shader& shader, const char* uniform);
    // handle inputs
    void handleInputs(GLFWwindow* window);

private:
    const float SLOW_SPEED = 0.05f;
    const float FAST_SPEED = 0.1f;
};