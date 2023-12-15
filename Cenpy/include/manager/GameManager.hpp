#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace cenpy::manager
{
    class GameManager
    {
    public:
        void startMainLoop();

    private:
        GLFWwindow *m_window;
        bool m_isRunning;

        bool initialize();

        void update();

        void render();

        void cleanup();
    };
} // namespace cenpy::manager
