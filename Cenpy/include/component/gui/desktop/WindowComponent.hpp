#pragma once

#include <component/gui/desktop/Resolution.hpp>
#include <component/Component.hpp>

namespace cenpy::component::gui::desktop
{
    class WindowComponent : public Component
    {
    public:
        WindowComponent() = default;
        WindowComponent(const Resolution &res, bool fullscreen) : m_resolution(res), m_fullscreen(fullscreen) {}

        void setResolution(const Resolution &res);

        void toggleFullscreen();

        const Resolution &getResolution() const;

        bool isFullscreen() const;

    private:
        Resolution m_resolution;
        bool m_fullscreen;
    };
} // namespace cenpy::gui::desktop
