#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

class Shader;

class Texture {
public:
    // Reference ID of the Texture
    GLuint ID;
    const char* type;
    GLuint unit;
    // Constructor that generates a Texture
    Texture(const char* image, const char* texType, const GLuint& slot);

    void texUnit(Shader& shader, const char* uniform, const GLuint& unit);

    // Binds the Texture
    void Bind();
    // Unbinds the Texture
    void Unbind();
    // Deletes the Texture
    void Delete();
};