#include "Camera.h"
#include "../Renderer/Shader.h"

Camera::Camera(GLsizei* width, GLsizei* height, const glm::vec3& position) :
    width(width), height(height), aspect(0.0f),
    Position(position),
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), Up(glm::vec3(0.0f, 1.0f, 0.0f)), Right(glm::vec3(1.0f, 0.0f, 0.0f)),
    cameraMatrix(glm::mat4(1.0f)),
    speed(SLOW_SPEED), sensitivity(100.0f),
    usingCursor(true) {}

Camera::Camera(GLsizei* width, GLsizei* height, const float& aspect, const glm::vec3& position) :
    width(width), height(height), aspect(aspect),
    Position(position),
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), Up(glm::vec3(0.0f, 1.0f, 0.0f)), Right(glm::vec3(1.0f, 0.0f, 0.0f)),
    cameraMatrix(glm::mat4(1.0f)),
    speed(SLOW_SPEED), sensitivity(100.0f),
    usingCursor(true) {}

void Camera::updateMatrix(const float& FOVdeg, const float& nearPlane, const float& farPlane) {
    // initialize matrices
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    // build matrix with correct orientation
    view = glm::lookAt(Position, Position + Front, Up);
    // 3D -> 2D
    float aRatio = aspect != 0.0f ? aspect : (float)*width / (float)*height;
    proj = glm::perspective(glm::radians(FOVdeg), aRatio, nearPlane, farPlane);

    // output camera matrix
    cameraMatrix = proj * view;
}

void Camera::exportMatrix(Shader& shader, const char* uniform) {
    // export camera matrix to vertex shader
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::handleInputs(GLFWwindow* window) {
    // WASD
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        Position += speed * Front;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        Position += speed * -Right;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        Position += speed * -Front;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        Position += speed * Right;
    }
    // QE
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        Position += speed * -Up;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        Position += speed * Up;
    }
    // L_SHIFT
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed = FAST_SPEED;
    } else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        speed = SLOW_SPEED;
    }

    // mouse
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if (usingCursor) {
            // remember click position
            glfwGetCursorPos(window, &xpos, &ypos);
            glfwSetCursorPos(window, *width / 2, *height / 2);
        }
        usingCursor = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
        if (!usingCursor) { glfwSetCursorPos(window, xpos, ypos); }
        usingCursor = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    // rotate camera
    if (!usingCursor) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sensitivity * (float)(mouseX - ((float)*width / 2.)) / (float)*width;
        float rotY = sensitivity * (float)(mouseY - ((float)*height / 2.)) / (float)*height;

        glm::vec3 oldFront(Front);
        Front = glm::rotate(Front, glm::radians(-rotY), Right);
        float dot = glm::dot(glm::normalize(Front), glm::vec3(0.0f, 1.0f, 0.0f));
        if (dot > 0.99f || dot < -0.99f) {
            Front = oldFront;
        }

        Front = glm::rotate(Front, glm::radians(-rotX), Up);
        Right = glm::normalize(glm::cross(Front, Up));

        glfwSetCursorPos(window, (float)*width / 2., (float)*height / 2.);
    }
}