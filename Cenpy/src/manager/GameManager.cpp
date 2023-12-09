
#include <iostream>
#include <stacktrace>
#include <manager/GameManager.hpp>

namespace cenpy::manager
{

    void error_callback(int error, const char *description)
    {
        std::cerr << " [" << error << "] " << description << '\n';
    }

    void GameManager::startMainLoop()
    {

        if (!initialize())
        {
            std::cerr << "Failed to initialize the game.\n";
            return;
        }

        // Main loop
        m_isRunning = true;
        while (m_isRunning && !glfwWindowShouldClose(m_window))
        {
            // Process input events
            glfwPollEvents();

            // Update and render the game
            update();
            render();

            // Swap buffers
            glfwSwapBuffers(m_window);
        }

        // Cleanup and terminate GLFW
        cleanup();
    }

    bool GameManager::initialize()
    {
        // Initialize GLFW
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW.\n";
            return false;
        }

        glfwSetErrorCallback(error_callback);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        // Create a GLFW window
        m_window = glfwCreateWindow(800, 600, "ECS Game", nullptr, nullptr);
        if (!m_window)
        {
            std::cerr << "Failed to create GLFW window.\n";
            glfwTerminate();
            return false;
        }

        // Make the OpenGL context current
        glfwMakeContextCurrent(m_window);

        // Initialize GLEW
        if (glewInit() != GLEW_OK)
        {
            std::cerr << "Failed to initialize GLEW.\n";
            return false;
        }

        // Additional initialization if needed

        return true;
    }

    void GameManager::update()
    {
        // Update game logic, including ECS updates
    }

    void GameManager::render()
    {
        // Render game, including ECS rendering
    }

    void GameManager::cleanup()
    {
        // Cleanup resources and terminate GLFW
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

} // namespace cenpy::manager
