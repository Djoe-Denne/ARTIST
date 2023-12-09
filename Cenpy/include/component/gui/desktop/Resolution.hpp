#pragma once

#include <cstdint>

namespace cenpy::component::gui::desktop
{
    class Resolution
    {
    public:
        Resolution() = default;
        Resolution(uint16_t width, uint16_t height)
            : m_width(width), m_height(height) {}

        uint16_t getWidth() const { return m_width; }
        uint16_t getHeight() const { return m_height; }

        void setWidth(uint16_t width) { m_width = width; }
        void setHeight(uint16_t height) { m_height = height; }

    private:
        uint16_t m_width;
        uint16_t m_height;
    };
} // namespace cenpy::gui::desktop
