#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader {
public:
    // Reference ID of the Shader Program
    GLuint ID;
    // Constructor that build the Shader Program from 2 different shaders
    Shader(const char* vertexFile, const char* fragmentFile);

    // Activates the Shader Program
    void Activate();
    // Deletes the Shader Program
    void Delete();

    void setBool(const std::string& name, const bool& b);
    void setFloat(const std::string& name, const GLfloat& f);
    void setVec2(const std::string& name, const glm::vec2& v);
    void setVec2(const std::string& name, const float& x, const float& y);
    void setVec3(const std::string& name, const glm::vec3& v);
    void setVec3(const std::string& name, const float& x, const float& y, const float& z);
    void setVec4(const std::string& name, const glm::vec4& v);
    void setVec4(const std::string& name, const float& x, const float& y, const float& z, const float& w);

private:
    // Checks if the different Shaders have compiled properly
    void compileErrors(unsigned int& shader, const char* type);
};