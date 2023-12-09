#include <component/gui/desktop/WindowComponent.hpp>

namespace cenpy::component::gui::desktop
{
    void WindowComponent::setResolution(const Resolution &res)
    {
        m_resolution = res;
    }

    void WindowComponent::toggleFullscreen()
    {
        m_fullscreen = !m_fullscreen;
    }

    const Resolution &WindowComponent::getResolution() const
    {
        return m_resolution;
    }

    bool WindowComponent::isFullscreen() const
    {
        return m_fullscreen;
    }

} // namespace cenpy::gui::desktop
