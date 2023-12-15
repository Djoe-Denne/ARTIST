#include <system/gui/desktop/WindowSystem.hpp>

namespace cenpy::system::gui::desktop
{

    void WindowSizeSystem::update(component::gui::desktop::WindowComponent &windowComponent)
    {
        int currentWidth;
        int currentHeight;
        glfwGetWindowSize(window, &currentWidth, &currentHeight);

        // If the window size has changed, update it
        if (currentWidth != windowComponent.getResolution().getWidth() || currentHeight != windowComponent.getResolution().getHeight())
        {
            glfwSetWindowSize(window, windowComponent.getResolution().getWidth(), windowComponent.getResolution().getHeight());
        }
    }

    void WindowFullscreenSystem::update(component::gui::desktop::WindowComponent &windowComponent)
    {
        if (windowComponent.isFullscreen())
        {
            // Get the current window position and size
            int x;
            int y;
            int width;
            int height;
            glfwGetWindowPos(window, &x, &y);
            glfwGetWindowSize(window, &width, &height);

            // Get the list of monitors
            int monitorCount;
            GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);

            // Find the monitor that the window is currently in
            GLFWmonitor *currentMonitor = nullptr;
            for (int i = 0; i < monitorCount; i++)
            {
                int monitorX;
                int monitorY;
                glfwGetMonitorPos(monitors[i], &monitorX, &monitorY);

                if (x >= monitorX && x < monitorX + width && y >= monitorY && y < monitorY + height)
                {
                    currentMonitor = monitors[i];
                    break;
                }
            }

            // Set the window to fullscreen
            glfwSetWindowMonitor(window, currentMonitor, 0, 0, windowComponent.getResolution().getWidth(), windowComponent.getResolution().getHeight(), GLFW_DONT_CARE);
        }
        else
        {
            // Get the current window position and size
            int x;
            int y;
            int width;
            int height;
            glfwGetWindowPos(window, &x, &y);
            glfwGetWindowSize(window, &width, &height);

            // Set the window to windowed
            glfwSetWindowMonitor(window, nullptr, x, y, width, height, GLFW_DONT_CARE);
        }
    }

} // namespace cenpy::system::gui::desktop
