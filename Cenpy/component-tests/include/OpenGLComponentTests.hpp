#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gtest/gtest.h>

class OpenGLComponentTest : public ::testing::Test
{
public:
    GLFWwindow *window;
    void SetUp() override
    {
        // Initialize GLFW
        if (!glfwInit())
        {
            // Initialization failed
            throw std::runtime_error("Failed to initialize GLFW.");
        }

        // Set OpenGL version, e.g., for OpenGL 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create a windowed mode window and its OpenGL context
        window = glfwCreateWindow(640, 480, "Test", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            // Window or OpenGL context creation failed
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);

        // Initialize GLEW
        if (glewInit() != GLEW_OK)
        {
            throw std::runtime_error("Failed to initialize GLEW.");
        }
    }

    void TearDown() override
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};
