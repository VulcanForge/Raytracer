#include "Image.h"

#include <GL/glew.h>

#include <ShaderProgram.h>

#include "stb_image_write.h"

// Coordinates / texture coordinates of canvas
constexpr float vertices[]
{
    -1, -1, 0, 0,
    -1, 1, 0, 1,
    1, -1, 1, 0,
    1, 1, 1, 1
};

constexpr unsigned int indices[] {0, 2, 3, 0, 3, 1};

Image::Image (unsigned int width, unsigned int height, std::unique_ptr<std::vector<unsigned char>>&& rgb)
    : width {width}, height {height}, rgb {std::move (rgb)}
{}

void Image::Render ()
{
    GLuint imageVAO, imageVBO, imageEBO, imageTexture;
    std::unique_ptr<ShaderProgram> imageShader;

    glGenVertexArrays (1, &imageVAO);
    glBindVertexArray (imageVAO);

    glGenBuffers (1, &imageVBO);
    glBindBuffer (GL_ARRAY_BUFFER, imageVBO);
    glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof (GLfloat), (void*)0);
    glEnableVertexAttribArray (0);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof (GLfloat), (void*)(2 * sizeof (GLfloat)));
    glEnableVertexAttribArray (1);

    glGenBuffers (1, &imageEBO);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, imageEBO);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);

    glActiveTexture (GL_TEXTURE0);
    glGenTextures (1, &imageTexture);
    glBindTexture (GL_TEXTURE_2D, imageTexture);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb->data ());
    glGenerateMipmap (GL_TEXTURE_2D);

    imageShader = ShaderProgram::CreateBasicShaderProgramWithNames ("Image", "Shaders/Image.vert", "Shaders/Image.frag");
    imageShader->UseProgram ();
    imageShader->SetUniformSampler ("imageTexture", 0);

    glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

    glDeleteTextures (1, &imageTexture);
    glDeleteBuffers (1, &imageEBO);
    glDeleteBuffers (1, &imageVBO);
    glDeleteVertexArrays (1, &imageVAO);
}

void Image::SaveToPNG (const std::string& filename) const
{
    stbi_flip_vertically_on_write (true);
    stbi_write_png (filename.c_str (), width, height, 3, rgb->data (), 3 * width);
}
