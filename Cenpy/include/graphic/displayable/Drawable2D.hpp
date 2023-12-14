#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

class Drawable2D : public SceneNode
{
public:
    Drawable2D(float x, float y, float size)
    {
        // Calculate the coordinates of the other vertices based on the upper left vertex and size
        GLfloat vertices[] = {
            // Positions      // Texture Coords
            x + size, y, 0.0f, 1.0f, 1.0f,        // Top Right
            x + size, y - size, 0.0f, 1.0f, 0.0f, // Bottom Right
            x, y - size, 0.0f, 0.0f, 0.0f,        // Bottom Left
            x, y, 0.0f, 0.0f, 1.0f                // Top Left
        };

        // Define indices to form two triangles for a square
        GLuint indices[] = {
            0, 1, 3, // First Triangle
            1, 2, 3  // Second Triangle
        };

        // Generate vertex array object (VAO), vertex buffer object (VBO), and element buffer object (EBO)
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind the vertex array object (VAO)
        glBindVertexArray(VAO);

        // Bind and fill the vertex buffer object (VBO) with vertex data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Bind and fill the element buffer object (EBO) with index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Specify the vertex attribute pointers for positions and texture coordinates
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        // Unbind the vertex array object (VAO) to prevent accidental modification
        glBindVertexArray(0);
    }

    void draw() const override
    {
        m_shader.use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    /**
     * @brief The vertex array object
     *
     * @details A VAO is an OpenGL object that stores the configuration of vertex attribute pointers and bindings.
     * It encapsulates the setup for rendering with VBOs, specifying how vertex data is organized and how it should be interpreted by shaders.
     * VAOs help simplify the process of switching between different sets of vertex data.
     */
    GLuint VAO;

    /**
     * @brief The vertex buffer object
     *
     * @details A VBO is a buffer in the GPU's memory that stores vertex data, such as positions, colors, normals, and texture coordinates.
     * Instead of sending vertex data to the GPU for each frame, you can store it in a VBO, which allows for more efficient rendering
     */
    GLuint VBO;

    /**
     * @brief The element buffer object
     *
     * @details An EBO, also known as an Index Buffer, is a buffer in the GPU's memory that stores indices.
     * Instead of duplicating vertex data for shared vertices among multiple triangles, you can use an EBO to reference shared vertices using indices.
     * This reduces memory usage and allows for more efficient storage of geometry data.
     */
    GLuint EBO;
    Shader m_shader{"path/to/2d_vertex_shader.glsl", "path/to/2d_fragment_shader.glsl"};
    Texture m_texture{"path/to/texture.png"};
};