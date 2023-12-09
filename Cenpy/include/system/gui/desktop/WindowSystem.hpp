#pragma once

#include <GLFW/glfw3.h>
#include <component/gui/desktop/WindowComponent.hpp>
#include <system/System.hpp>

namespace cenpy::system::gui::desktop
{
    /**
     * @brief A system that updates the size of a window if it has changed.
     */
    class WindowSizeSystem : public System<component::gui::desktop::WindowComponent>
    {
    private:
        GLFWwindow *window;

    public:
        /**
         * @brief Constructs a WindowSizeSystem object.
         * @param window The GLFWwindow object representing the window.
         */
        WindowSizeSystem(GLFWwindow *window) : window(window)
        {
        }

        /**
         * @brief Updates the window size if it has changed.
         * @param windowComponent The component::gui::desktop::WindowComponent object associated with the window.
         */
        void update(component::gui::desktop::WindowComponent &windowComponent) override;
    };

    /**
     * @brief A system for managing fullscreen functionality of a window.
     *
     * This system is responsible for updating the fullscreen state of a window based on the component::gui::desktop::WindowComponent's fullscreen flag.
     * It uses GLFW functions to set the window to fullscreen or windowed mode.
     */
    class WindowFullscreenSystem : public System<component::gui::desktop::WindowComponent>
    {
    private:
        GLFWwindow *window;

    public:
        /**
         * @brief Constructs a WindowFullscreenSystem object.
         *
         * @param window The GLFWwindow object representing the window to manage fullscreen for.
         */
        WindowFullscreenSystem(GLFWwindow *window) : window(window) {}

        /**
         * @brief Updates the fullscreen state of the window.
         *
         * This function is called by the system manager to update the fullscreen state of the window based on the component::gui::desktop::WindowComponent's fullscreen flag.
         * If the fullscreen state has changed, it uses GLFW functions to set the window to fullscreen or windowed mode.
         *
         * @param windowComponent The component::gui::desktop::WindowComponent associated with the window.
         */
        void update(component::gui::desktop::WindowComponent &windowComponent) override;
    };
} // namespace cenpy::system::gui::desktop
