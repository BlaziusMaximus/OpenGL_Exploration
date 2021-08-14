#include <iostream>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Scene/Scene.h"
#include "Scene/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include "FrameCounter.h"

void framebuffer_size_callback(GLFWwindow* window, GLsizei width, GLsizei height);
void processInput(GLFWwindow* window);

// settings
GLsizei SCR_WIDTH = 800;
GLsizei SCR_HEIGHT = 600;

int main() {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Review | Summer 2021", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // shader setup
    Shader lightShader("shaders/light.vert", "shaders/light.frag");
    Shader sphereShader("shaders/default.vert", "shaders/mesh.frag");

    // light properties and object setup
    glm::vec3 lightPos(0.0f);
    float lightSize = 0.1f;
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    lightShader.setVec4("lightColor", glm::vec4(lightColor, 1.0f));
    PointLight pointLight(sphereShader, "pointLight", glm::vec3(0.0f));
    // SphereMesh lightSphere(0.05f, 18, 9, glm::vec4(lightColor, 1.0f));

    DirLight dirLight(sphereShader, "dirLight");
    SpotLight spotLight(sphereShader, "spotLight", glm::vec3(0.0f), glm::vec3(0.0f));

    // enable depth buffer and set depth function
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // enable source-alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // camera
    Camera camera(&SCR_WIDTH, &SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    // const Model bunnyModel("models/bunny/scene.gltf");
    // std::vector<Model> models;
    // models.push_back(bunnyModel);

    std::array<LineVertex, 6> lineVertices = {
        LineVertex{ glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) },
        LineVertex{ glm::vec3(1.0f, 0.0f, 0.0f),
                    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) },

        LineVertex{ glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) },
        LineVertex{ glm::vec3(0.0f, 1.0f, 0.0f),
                    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) },

        LineVertex{ glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) },
        LineVertex{ glm::vec3(0.0f, 0.0f, 1.0f),
                    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) },
    };
    std::vector<LineVertex> lineVerts(lineVertices.begin(), lineVertices.end());
    Line line(lineVerts);
    Shader lineShader("shaders/line.vert", "shaders/line.frag");

    std::vector<Vertex> XZverts{
        Vertex{ .position = glm::vec3(0.0f, 0.0f, 0.0f),
                .normal = glm::vec3(0.0f, 1.0f, 0.0f),
                .color = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f) },

        Vertex{ .position = glm::vec3(2.0f, 0.0f, 0.0f),
                .normal = glm::vec3(0.0f, 1.0f, 0.0f),
                .color = glm::vec4(1.0f, 0.5f, 0.5f, 1.0f) },

        Vertex{ .position = glm::vec3(0.0f, 0.0f, 2.0f),
                .normal = glm::vec3(0.0f, 1.0f, 0.0f),
                .color = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f) },

        Vertex{ .position = glm::vec3(2.0f, 0.0f, 2.0f),
                .normal = glm::vec3(0.0f, 1.0f, 0.0f),
                .color = glm::vec4(1.0f, 0.5f, 1.0f, 1.0f) },
    };
    std::vector<GLuint> XZinds{
        0, 1, 3,
        0, 3, 2
    };
    Mesh XZ = Mesh(XZverts, XZinds);

    // std::vector<Texture> sphereTextures{
    //     Texture("textures/earthmap1k.jpg", "diffuse", 0),
    //     Texture("textures/earthspec1k.jpg", "specular", 1)
    // };
    // std::vector<Texture> icosphereTextures{
    //     Texture("textures/ico_earthmap_diffuse.jpg", "diffuse", 0),
    //     Texture("textures/ico_earthmap_specular.jpg", "specular", 1)
    // };
    std::vector<Texture> icosphereTextures{
        Texture("textures/ico_ex_diffuse.png", "diffuse", 0),
        Texture("textures/ico_ex_specular.png", "specular", 1)
    };
    // SphereMesh sphere(1.0f, 36, 18, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    // SphereMesh sphere(0.2f, 36, 18, sphereTextures);
    IcosphereMesh sphere(IcosphereMesh::constructSphere(1.0f, 0, glm::vec4(0.2f, 0.5f, 0.3f, 1.0f)), icosphereTextures);
    // sphere.Translate(1.0f, 0.0f, 0.0f);
    sphereShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    sphereShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    sphereShader.setVec3("material.specular", glm::vec3(0.5f));
    sphereShader.setFloat("material.shininess", 16.0f);

    // FPS
    FrameCounter fpsCounter(60);

    bool spaceIsPressed = false;

    srand((unsigned int)fpsCounter.currTime);

    // main loop
    while (!glfwWindowShouldClose(window)) {
        // std::cout << "FPS: " << fpsCounter.getFPS() << std::endl;
        if (fpsCounter.tick()) {
            // input
            processInput(window);
            camera.handleInputs(window);

            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spaceIsPressed) {
                // Model newModel = bunnyModel;
                // newModel.Translate(glm::vec3((float)(rand() % 100) / 100.0f, 1.0f, (float)(rand() % 100) / 100.0f));
                // models.push_back(newModel);
                // spotLight.switchOnOff();
                sphere.subdivideSphere(1);
                spaceIsPressed = true;
            }
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE && spaceIsPressed) {
                spaceIsPressed = false;
            }

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // update camera matrix
            camera.updateMatrix(45.0f, 0.1f, 100.0f);

            spotLight.setPosition(camera.Position + camera.Front * 0.5f + -glm::cross(camera.Right, camera.Front) * 0.1f + camera.Right * 0.2f);
            spotLight.setDirection(camera.Front);

            // pointLight.drawSphere(lightShader, camera);
            spotLight.drawSphere(lightShader, camera);

            // model.Translate(glm::vec3(0.0f, -0.001f, 0.0f));
            // model.RotateWorld(0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
            // model.RotateLocal(0.02f, glm::vec3(0.0f, 1.0f, 0.0f));
            // model.Scale((GLfloat)(glm::sin(fpsCounter.currTime * 5.0f) / 100.0f + 1.0f) * glm::vec3(1.0f));

            // for (Model& model : models) {
            //     model.Translate(glm::vec3(0.0f, -0.01f, 0.0f));
            //     model.Draw(shaderProgram, camera);
            // }
            // boundingBox.Draw(boxShader, camera);  //, model.matricesMeshes
            line.Draw(lineShader, camera);
            // XZ.Draw(shaderProgram, camera);

            // sphere.RotateLocal(-0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
            // sphere.RotateWorld(0.001f, glm::vec3(0.0f, 1.0f, 0.0f));

            sphere.Draw(sphereShader, camera);
            sphere.drawLines(camera);

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    // delete created objects
    sphereShader.Delete();
    lightShader.Delete();
    lineShader.Delete();

    // delete window
    glfwDestroyWindow(window);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, GLsizei width, GLsizei height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport(0, 0, width, height);
}